/*
 * main.c - A simple  HTTP/1.0 Web server based on select
 *     Created by hs on 2020/3/12.
 */
#include "csapp.h"
#include "tiny.h"
#include "pool.h"

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
    init_pool(listenfd, &pool);

    while (1) {
        /* Wait for listening/connected descriptor(s) to become ready */
        pool.ready_set = pool.read_set;

        if ((pool.nready = select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL)) < 0 ) {
            if (errno = EINTR) {
                continue;
            }
            else
                unix_error("Select error");
        }

        /* If listening descriptor ready, add new client to pool */
        if (FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(clientaddr);
            connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        check_clients(&pool);
    }
}