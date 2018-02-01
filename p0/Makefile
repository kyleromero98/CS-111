# NAME: Kyle Romero
# Email: kyleromero98@gmail.com
# ID: 204747283

CC = gcc
CFLAGS = -g -Wall -Wextra

default: lab0

lab0: lab0.c
	$(CC) $(CFLAGS) lab0.c -o $@

dist:
	@tar -z -cf lab0-204747283.tar.gz lab0.c Makefile backtrace.png breakpoint.png README
	@echo "Successfully packaged for dist"

check: lab0
	@rm -f *.txt
#first test for --input and --output functionality
	@echo hello > hello.txt
	@./lab0 --input=hello.txt --output=output.txt
	@cmp --silent hello.txt output.txt  || (echo "FAILED test #1 for --input functionality" && exit 1)
	@rm hello.txt; rm output.txt
#second test for --segfault and --catch functionality
	-@echo hello | ./lab0 --segfault --catch &> output.txt
	@echo SIGSEGV Error: Successful --catch option > test.txt
	@cmp --silent test.txt output.txt || (echo "FAILED test #2 for --segfault and --catch functionality" && exit 1)
	@rm output.txt; rm test.txt
#third test for invalid --input file
	-@echo hi there | ./lab0 --input=hllo.txt &> output.txt
	@echo IO Error: Unable to open hllo.txt for --input: No such file or directory > test.txt
	@cmp --silent test.txt output.txt || (echo "FAILED test #3 for invalid --input file" && exit 1)
	@rm output.txt; rm test.txt
#fourth test for invalid argument
	-@echo hi there | ./lab0 --badarg &> output.txt
	@printf "./lab0: unrecognized option '--badarg'\nOption Error: Invalid option found. Valid options: --input= --output= --segfault --catch\n Correct usage: ./lab0 --segfault --catch --input=input.txt --output=output.txt\n"> test.txt
	@cmp --silent test.txt output.txt || (echo "FAILED test #4 for invalid option passed" && exit 1)
	@rm output.txt; rm test.txt
# fifth test for unsuccessful --output because of duplicate file
	@echo hi there > hello.txt
	@chmod 000 hello.txt
	-@echo hi there | ./lab0 --output=hello.txt &> output.txt
	@printf "IO Error: Unable to open hello.txt for --output: Permission denied\n" > test.txt
	@cmp --silent test.txt output.txt || (echo "FAILED test #5 for IO output error" && exit 1)
	@chmod 777 hello.txt
	@rm test.txt; rm output.txt; rm hello.txt 
	@echo "Success 5 out of 5 tests passed." 

clean:
	rm -f *.o *.so *.tar.gz lab0 
