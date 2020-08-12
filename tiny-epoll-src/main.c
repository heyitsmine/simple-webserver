/*
 * main.c - A simple  HTTP/1.0 Web server based on select
 *     Created by hs on 2020/3/12.
 */
#include "csapp.h"
#include "tiny.h"
#include "pool.h"
#include <sys/epoll.h>

#define MAX_EVENT 4096

int main(int argc, char **argv)
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    /* Check command line args */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGPIPE, SIG_IGN);

    listenfd = Open_listenfd(argv[1]);
    int epfd = epoll_create(256);
    init_pool(epfd, listenfd, &pool);
    
    while (1) {
        /* Wait for listening/connected descriptor(s) to become ready */
        if ((pool.nready = epoll_wait(pool.epfd, pool.evlist, MAX_EVENTS, -1)) < 0 ) {
            if (errno = EINTR) {
                continue;
            }
            else
                unix_error("Select error");
        }
        check_clients(&pool);
    }
}