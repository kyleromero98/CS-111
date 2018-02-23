# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -Wall -Wextra -g -lmraa

default: lab4b

lab4b: lab4b.c
	$(CC) $(CFLAGS) lab4b.c -o $@

check:

clean:
	rm -f *.o *.so *.tar.gz lab4b

dist:
	tar -z -cf lab4b-204747283.tar.gz lab4b.c README Makefile
