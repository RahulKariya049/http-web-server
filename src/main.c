#include "server.h"
#include "http.h"
#include <stdio.h>
int main(){
    // create server instance
    Server server;
    server = create_server("127.0.0.1", 6767, 10);
    
    if(server.fd == -1){
        printf("There is an error creating socket..\n");
    }

    printf("Server instance create successfully..\n");

    int i=0;
    while(i < 2){
        Client clt;
        clt = accept_request(&server);

        char* raw_request = receive_request(&clt);

        printf("Received Request:\n");
        printf("%s", raw_request);

        HTTPRequest req;
                
        close_client(&clt);

        i++;
        printf("Served %d Client\n", i);
    }
    destroy_server(&server);
    return 0;
}