// This module has helper functions to write response into buffer from the struct to directly send over sockets
#ifndef RESPONSE_H
#define RESPONSE_H

#include <stddef.h> // for size_t
#include "http.h"

// this helper maps mime enum type to the string mime type to be sent in response
const char* mime_to_string(MIMEType mime);

// this is helper which will map status code to the string reason to be sent in response
const char* status_reason(HTTPStatus status);

// this helper writes the body of response when there is no appropriate file or some error
const char *generate_error_page(HTTPStatus status);

// this helper writes raw http response into buffer provided and return size of header written
size_t serialize_response(HTTPResponse* response, char* buffer, size_t bufsize);

#endif