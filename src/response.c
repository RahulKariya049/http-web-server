#include <stddef.h> // for size_t
#include "http.h"
#include <stdio.h>
#include <string.h> // for strlen()

static const char METHOD_NOT_ALLOWED_PAGE[] =
"<h1>BRUHHHH LET ME SUPPORT THIS METHOD MAN </h1>";

static const char NOT_FOUND_PAGE[] =
"<h1>404... YOU FOUND THE VOID </h1>";

static const char BAD_REQUEST_PAGE[] =
"<h1>BRUHH.. Your Browser is trash..</h1>";

static const char INTERNAL_SERVER_ERROR_PAGE[] =
"<h1>BRUHH..  I BROKE SOMETHING INSIDE THE SERVER </h1>";


const char *generate_error_page(HTTPStatus status)
{
    switch (status)
    {
        case HTTP_BAD_REQUEST:
            return BAD_REQUEST_PAGE;

        case HTTP_METHOD_NOT_ALLOWED:
            return METHOD_NOT_ALLOWED_PAGE;

        case HTTP_NOT_FOUND:
            return NOT_FOUND_PAGE;

        case HTTP_INTERNAL_SERVER_ERROR:
            return INTERNAL_SERVER_ERROR_PAGE;

        default:
            return INTERNAL_SERVER_ERROR_PAGE;
    }
}

const char* mime_to_string(MIMEType mime){
    switch(mime){
        case MIME_HTML:
            return "text/html";
        case MIME_CSS:
            return "text/css";
        case MIME_SVG:
            return "image/svg+xml";
        case MIME_PNG:
            return "image/png";
        case MIME_JPG:
            return "image/jpeg";
        case MIME_TEXT:
            return "text/plain";
    }
    return "text/plain";
}

const char* status_reason(HTTPStatus status){
    switch(status){
        case HTTP_OK:
            return "OK";
        case HTTP_BAD_REQUEST:
            return "Bad Request";
        case HTTP_INTERNAL_SERVER_ERROR:
            return "Internal Server Error";
        case HTTP_METHOD_NOT_ALLOWED:   
            return "Method Not Allowed";
        case HTTP_NOT_FOUND:
            return "Not Found";
        case HTTP_FORBIDDEN:
            return "Forbidden";
    }
    return NULL;
}

size_t serialize_response(HTTPResponse* response, char* buffer, size_t bufsize){
    if(response->status != HTTP_OK){
        response->body.body_source = generate_error_page(response->status);
        response->body.length = strlen(generate_error_page(response->status));
    }
    int written = snprintf(buffer, bufsize,
         "HTTP/1.1 %d %s\r\n"
         "Server: RahulHTTP\r\n"
         "Content-Type: %s\r\n"
         "Content-Length: %zu\r\n"
         "Connection: close\r\n"
         "\r\n", response->status, status_reason(response->status), mime_to_string(response->mime), response->body.length);

    

    return (size_t)written;
}
