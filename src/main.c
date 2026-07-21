#include "server.h"
#include "http.h"
#include "parser.h"
#include <stdio.h>
int main(){
    // create server instance
    Server server;
    server = create_server("127.0.0.1", 6767, 10);
    
    if(server.fd == -1){
        printf("[LOG]: There is an error creating socket..\n");
    }

    printf("Server instance create successfully..\n");

    int i=0;
    while(i < 1){
        // Client clt;
        // clt = accept_request(&server);

        // char* raw_request = receive_request(&clt);

        // printf("Received Request:\n");
        // printf("%s", raw_request);
        char raw_request[] =
        "GET /index.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64)\r\n"
        "Connection: keep-alive\r\n"
        "\r\n";

        HTTPRequest req;
        int valid = parse_request(raw_request, &req);

        if(valid == -1){
            printf("[LOG]: Invalid Request or Parser Error");
        }
        
        printf("HEADER OF REQUEST: \n");
        printf("METHOD: %s PATH: %s VERSION: %s\n", req.method, req.path, req.version);

        for(int i=0; i<req.header_count; i++){
            printf("HEADER:\n");
            printf("%s : %s\n", req.headers[i].key, req.headers[i].value);
        }
        // close_client(&clt);

        i++;
        printf("Served %d Client\n", i);
    }
    destroy_server(&server);
    return 0;
}