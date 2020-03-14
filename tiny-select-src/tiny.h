/*
 * tiny.h
 */

void sigchld_handler(int signo);
void doit(int fd);
int read_requesthdrs(rio_t *rp, char *method);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize, char *method);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs, char *method);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void Im_rio_writen(int fd, void *usrbuf, size_t n); // rio_written for EPIPE error

