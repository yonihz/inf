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
    printf("super_block info:\n");
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
    printf("super_block: s_block_group_nr = %lu\n", sb->s_block_group_nr);
    printf("super_block: s_blocks_count = %lu\n", sb->s_blocks_count);
    printf("super_block: s_log_block_size = %lu\n", sb->s_log_block_size);

}

void PrintGroupDesc(char *device_name)
{
    printf("super_block info:\n");
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

    printf("ext2_group_desc: bg_used_dirs_count = %lu\n", gb->bg_used_dirs_count);
    printf("ext2_group_desc: bg_free_inodes_count = %lu\n", gb->bg_free_inodes_count);
}