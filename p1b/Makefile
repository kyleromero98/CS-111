# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -lz -Wall -Wextra

default: lab1b-client lab1b-server

lab1b-client: lab1b-client.c
	$(CC) $(CFLAGS) lab1b-client.c -o $@

lab1b-server: lab1b-server.c
	$(CC) $(CFLAGS) lab1b-server.c -o $@

dist:
	@tar -z -cf lab1b-204747283.tar.gz lab1b-client.c lab1b-server.c Makefile README

clean:
	rm -f *.o *.so *.tar.gz lab1b-client lab1b-server 
