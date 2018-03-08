CC = gcc
CFLAGS = -g -Wall -Wextra
files = lab3a.c ext2_fs.h Makefile README

default:
	$(CC) $(CFLAGS) -o lab3a lab3a.c

dist: default
	tar -czf lab3a-904771873.tar.gz $(files)

clean:
	rm -f lab3a *.o *.txt *.tar.gz
