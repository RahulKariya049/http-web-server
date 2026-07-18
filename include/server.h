// this module has responsibility of networking socket creation handling reading requests sending 

#ifndef SERVER_H
#define SERVER_H
#include <stdint.h> // for fixed-width integer types 
#include <stddef.h>

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

// this function reads from client sockets and returns number of bytes of request
int receive_request(Client* client, char* request_buffer, size_t size);

// this function writes response of requested resource to client socket and returns number of bytes written
int send_response(Client* client, char* response_buffer, size_t size);


void close_client(Client* client);

void destroy_server(Server* server);

#endif