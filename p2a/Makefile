# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -g -Wall -Wextra -pthread

default: build

build: lab2_add lab2_list

lab2_add: lab2_add.c
	$(CC) $(CFLAGS) lab2_add.c -o $@

lab2_list: SortedList.c lab2_list.c
	$(CC) $(CFLAGS) SortedList.c lab2_list.c -o $@

tests:
# clear the output file
	-rm lab2_add.csv
# add-none tests
	./lab2_add --threads=1 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 >> lab2_add.csv
#add-m tests
	./lab2_add --threads=1 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=m >> lab2_add.csv
#add-s tests
	./lab2_add --threads=1 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=250 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=500 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=250 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=500 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=250 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=500 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=250 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=500 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=250 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=500 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=s >> lab2_add.csv
#add-c tests
	./lab2_add --threads=1 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=c >> lab2_add.csv
# add-yield-none tests
	./lab2_add --threads=1 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield >> lab2_add.csv
# add-yield-m tests
	./lab2_add --threads=1 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield --sync=m >> lab2_add.csv	
# add-yield-s tests
	./lab2_add --threads=1 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=250 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=500 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=250 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=500 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=250 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=500 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=250 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=500 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=250 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=500 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=s >> lab2_add.csv
# add-yield-c tests
	./lab2_add --threads=1 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield --sync=c >> lab2_add.csv
# clear output file
	-rm lab2_list.csv
# list-none-none
	-./lab2_list --threads=1 --iterations=10 >> lab2_list.csv
	-./lab2_list --threads=1 --iterations=100 >> lab2_list.csv
	-./lab2_list --threads=1 --iterations=1000 >> lab2_list.csv
	-./lab2_list --threads=1 --iterations=10000 >> lab2_list.csv
	-./lab2_list --threads=1 --iterations=20000 >> lab2_list.csv	
# list-none-none
	-./lab2_list --threads=2 --iterations=1 >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=10 >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=100 >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=1000 >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=1 >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=10 >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=100 >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=1000 >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=1 >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=10 >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=100 >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=1000 >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=1 >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=10 >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=100 >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=1000 >> lab2_list.csv
# list-i-none
	-./lab2_list --threads=2 --iterations=1 --yield=i >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=2 --yield=i >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=i >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=i >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=i >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=i >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=1 --yield=i >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=i >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=i >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=i >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=i >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=i >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=1 --yield=i >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=i >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=i >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=i >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=i >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=i >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=1 --yield=i >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=i >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=i >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=i >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=i >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=i >> lab2_list.csv
# list-d-none
	-./lab2_list --threads=2 --iterations=1 --yield=d >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=2 --yield=d >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=d >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=d >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=d >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=d >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=1 --yield=d >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=d >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=d >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=d >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=d >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=d >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=1 --yield=d >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=d >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=d >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=d >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=d >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=d >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=1 --yield=d >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=d >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=d >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=d >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=d >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=d >> lab2_list.csv
# list-il-none
	-./lab2_list --threads=2 --iterations=1 --yield=il >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=2 --yield=il >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=il >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=il >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=il >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=il >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=1 --yield=il >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=il >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=il >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=il >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=il >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=il >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=1 --yield=il >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=il >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=il >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=il >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=il >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=il >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=1 --yield=il >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=il >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=il >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=il >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=il >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=il >> lab2_list.csv
# list-dl-none
	-./lab2_list --threads=2 --iterations=1 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=2 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=4 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=8 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=16 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=2 --iterations=32 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=1 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=4 --iterations=32 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=1 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=8 --iterations=32 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=1 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=dl >> lab2_list.csv
	-./lab2_list --threads=12 --iterations=32 --yield=dl >> lab2_list.csv
# list-i-m
	./lab2_list --threads=2 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=i --sync=m >> lab2_list.csv
# list-d-m
	./lab2_list --threads=2 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=d --sync=m >> lab2_list.csv
# list-il-m
	./lab2_list --threads=2 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> lab2_list.csv
# list-dl-m
	./lab2_list --threads=2 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
# list-i-s
	./lab2_list --threads=2 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=i --sync=s >> lab2_list.csv
# list-d-s
	./lab2_list --threads=2 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=d --sync=s >> lab2_list.csv
# list-il-s
	./lab2_list --threads=2 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> lab2_list.csv
# list-dl-s
	./lab2_list --threads=2 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
# list-none-m
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2_list.csv
# list-none-s
	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2_list.csv

graphs:
	./lab2_add.gp
	./lab2_list.gp

dist: default tests graphs
	tar -z -cf lab2a-204747283.tar.gz lab2_add.c SortedList.h SortedList.c lab2_list.c Makefile *.csv *.png *.gp README

clean:
	rm -f *.o *.so *.tar.gz lab2_add lab2_list
