#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "stratum-server.h"
#include "stratum_protocol.h"

void *clientThread(void *args) {
	char buf[BUFFER_SIZE];
	char resp[BUFFER_SIZE];
	int client_fd, err;

	client_fd = *((int *) args);
	while(1) {
		int read = recv(client_fd, buf, BUFFER_SIZE, 0);
	    if (!read) break; // done reading
		if (read < 0) on_error("Client read failed\n");

		// figure out what the f im supposed to do
		process(&buf[0], &resp[0]);
		// TODO: is strlen(resp) ok ???
		err = send(client_fd, resp, strlen(resp), 0);
		if (err < 0) on_error("Client write failed\n");
		// clear buffer
		memset(buf, '\0', (size_t) BUFFER_SIZE);
	}

	return NULL;
}

int serverInit(int port) {
	int server_fd, err, opt_val;
	struct sockaddr_in server;

	opt_val = 1;

	// begin listening for connections on port
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
  	if (server_fd < 0) on_error("Could not create socket\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

	err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
	if (err < 0) on_error("Could not bind socket\n");

	err = listen(server_fd, 128);
	if (err < 0) on_error("Could not listen on socket\n");

	printf("Server is listening on %d\n", port);

	// if successful return server's file descriptor
	return server_fd;
}

int acceptConn(int server_fd) {
	struct sockaddr_in client;
	int client_fd;
	socklen_t client_len = sizeof(client);
	pthread_t t[MAX_CONCURRENCY];

	while (1) {
		for (int i = 0; i < MAX_CONCURRENCY; i++) {
			client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);
			if (client_fd < 0) on_error("Could not establish new connection\n");
			pthread_create(&t[i],NULL,clientThread,&client_fd);
		}
	}

	// should never get here
	return 0;
}

int main(int argc, char* argv[]) {
	int port = 1234;
	int server_fd;

	// Check args
	if (argc < 2) {
		printf("Usage: ./stratum-c <port>\n");
		exit(-1);
	}
	port = atoi(argv[1]);
	if (port <= 0) {
		printf("Invalid port provided.\n");
		exit(-2);
	}

	// Initialize the server
	server_fd = serverInit(port);
	acceptConn(server_fd);


	// should never reach here
	return 0;
}