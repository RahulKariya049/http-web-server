#include "http.h"
#include <string.h> // for string functions
#include <stdio.h> // for printf
// helpers for parser
char* find_char(char* string, char target){
    while (*string)
    {
        if (*string == target)
            return string;

        string++;
    }
    return NULL;
}

char* find_crlf(char* string){
    while(*string){
        if(*(string+1) && (*string == '\r' && *(string+1) == '\n')){
            return string;
        }
        string++;
    }
    return NULL;
}

// int basically here is 0 means gracefully filled struct instead -1 means INVALID REQUEST
int parse_request(char* buffer, HTTPRequest *request){
    int parsed_lines = 0;
    int th = 0; // total headers
    while(1){
        // get first line
        char* line_end = find_crlf(buffer);
        // so this means buffer ptr to line_end is current line
        if(!parsed_lines){
            char* first_space = find_char(buffer, ' ');
            request->method = buffer;
            *first_space = '\0';
            buffer = first_space + 1;

            char* second_space = find_char(buffer, ' ');
            request->path = buffer;
            *second_space = '\0';
            buffer = second_space + 1;

            request->version = buffer;
            *line_end = '\0';
        }
        else{
            char* colon = find_char(buffer, ':');
            *colon = '\0'; //for key of header;
            request->headers[th].key = buffer;
            buffer = colon + 1;

            // remoce leading spaces
            while(*buffer == ' '){
                buffer++;
            }
            request->headers[th].value = buffer;
            *line_end = '\0';

            th++;
        }
        buffer = line_end + 2;
        parsed_lines++;
        if(*buffer == '\r' && *(buffer+1) == '\n'){
            // header ended 
            break;
        }
        if(th == 20){
            printf("[LOG]: BRUHH how many headers you want huh\n");
            return -1;
        }
    }

    request->header_count = th;
    return 0;
}