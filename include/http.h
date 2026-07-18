// this module defines different structs needed like HTTPRequest HTTPResponse..
#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>


typedef struct
{
    char key[64];
    char value[512];
} Header;

typedef struct
{
    Header *headers;
    size_t header_count;
    size_t header_capacity;

    char method[8];
    char path[256];
    char version[16];

    char *body;
    size_t body_length;

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
