all: test

sort.o: sort.c sort.h
	gcc -c sort.c -Wall

test: test.c sort.o
	gcc -o test sort.o test.c -Wall

clean:
	-rm -f *.o
	-rm test
