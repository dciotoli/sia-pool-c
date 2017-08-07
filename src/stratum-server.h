#ifndef STRATUM_SERVER_H
#define STRATUM_SERVER_H

#define MAX_CONCURRENCY 20
#define BUFFER_SIZE 1024
#define on_error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

void *clientThread(void *args);
int serverInit(int port);
int acceptConn(int server_fd);

#endif /* STRATUM_SERVER_H */