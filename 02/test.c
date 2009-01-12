/*
 *  test.c
 *  Jednotkovy test
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 2
 *  Datum: 10.12.2008
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"


long*
rand_array(size_t n)
{
	long *r;
	int i;

	r = xmalloc(n * sizeof(long));

	for(i = 0; i < n; i++)
	{
		r[i] = rand() % (n*n) + 1;
	}

	return r;
}

void
print_array(const long a[], size_t n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("%ld\n", a[i]);
	}
}

double
time_diff(clock_t begin, clock_t end)
{
	double diff = end - begin;
	//diff = (diff * 10)/CLOCKS_PER_SEC;
	return diff;
}

int
main(int argc, char** argv)
{
	clock_t begin, end;
	int i, j;

	// inicializace rand posloupnosti
	srand(time(NULL));

	// testovani
	printf("n    | #  | tiky     | ms\n");
	for(i=500; i < 5500; i = i + 500)
	{
		for(j = 0; j < 10; j++)
		{
			long *a = rand_array(i);
//			print_array(a,i);

			begin = clock();
			sort(a, i, i*i);
			end = clock();

//			print_array(a,i);
			xfree(a);
			printf("%04d | %02d | %08.1f | %03.2f\n", i, j+1, time_diff(begin, end), time_diff(begin, end)*10/CLOCKS_PER_SEC);
		}
	}

	return EXIT_SUCCESS;
}
