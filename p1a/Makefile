# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -Wall -Wextra

default: lab1a

lab1a: lab1a.c
	$(CC) $(CFLAGS) lab1a.c -o $@

dist:
	@tar -z -cf lab1a-204747283.tar.gz lab1a.c Makefile README
	@echo "Successfully packaged for dist"

clean:
	rm -f *.o *.so *.tar.gz lab1a 
