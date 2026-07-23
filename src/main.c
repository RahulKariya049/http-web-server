#include "server.h"
#include "http.h"
#include "parser.h"
#include "static.h"
#include "response.h"
#include <stdio.h>
#include <string.h> // for strlen()
#include <stdlib.h> // for free()
#include <sys/sendfile.h> // for sendfile()
#include <fcntl.h> // for file related system calls
#include <unistd.h> // for general POSIX system calls close() read() write()

int main(){
    // create server instance
    Server server;
    server = create_server("127.0.0.1", 6767, 10);
    
    if(server.fd == -1){
        printf("[LOG]: There is an error creating socket..\n");
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
        int valid = parse_request(raw_request, &req);

        if(valid == -1){
            printf("[LOG]: Invalid Request or Parser Error");
        }
        
        // printf("HEADER OF REQUEST: \n");
        // printf("METHOD: %s PATH: %s VERSION: %s\n", req.method, req.path, req.version);

        // for(int i=0; i<req.header_count; i++){
        //     printf("HEADER i: %d ", i);
        //     printf("%s : %s\n", req.headers[i].key, req.headers[i].value);
        // }

        HTTPResponse res;
        process_static_request(&req, &res);

        free(raw_request);

        char response_buffer[2048];
        size_t header_bytes = serialize_response(&res, response_buffer, 2048);

        printf("\n");
        printf("HEADER MADE BY SERVER: \n");
        printf("%s\n", response_buffer);
        // send header
        send_response(&clt, response_buffer, header_bytes);

        if(!res.body.is_file){
            send_response(&clt, res.body.body_source, strlen(res.body.body_source));
        }
        else{
            // read only
            int file_fd = open(res.body.file_source, O_RDONLY);

            sendfile(clt.fd, file_fd, NULL, res.body.length);

            close(file_fd);
            free(res.body.file_source);
        }

        close_client(&clt);

        i++;
        printf("Served %d Client\n", i);
    }
    destroy_server(&server);
    return 0;
}