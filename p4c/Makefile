# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -Wall -Wextra -g -lmraa -lm

default: lab4c_tcp lab4c_tls

lab4c_tcp: lab4c_tcp.c
	$(CC) $(CFLAGS) lab4c_tcp.c -o $@

lab4c_tls: lab4c_tls.c
	$(CC) $(CFLAGS) -lssl -lcrypto lab4c_tls.c -o $@

clean:
	rm -f *.o *.so *.tar.gz lab4c_tcp lab4c_tls

dist:
	tar -z -cf lab4c-204747283.tar.gz lab4c_tcp.c lab4c_tls.c README Makefile
