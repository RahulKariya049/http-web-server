// this module defines different structs needed like HTTPRequest HTTPResponse..
#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>

typedef struct
{
    char* key;
    char* value;
    // this makes assumption now req buffer should be freed adter the response is generated and parser adds '\0' for us  
} Header;

typedef struct
{
    // right now we stick to fixed number of headers to be allowed at max 20 headers
    Header headers[20];
    int header_count;

    char* method;
    char* path;
    char* version;

} HTTPRequest;


typedef struct
{
    int status_code;

    Header *headers;
    size_t header_count;
    size_t header_capacity;

    char *body;
    size_t body_length;

} HTTPResponse;

#endif
