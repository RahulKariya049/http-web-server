# RahulHTTP

RahulHTTP is a lightweight HTTP/1.1 web server written in C using POSIX sockets on Linux. It serves static files, parses HTTP requests, generates standards-compliant HTTP responses, and is designed with a modular architecture where networking, parsing, response generation, and static file handling remain independent components.

## Features

* HTTP/1.1 request parsing
* Static file serving
* MIME type detection
* Custom 404 error pages
* Browser-compatible responses
* Content-Length and Content-Type support
* Modular architecture with clear separation of responsibilities
* Tested across browsers and physical devices over a local network

## Project Structure

```
src/
├── main.c
├── server.c
├── parser.c
├── response.c
└── static.c

include/
├── http.h
├── server.h
├── parser.h
├── response.h
└── static.h

public/
```

## Module Responsibilities

### http.h

Defines the core HTTP data structures shared across the project.

Contains:

* `HTTPRequest`
* `HTTPResponse`
* `HTTPBody`
* `Header`
* `HTTPStatus` enum
* `MIMEType` enum

---

### server.c / server.h

Responsible for the networking layer.

Provides:

* `create_server()`
* `accept_request()`
* `receive_request()`
* `send_response()`
* `close_client()`
* `close_server()`

This module manages socket creation, connection handling, receiving client requests, transmitting responses, and server shutdown.

---

### parser.c / parser.h

Responsible for converting raw HTTP request bytes into an `HTTPRequest` structure.

Includes small parsing helpers such as:

* `find_char()`
* `find_crlf()`

along with the request parser itself.

---

### static.c / static.h

Assists response generation by handling static resources.

Responsibilities include:

* Validating requested file paths using `stat()`
* Determining appropriate MIME types
* Identifying missing resources
* Reporting the appropriate HTTP status back to the response layer

This module does not serialize HTTP responses; it provides file-system information used to construct them.

---

### response.c / response.h

Responsible for HTTP response serialization.

Given a populated `HTTPResponse` structure, this module generates the exact byte stream that is transmitted to the client.

Responsibilities include:

* Writing the status line
* Serializing HTTP headers
* Formatting the final response buffer

This module performs no routing or file validation—it only converts an `HTTPResponse` into a valid HTTP response.

---

## Request Lifecycle

```
Client
    │
    ▼
server.c
    │
receive_request()
    │
    ▼
parser.c
    │
HTTPRequest
    │
    ▼
static.c
    │
File validation
MIME detection
Status selection
    │
    ▼
response.c
    │
Serialize HTTPResponse
into raw bytes
    │
    ▼
server.c
    │
send_response()
    │
    ▼
Client
```

## Current Limitations

* Handles one client connection at a time
* Connection closes after every response (no persistent connections)
* Supports static content only
* No multithreading or event-driven I/O
* No chunked transfer encoding
* No HTTP/2 support

## Future Roadmap

* Persistent (Keep-Alive) connections
* Memory auditing and leak elimination
* Thread pool architecture
* Event-driven I/O (`epoll`)
* Performance benchmarking and optimization
* Linux kernel networking exploration
* HTTP protocol enhancements
