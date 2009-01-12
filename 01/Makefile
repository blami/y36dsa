all: test

seznam.o: seznam.c seznam.h
	gcc -c seznam.c -Wall -DDEBUG=1

test: test.c seznam.o
	gcc -o test seznam.o test.c -Wall -DDEBUG=1

clean:
	-rm -f *.o
	-rm test
