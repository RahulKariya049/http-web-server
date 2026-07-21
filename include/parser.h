// This modules includes helpers for parsing HTTPRequest and storing it in struct defined in http.h
#ifndef PARSER_H
#define PARSER_H

#include "http.h"

// thee are helpers for parser
char* find_char(char* string, char target);

char* find_crlf(char* string);

// int basically here is 0 means gracefully filled struct instead -1 means INVALID REQUEST
int parse_request(const char* buffer, HTTPRequest *request);

#endif