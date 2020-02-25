// install ext2 libs: sudo apt-get install e2fslibs-dev
// include in program: #include <ext2fs/ext2_fs.h>
// create block ram disk /dev/ram0: modprobe brd
// make ext2 fs: mkfs.ext2 /dev/ram0
// mount fs: mount /dev/ram0 /mnt -o sync
// show mount info: df /mnt
// unmount: umount /mnt/
// remove block ram disk: sudo modprobe -r brd

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ext2fs/ext2_fs.h>
#include <string.h>


void PrintSuperBlock(char *device_name);
void PrintGroupDesc(char *device_name);

int main()
{
    char *device_name = "/dev/ram0";
    PrintSuperBlock(device_name);
    PrintGroupDesc(device_name);

    return 0;
}

void PrintSuperBlock(char *device_name)
{
    printf("-----\n");
    printf("super_block info:\n");
    printf("-----\n");
    int fd;
    ssize_t status;
    fd = open(device_name, O_RDONLY);

    if (-1 == fd)
    {
        perror("open");
        return;
    }

    struct ext2_super_block *sb = malloc(sizeof(struct ext2_super_block));

    lseek(fd, (off_t) 1024, SEEK_SET);
    status = read(fd, sb, sizeof(struct ext2_super_block));

    if (-1 == status)
    {
        perror("read");
        return;
    }

    printf("super_block: s_magic = %x\n", sb->s_magic);
    printf("super_block: s_inodes_count = %d\n", sb->s_inodes_count);
    printf("super_block: s_blocks_count = %d\n", sb->s_blocks_count);
    printf("super_block: s_first_data_block = %d\n", sb->s_first_data_block);
    printf("super_block: s_log_block_size = %d (%d)\n", sb->s_log_block_size, 1 << (10 + sb->s_log_block_size)); /* Block size is 2 ^ (10 + s_log_block_size) */
    printf("super_block: s_first_ino = %u\n", sb->s_first_ino);
    printf("super_block: s_inode_size = %u\n", sb->s_inode_size);
}

void PrintGroupDesc(char *device_name)
{
    printf("-----\n");
    printf("group_desc info:\n");
    printf("-----\n");
    int fd;
    ssize_t status;
    fd = open(device_name, O_RDONLY);

    if (-1 == fd)
    {
        perror("open");
        return;
    }

    struct ext2_group_desc *gb = malloc(sizeof(struct ext2_group_desc));

    lseek(fd, 1024 * 2, SEEK_SET);
    status = read(fd, gb, sizeof(struct ext2_group_desc));

    if (-1 == status)
    {
        perror("read");
        return;
    }

    printf("ext2_group_desc: bg_inode_table = %x (x) / %d (d)\n", gb->bg_inode_table, gb->bg_inode_table);

    printf("-----\n");
    printf("inode info:\n");
    printf("-----\n");

    struct ext2_inode *ino = malloc(sizeof(struct ext2_inode));

    lseek(fd, 1024 * 258 + 1 * 128, SEEK_SET); /* root dir inode */
    status = read(fd, ino, sizeof(struct ext2_inode));

    if (-1 == status)
    {
        perror("read");
        return;
    }

    printf("ext2_inode: i_size = %d\n", ino->i_size);
    printf("ext2_inode: i_block = %d\n", ino->i_block[0]);

    struct ext2_dir_entry_2 *dir = malloc(sizeof(struct ext2_dir_entry_2));

    lseek(fd, 1024 * ino->i_block[0], SEEK_SET); /* root dir data */
    status = read(fd, dir, sizeof(struct ext2_dir_entry_2));

    printf("ext2_dir_entry: inode = %u\n", dir->inode);
    printf("ext2_dir_entry: file_type = %d\n", dir->file_type);
    char *file_name = (char*)malloc(sizeof(dir->name_len));
    strcpy(file_name, dir->name);
    printf("ext2_dir_entry: name = %s\n", file_name);

}