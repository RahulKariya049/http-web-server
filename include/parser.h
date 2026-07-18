// This modules includes helpers for parsing HTTPRequest and storing it in struct defined in http.h
#ifndef SERVER_H
#define SERVER_H

#include "http.h"

// int basically here is 0 means gracefully filled struct instead -1 means INVALID REQUEST
int parse_request(const char* buffer, HTTPRequest *request);

#endif