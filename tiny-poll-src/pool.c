/*
 * pool.c - pool of connected descriptors
 */
#include "csapp.h"
#include "pool.h"
#include "tiny.h"

static int byte_cnt = 0; /* Counts total bytes received by server */

void init_pool(int listenfd, pool *p)
{
    /* Initially, there are no connected descriptors */
    for (int i = 0; i < OPEN_MAX; i++)
        p->client[i].fd = -1;
    p->maxi = 0;
    p->client[0].fd = listenfd;
    p->client[0].events = POLL_IN;
}

void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    for (i = 1; i < OPEN_MAX; i++)  /* Find an available slot */
        if (p->client[i].fd < 0) {
            /* Add connected descriptor to the pool */
            p->client[i].fd = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            p->client[i].events = POLL_IN;
            
            /* Update pool highwater mark */
            if (i > p->maxi)
                p->maxi = i;
            break;
        }
    if (i == OPEN_MAX) /* Couldn't find an empty slot */
        app_error("add_client error: Too many clients");
}

void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 1; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->client[i].fd;
        rio = p->clientrio[i];

        /* If the descriptor is ready, echo a text line from it */
        if ((connfd > 0) && p->client[i].revents & POLL_IN) {
            p->nready--;

            doit(connfd);
            Close(connfd);
            p->client[i].fd = -1;
        }
    }
}

