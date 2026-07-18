// this module has responsibility of networking socket creation handling reading requests sending 

#ifndef SERVER_H
#define SERVER_H
#include <stdint.h> // for fixed-width integer types 
#include <stddef.h>

#define MAX_REQUEST_BUFFER 16000

typedef struct 
{
    int fd; 
    uint16_t port; // 16bit unsigned int
}Server;

typedef struct 
{
    int fd;
}Client;

// create a socket and bind port 
Server create_server(const char* ip, uint16_t port, int backlog);

// listens and accepts TCP requests from clients with backlog and returns fd of client
Client accept_request(Server* server);

// this function reads from client sockets and returns the pointer to the buffer where request is appended
char* receive_request(Client* client);

// this function writes response of requested resource to client socket and returns number of bytes written
int send_response(Client* client, char* response_buffer, size_t size);


void close_client(Client* client);

void destroy_server(Server* server);

#endif