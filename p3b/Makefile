FILE=P3B-test
files = lab3b.py Makefile README

default:
	ln -s lab3b.py lab3b

dist: clean default
	tar -czf lab3b-904771873.tar.gz $(files)

tests:
	for i in $(shell seq 1 22); do echo $(FILE)_$${i} >> check & ./lab3b test/csv/$(FILE)_$${i}.csv >> check; done

clean:
	rm -f lab3b *.o *.txt *.tar.gz
