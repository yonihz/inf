// install ext2 libs: sudo apt-get install e2fslibs-dev
// include in program: #include <ext2fs/ext2_fs.h>
// create block ram disk /dev/ram0: sudo modprobe brd
// make ext2 fs: sudo mkfs.ext2 /dev/ram0
// mount fs: sudo mount /dev/ram0 /mnt -o sync
// show mount info: df /mnt
// unmount: sudo umount /mnt
// remove block ram disk: sudo modprobe -r brd

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ext2fs/ext2_fs.h>
#include <string.h>

#define SUPERBLOCK_OFFSET 1024

int GetInodeRegFileInRoot(int fd, const char *regfile_name, struct ext2_inode *inode_regfile);
int GetInodeRegFile(int fd, const char *regfile_name, struct ext2_inode *inode_regfile);
void PrintRegFile(int fd, struct ext2_inode *inode_regfile);

int GetSuperBlock(int fd, struct ext2_super_block *sb);
size_t GetBlockSize(struct ext2_super_block *sb);
size_t GetInodeSize(struct ext2_super_block *sb);
int GetGroupDesc(int fd, size_t idx, size_t block_size, struct ext2_group_desc *gb);
int GetInodeInDir(int fd, size_t block_size, size_t inode_size, const char *file_name, struct ext2_inode *inode_dir, struct ext2_inode *inode_file);

int main()
{
    char *device_name = "/dev/ram0";
    int fd = open(device_name, O_RDONLY);
    int status;

    if (-1 == fd)
    {
        perror("open");
        return 0;
    }

    // Test: print file content in root

    struct ext2_inode inode_regfile1;
    const char *regfile_name1 = "test1";

    status = GetInodeRegFileInRoot(fd, regfile_name1, &inode_regfile1);

    if (status == 0)
    {
        PrintRegFile(fd, &inode_regfile1);
    }
    else
    {
        printf("File not found: %s\n", regfile_name1);
    }

    // Test: print file content in any directory

    struct ext2_inode inode_regfile2;
    const char *regfile_name2 = "/dir1/dir2/test2";
    
    status = GetInodeRegFile(fd, regfile_name2, &inode_regfile2);

    if (status == 0)
    {
        PrintRegFile(fd, &inode_regfile2);
    }
    else
    {
        printf("File not found: %s\n", regfile_name2);
    }
    
    return 0;
}

int GetSuperBlock(int fd, struct ext2_super_block *sb)
{
    lseek(fd, SUPERBLOCK_OFFSET, SEEK_SET);
    int status = read(fd, sb, sizeof(struct ext2_super_block));

    if (-1 == status)
    {
        perror("read");
        return -1;
    }

    if (sb->s_magic != EXT2_SUPER_MAGIC)
    {
        fprintf(stderr, "Filesystem is not ext2\n");
        return -1;
    }

    return 0;
}

size_t GetBlockSize(struct ext2_super_block *sb)
{
    return (1024 << sb->s_log_block_size);
}

size_t GetInodeSize(struct ext2_super_block *sb)
{
    return sb->s_inode_size;
}

size_t GetInodePerGroup(struct ext2_super_block *sb)
{
    return sb->s_inodes_per_group;
}

int GetGroupDesc(int fd, size_t idx, size_t block_size, struct ext2_group_desc *gb)
{
    lseek(fd, SUPERBLOCK_OFFSET + block_size + (idx -1) * sizeof(struct ext2_group_desc), SEEK_SET);
    int status = read(fd, gb, sizeof(struct ext2_group_desc));

    if (-1 == status)
    {
        perror("read");
        return -1;
    }

    return 0;
}

int GetRootInode(int fd, struct ext2_group_desc *first_gb, size_t block_size, size_t inode_size, struct ext2_inode *inode_root)
{
    size_t inode_table_offset = block_size * first_gb->bg_inode_table;
    size_t inode_root_offset = inode_table_offset + inode_size;
    lseek(fd, inode_root_offset, SEEK_SET);
    read(fd, inode_root, sizeof(struct ext2_inode));
    return 0; // return value?
}

int GetInodeInDir(int fd, size_t block_size, size_t inode_size, const char *file_name, struct ext2_inode *inode_dir, struct ext2_inode *inode_file)
{
    char buff[256]; // size?

    struct ext2_super_block sb;
    GetSuperBlock(fd, &sb);
    size_t inodes_per_group = GetInodePerGroup(&sb);

    struct ext2_dir_entry_2 dir;
    lseek(fd, block_size * inode_dir->i_block[0], SEEK_SET);
    size_t total_rec_len = 0;
    read(fd, &dir, sizeof(struct ext2_dir_entry_2));

    while (total_rec_len < block_size)
    {
        strncpy(buff, dir.name, dir.name_len);
        buff[dir.name_len] = '\0';

        if (strncmp(buff, file_name, dir.name_len) == 0)
        {
            if (dir.file_type == EXT2_FT_REG_FILE || dir.file_type == EXT2_FT_DIR)
            {
                size_t gb_idx = (dir.inode - 1) / inodes_per_group + 1;
                size_t inode_idx = (dir.inode - 1) % inodes_per_group + 1;
                struct ext2_group_desc gb;
                GetGroupDesc(fd, gb_idx, block_size, &gb);
                size_t inode_table_offset = block_size * gb.bg_inode_table;
                size_t inode_file_offset = inode_table_offset + inode_size * (inode_idx - 1);
                lseek(fd, inode_file_offset, SEEK_SET);
                read(fd, inode_file, sizeof(struct ext2_inode));
                return dir.file_type;
            }
            else
            {
                break;
            }
        }

        lseek(fd, dir.rec_len - sizeof(struct ext2_dir_entry_2), SEEK_CUR);
        total_rec_len += dir.rec_len;
        read(fd, &dir, sizeof(struct ext2_dir_entry_2));
    }

    return -1;
}

int GetInodeRegFileInRoot(int fd, const char *regfile_name, struct ext2_inode *inode_regfile)
{
    struct ext2_super_block sb;
    int status = GetSuperBlock(fd, &sb);

    if (-1 == status)
    {
        fprintf(stderr, "GetSuperBlock failed\n");
        return 0;
    }

    size_t block_size = GetBlockSize(&sb);
    size_t inode_size = GetInodeSize(&sb);

    struct ext2_group_desc gb;
    status = GetGroupDesc(fd, 1, block_size, &gb);

    if (-1 == status)
    {
        fprintf(stderr, "GetGroupDesc failed\n");
        return 0;
    }

    struct ext2_inode inode_root;
    GetRootInode(fd, &gb, block_size, inode_size, &inode_root);
    
    status = GetInodeInDir(fd, block_size, inode_size, regfile_name, &inode_root, inode_regfile);

    if (EXT2_FT_REG_FILE == status)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int GetInodeRegFile(int fd, const char *regfile_name, struct ext2_inode *inode_file)
{
    struct ext2_super_block sb;
    int status = GetSuperBlock(fd, &sb);
    char *file_name = (char*)malloc(strlen(regfile_name) + 1);
    strcpy(file_name, regfile_name);
    char *file_name_org = file_name;

    if (-1 == status)
    {
        fprintf(stderr, "GetSuperBlock failed\n");
        return 0;
    }

    size_t block_size = GetBlockSize(&sb);
    size_t inode_size = GetInodeSize(&sb);

    struct ext2_group_desc gb;

    status = GetGroupDesc(fd, 1, block_size, &gb);

    if (-1 == status)
    {
        fprintf(stderr, "GetGroupDesc failed\n");
        return 0;
    }

    struct ext2_inode inode_curr;
    GetRootInode(fd, &gb, block_size, inode_size, &inode_curr);

    if (file_name[0] == '/')
    {
        ++file_name;
    }

    char *p;
    while (1)
    {
        if (*file_name == '\0')
        {
            printf("Invalid filename\n");
        }
        p = strchr(file_name, '/');

        if (p != NULL)  
        {
            *p = '\0';
        }

        status = GetInodeInDir(fd, block_size, inode_size, file_name, &inode_curr, inode_file);

        if (-1 == status)
        {
            break;
        }

        if (EXT2_FT_DIR == status) 
        {
            inode_curr = *inode_file;
            file_name = p + 1;
        }
        else if (EXT2_FT_REG_FILE == status)
        {
            break;
        }
    }

    free(file_name_org);
    return status;
}

void PrintRegFile(int fd, struct ext2_inode *inode_regfile)
{
    struct ext2_super_block sb;
    GetSuperBlock(fd, &sb);

    size_t block_size = GetBlockSize(&sb);

    char buff[256]; // size?

    lseek(fd, block_size * inode_regfile->i_block[0], SEEK_SET);
    read(fd, buff, 256);
    printf("Printing file:\n%s", buff);  
}