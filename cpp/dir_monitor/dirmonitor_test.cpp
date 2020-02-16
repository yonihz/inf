// #include "dirmonitor.hpp"

#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>

/* size of the event structure, not counting name */
#define EVENT_SIZE (sizeof (struct inotify_event))

/* reasonable guess as to size of 1024 events */
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

int main()
{
    int fd;
    int wd;
    char *path = "/home/user/watch_dir";
    int status;
    int fdmax = 0;

    fd_set read_fds, master_fds;
    FD_ZERO(&master_fds);


    /* Create the file descriptor for accessing the inotify API */

    fd = inotify_init1(IN_NONBLOCK);
    FD_SET(fd, &master_fds);
    fdmax = fd;

    if (fd == -1)
    {
        perror("inotify_init1");
        exit(EXIT_FAILURE);
    }

    wd = inotify_add_watch(fd, path, IN_MOVED_TO | IN_MOVED_FROM | IN_DELETE);

    if (wd == -1)
    {
        fprintf(stderr, "watch '%s': %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        struct timeval timev;
        timev.tv_sec = 2;
        timev.tv_usec = 0;

        read_fds = master_fds;
        status = select(fdmax + 1, &read_fds, NULL, NULL, &timev);

        if (-1 == status)
        {
            perror("select");
        }
        else if (0 == status)
        {
            printf("time out\n");
        }
        else if (FD_ISSET (fd, &read_fds))
        {
            printf("fd ready\n");
            char buf[BUF_LEN];
            int len, i = 0;

            len = read(fd, buf, BUF_LEN);
            if (len < 0) 
            {
                if (errno == EINTR)
                {
                    /* need to reissue system call */
                }
                else
                {
                    perror ("read");
                }
            } 
            else if (!len)
            {
                printf("len = 0\n");
                /* BUF_LEN too small? */
            }

            while (i < len) 
            {
                struct inotify_event *event;

                event = (struct inotify_event *) &buf[i];

                printf ("wd=%d mask=%u cookie=%u len=%u\n",
                        event->wd, event->mask,
                        event->cookie, event->len);

                if (event->len)
                {
                    printf ("name=%s\n", event->name);
                }

                i += EVENT_SIZE + event->len;
            }
            /* inotify events are available! */
        }
    }
}