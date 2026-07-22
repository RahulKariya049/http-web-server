// this helper helps reading necessary files
#ifndef STATIC_H
#define STATIC_H

#include "http.h"

// this helper fills up the struct which it got from main basically fills up HTTPResponse struct
void process_static_request(const HTTPRequest* req, HTTPResponse* res);

#endif