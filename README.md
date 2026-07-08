# http-web-server
# RahulHTTP

A lightweight HTTP server written in C from scratch using Linux socket APIs.

This project is a personal journey to understand how web servers work beneath frameworks. Instead of relying on existing libraries, RahulHTTP is being built layer by layer—from raw TCP sockets to parsing HTTP requests and serving static websites.

---

## Goals

- Understand Linux socket programming
- Learn HTTP by implementing it manually
- Build a modular C codebase
- Explore systems programming concepts such as file descriptors, system calls, networking, and process interaction
- Serve static HTML, CSS, and JavaScript files

---

## Current Progress

### ✅ Networking Layer

- TCP server using Linux socket APIs
- Socket creation
- Address binding
- Listening for incoming connections
- Accepting client connections
- Sending and receiving raw bytes
- Successfully communicates with modern browsers

### 🚧 HTTP Layer

- Request parsing *(In Progress)*
- Response generation *(Planned)*
- Static file serving *(Planned)*
- MIME type detection *(Planned)*
- Persistent connections *(Planned)*

---

## Project Structure

```
RahulHTTP/
│
├── include/
│   ├── server.h
│   ├── http.h
│   └── file.h
│
├── src/
│   ├── main.c
│   ├── server.c
│   ├── http.c
│   └── file.c
│
├── public/
│   └── index.html
│
├── README.md
```

---

## Build

```bash
gcc src/*.c -Iinclude -Wall -Wextra -g -o RahulHTTP
```

Run

```bash
./RahulHTTP
```

Open your browser and visit

```
http://localhost:6767
```

---

## Technologies

- C
- Linux
- POSIX Socket APIs
- GCC

---

## Learning Objectives

This project focuses on understanding the complete path of an HTTP request:

```
Browser
    ↓
TCP Connection
    ↓
Linux Kernel
    ↓
Socket API
    ↓
HTTP server
    ↓
HTTP Parsing
    ↓
Response Generation
    ↓
Browser Rendering
```

---

## Roadmap

- [x] TCP server
- [x] Browser connection
- [x] Receive HTTP requests
- [ ] HTTP parser
- [ ] HTTP response generator
- [ ] Static website hosting
- [ ] CSS & JavaScript support
- [ ] MIME type detection
- [ ] 404 responses
- [ ] Keep-Alive support
- [ ] Concurrent client handling

---

## License

This project is built for learning systems programming and computer networking.
