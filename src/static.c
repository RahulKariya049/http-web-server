#include "http.h"
#include <string.h> // for strcmp and other helpers
#include <sys/stat.h> // for struct stat
#include <stdlib.h> // for free(ptr)

// this helper fills up the struct which it got from main basically fills up HTTPResponse struct
void process_static_request(const HTTPRequest* req, HTTPResponse* res){

    if(strcmp(req->method,"GET") != 0){
        res->status = HTTP_METHOD_NOT_ALLOWED;
        res->body.is_file = false;
        res->mime = MIME_HTML;
        printf("[LOG]: Bruhh this method is not supported yet...\n");
        return;
    }

    char *temp_file_source;

    if (strcmp(req->path, "/") == 0){
        temp_file_source = malloc(strlen("public/index.html") + 1);
        if (temp_file_source == NULL) {
            res->status = HTTP_INTERNAL_SERVER_ERROR;
            res->body.is_file = false;
            res->mime = MIME_HTML;
            printf("[LOG]: malloc allocation failed\n");
            return;
        }
        strcpy(temp_file_source, "public/index.html");
    }
    else{
        size_t len = strlen("public") + strlen(req->path) + 1;

        temp_file_source = malloc(len);
        // memory allocation error
        if (temp_file_source == NULL) {
            res->status = HTTP_INTERNAL_SERVER_ERROR;
            res->body.is_file = false;
            res->mime = MIME_HTML;
            printf("[LOG]: malloc allocation failed\n");
            return;
        }

        strcpy(temp_file_source, "public");
        strcat(temp_file_source, req->path);
    }

    struct stat st;
    // file does not exist
    if(stat(temp_file_source, &st) == -1){
        res->status = HTTP_NOT_FOUND;
        res->body.is_file = false;
        res->mime = MIME_HTML;
        printf("[LOG]: Bruhh this path does not even Exists\n");
        free(temp_file_source);
        return;
    }

    // if not a regular file
    if(!S_ISREG(st.st_mode)){
        res->status = HTTP_INTERNAL_SERVER_ERROR;
        res->body.is_file = false;
        res->mime = MIME_HTML;
        printf("[LOG]: Bruhh this guy didn't ask file he is asking Directoryy\n");
        free(temp_file_source);
        return;
    }

    res->status = HTTP_OK;
    res->body.file_source = temp_file_source;  // main should free this heap allocated memoryyyyyyy
    res->body.is_file = true;
    res->body.length = st.st_size;

    char* extension = strrchr(temp_file_source, '.'); // extension has string .png .hmtl or like that

    if(extension == NULL) res->mime = MIME_TEXT;
    else if(strcmp(extension, ".html") == 0) res->mime = MIME_HTML;
    else if(strcmp(extension, ".css") == 0) res->mime = MIME_CSS;
    else if(strcmp(extension, ".svg") == 0) res->mime = MIME_SVG;
    else if(strcmp(extension, ".png") == 0) res->mime = MIME_PNG;
    else if(strcmp(extension, ".jpg") == 0) res->mime = MIME_JPG;

    return;
    
}