# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -Wall -Wextra -pthread -g -lprofiler

default: build

build: lab2_list

lab2_list: SortedList.c lab2_list.c
	$(CC) $(CFLAGS) SortedList.c lab2_list.c -o $@

tests:
# clear the output file
	-rm lab2b_list.csv
# tests for test #1
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2b_list.csv
# tests for test #3
	-./lab2_list --lists=4 --threads=1 --iterations=1 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=1 --iterations=2 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=1 --iterations=4 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=1 --iterations=8 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=1 --iterations=16 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=4 --iterations=1 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=4 --iterations=2 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=4 --iterations=4 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=4 --iterations=8 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=4 --iterations=16 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=8 --iterations=1 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=8 --iterations=2 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=8 --iterations=4 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=8 --iterations=8 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=8 --iterations=16 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=12 --iterations=1 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=12 --iterations=2 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=12 --iterations=4 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=12 --iterations=8 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=12 --iterations=16 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=16 --iterations=1 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=16 --iterations=2 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=16 --iterations=4 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=16 --iterations=8 --yield=id >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=16 --iterations=16 --yield=id >> lab2b_list.csv
# more tests for ensuring no errors with synchronization
	./lab2_list --lists=4 --threads=1 --iterations=10 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=1 --iterations=20 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=1 --iterations=40 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=1 --iterations=80 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=10 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=20 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=40 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=80 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=10 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=20 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=40 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=80 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=10 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=20 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=40 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=80 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=10 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=20 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=40 --yield=id --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=80 --yield=id --sync=s >> lab2b_list.csv
#sync with mutexes instead of spin locks
	./lab2_list --lists=4 --threads=1 --iterations=10 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=1 --iterations=20 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=1 --iterations=40 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=1 --iterations=80 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=10 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=20 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=40 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=80 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=10 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=20 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=40 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=80 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=10 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=20 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=40 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=80 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=10 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=20 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=40 --yield=id --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=16 --iterations=80 --yield=id --sync=m >> lab2b_list.csv
# tests for graphs 4 and 5
	./lab2_list --lists=4 --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=8 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=16 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --lists=4 --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=4 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=8 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --lists=16 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	cp lab2b_list.csv lab2_list.csv

profile:
	touch gpprof.prof
	CPUPROFILE=gpprof.prof ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text lab2_list gpprof.prof > profile.out
	pprof --list=manipulateThreads lab2_list gpprof.prof >> profile.out
	rm gpprof.prof

graphs:
	./lab2_list.gp

dist: default tests graphs profile
	tar -z -cf lab2b-204747283.tar.gz SortedList.h SortedList.c lab2_list.c Makefile *.csv *.png *.gp README profile.out

clean:
	rm -f *.o *.so *.tar.gz lab2_list
