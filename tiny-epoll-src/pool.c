/*
 * pool.c - pool of connected descriptors
 */
#include "csapp.h"
#include "pool.h"
#include "tiny.h"

static int byte_cnt = 0; /* Counts total bytes received by server */

void init_pool(int epfd, int listenfd, pool *p)
{
    p->epfd = epfd;
    p->listenfd = listenfd;
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    epoll_ctl(p->epfd, EPOLL_CTL_ADD, listenfd, &ev);
}

void add_client(int connfd, pool *p)
{
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = connfd;
    epoll_ctl(p->epfd, EPOLL_CTL_ADD, connfd, &ev);
}

void check_clients(pool *p)
{
    int connfd;
    char buf[MAXLINE];
    rio_t rio;

    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    struct epoll_event ev;
    ev.events = EPOLLIN;
    
    for (int i = 0; i < p->nready; i++) {
        rio = p->clientrio[i];
        if (p->evlist[i].data.fd == p->listenfd && p->evlist[i].events & EPOLLIN) {
            clientlen = sizeof(clientaddr);
            connfd = Accept(p->listenfd, (SA *) &clientaddr, &clientlen);
            add_client(connfd, p);
        } else if (p->evlist[i].events & EPOLLIN) {
            doit(p->evlist[i].data.fd);
            Close(p->evlist[i].data.fd);
        }
    }
}

