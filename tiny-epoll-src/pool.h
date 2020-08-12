/*
 * pool.h
 */
#include <sys/epoll.h>
#define MAX_EVENTS 4096
// ulimit -n 4096

typedef struct {      /* Represents a pool of connected descriptors */ //line:conc:echoservers:beginpool
    int epfd, listenfd;
    int nready;       /* Number of ready descriptors from select */
    struct epoll_event evlist[MAX_EVENTS];
    rio_t clientrio[MAX_EVENTS]; /* Set of active read buffers */
} pool; //line:conc:echoservers:endpool
void init_pool(int eventfd, int listenfd, pool *p);

void add_client(int connfd, pool *p);

void check_clients(pool *p);
