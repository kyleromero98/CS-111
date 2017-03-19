# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -Wall -Wextra -g -lmraa -lm

default: lab4b

lab4b: lab4b.c
	$(CC) $(CFLAGS) lab4b.c -o $@

check:
# first test for log file
	@echo "Checking for correct log file..."
	@{ echo "START"; echo "SCALE=C"; echo "OFF"; } | ./lab4b --log=log.txt
	@echo "Printing log contents..."
	@cat log.txt
	@rm log.txt
# second test for scale option and start/stop
	@echo "Checking for scale option..."
	@{ sleep 4; echo "STOP"; sleep 4; echo "START"; sleep 4; echo "OFF"; } | ./lab4b --scale=C
# third test for period option and scale in stdin
	@echo "Checking for period change and scale change in middle..."
	@{ sleep 4; echo "SCALE=C"; sleep 4; echo "SCALE=F"; sleep 4; echo "OFF"; } | ./lab4b --period=2
# fourth test for period during stdin
	@echo "Testing for period change of 2..."
	@{ sleep 4; echo "PERIOD=2"; sleep 4; echo "OFF"; } | ./lab4b

clean:
	rm -f *.o *.so *.tar.gz lab4b

dist:
	tar -z -cf lab4b-204747283.tar.gz lab4b.c README Makefile
