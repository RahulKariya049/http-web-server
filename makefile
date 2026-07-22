Build:
	gcc -Wall src/main.c src/server.c src/parser.c src/static.c src/response.c -Iinclude -o RahulHTTP

Run:
	./RahulHTTP