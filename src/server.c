#include "server.h"
#include <stdio.h> //printf()
#include <stdint.h> // for uint16_t
#include <sys/socket.h>// for socket(), bind(), accept(), listen()
#include <arpa/inet.h> // for structs like sockaddr sockaddr_storage
#include <string.h> // for strlen() and strstr() to search inside string
#include <stddef.h> // for size_t
#include <stdlib.h> // for exit()
#include <unistd.h> // for close()

Server create_server(const char* ip, uint16_t port, int backlog){
    Server server;
    server.port = port;

    // request socket
    server.fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server.fd == -1){
        perror("Socket: ");
        exit(1);
    }

    // bind socket with appropriate ip
    struct sockaddr_in addr_server;
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr_server.sin_addr);

    int bind_status = bind(server.fd, (struct sockaddr*)&addr_server, sizeof(addr_server));

    if(bind_status == -1){
        perror("Bind: ");
        exit(1);
    }

    int listen_status = listen(server.fd, backlog);

    if(listen_status == -1){
        perror("Listen: ");
        exit(1);
    }

    return server;
}

Client accept_request(Server* server){
    Client client;
    struct sockaddr_storage addr_client;
    socklen_t sz = sizeof(addr_client);

    client.fd = accept(server->fd, (struct sockaddr*)&addr_client, &sz);

    if(client.fd == -1){
        perror("Client FD: ");
        exit(1);
    }
    return client;
}

char *receive_request(Client *client)
{
    int capacity = 1024;// initial buffer size
    int total_received = 0;

    char *req_buf = malloc(capacity+1);
    if (req_buf == NULL) return NULL; // allocation error

    while (1)
    {
        // No room left? Grow before recv().
        if (total_received == capacity){
            int new_capacity = capacity * 2;
            if (new_capacity > MAX_REQUEST_BUFFER){
                free(req_buf);
                return NULL;
            }
            char *temp = realloc(req_buf, new_capacity+1);
            if (temp == NULL){
                free(req_buf);
                return NULL;
            }
            req_buf = temp;
            capacity = new_capacity;
        }

        int bytes = recv(client->fd, req_buf + total_received,capacity - total_received, 0);

        if (bytes == -1){
            perror("recv");
            free(req_buf);
            return NULL;
        }

        if (bytes == 0){// Client disconnected.
            break;
        }

        total_received += bytes;
        req_buf[total_received] = '\0';

        // Complete HTTP headers?
        if (strstr(req_buf, "\r\n\r\n") != NULL){
            break;
        }
    }

    return req_buf;
}

int send_response(Client* client, char* response_buffer, size_t size){
    int written_bytes = send(client->fd, response_buffer, size, 0);
    
    if(written_bytes == -1){
        perror("Response: ");
        exit(1);
    }
    return written_bytes;
}

void close_client(Client* client){
    close(client->fd);
}


void destroy_server(Server* server){
    close(server->fd);
}