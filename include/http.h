// this module defines different structs needed like HTTPRequest HTTPResponse..
#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct
{
    char* key;
    char* value;
    // this makes assumption now req buffer should be freed adter the response is generated and parser adds '\0' for us  
} Header;

typedef enum
{
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_METHOD_NOT_ALLOWED = 405,
    HTTP_INTERNAL_SERVER_ERROR = 500

} HTTPStatus;

typedef enum{
    MIME_HTML,MIME_CSS,MIME_TEXT,MIME_PNG,MIME_SVG,MIME_JPG
}MIMEType;

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
    bool is_file;

    char *file_source;
    char *body_source;

    size_t length;

} HTTPBody;


typedef struct
{
    HTTPStatus status;

    HTTPBody body;

    MIMEType mime;

} HTTPResponse;

#endif
