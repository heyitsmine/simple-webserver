/*
 * pool.h
 */
#include <poll.h>
#define OPEN_MAX 4096
// ulimit -n 4096

typedef struct {      /* Represents a pool of connected descriptors */ //line:conc:echoservers:beginpool
    int nready;       /* Number of ready descriptors from select */
    int maxi;         /* Highwater index into client array */
    struct pollfd client[OPEN_MAX];    /* Set of active descriptors */
    rio_t clientrio[OPEN_MAX]; /* Set of active read buffers */
} pool; //line:conc:echoservers:endpool
void init_pool(int listenfd, pool *p);

void add_client(int connfd, pool *p);

void check_clients(pool *p);
