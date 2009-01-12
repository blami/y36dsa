all: analyza phash

analyza: analyza.c
	gcc -o analyza analyza.c -Wall -DDEBUG

phash: phash.c
	gcc -o phash phash.c -Wall -DDEBUG

clean:
	-rm -f *.o
	-rm analyza
	-rm phash
