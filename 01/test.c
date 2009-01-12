/*
 *  test.c
 *  Jednotkovy test
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 1
 *  Datum: 04.11.2008
 */
#include <stdio.h>
#include <stdlib.h>
#include "seznam.h"


void vypis(t_seznam*);


int
main(int argc, char** argv)
{
	int ret = 0;
	t_seznam* seznam1 = NULL;

	// inicializace
	seznam1 = seznam_init();

	printf("seznam je: %s\n", seznam_empty(seznam1) ? "prazdny" : "neprazdny");

	// naplneni
	vypis(seznam1);
	seznam_insert(seznam1, (char*)"a");
	vypis(seznam1);
	seznam_insert(seznam1, (char*)"b");
	vypis(seznam1);
	seznam_insert(seznam1, (char*)"c");
	vypis(seznam1);

	// pohyb s kurzorem vpred
	seznam_next(seznam1);
	vypis(seznam1);
	seznam_next(seznam1);
	seznam_next(seznam1);
	seznam_next(seznam1);
	seznam_next(seznam1);
	vypis(seznam1);

	printf("seznam je: %s\n", seznam_empty(seznam1) ? "prazdny" : "neprazdny");

	// pohyb s kurzorem vzad
	seznam_prev(seznam1);
	vypis(seznam1);
	seznam_prev(seznam1);
	seznam_prev(seznam1);
	seznam_prev(seznam1);
	seznam_prev(seznam1);
	vypis(seznam1);

	// vlozeni prvku do stredu seznamu
	seznam_next(seznam1);
	seznam_next(seznam1);
	vypis(seznam1);
	seznam_insert(seznam1, (char*)"X");
	vypis(seznam1);

	// mazani v seznamu
	seznam_delete(seznam1);
	vypis(seznam1);
	seznam_delete(seznam1);
	vypis(seznam1);
	seznam_delete(seznam1);
	vypis(seznam1);
	seznam_first(seznam1);
	vypis(seznam1);
	seznam_delete(seznam1);
	seznam_next(seznam1);
	vypis(seznam1);
	seznam_delete(seznam1);
	seznam_delete(seznam1);
	vypis(seznam1);

	printf("seznam je: %s\n", seznam_empty(seznam1) ? "prazdny" : "neprazdny");

	return ret;
}


// ladici vypis seznamu
void
vypis(t_seznam* s)
{
	t_prvek* p;

	printf("{");

	for(p = s->prvni; p != NULL; p = p->dalsi)
	{
		if(p == s->kurzor)
			printf("[%s]", (char*)p->data);
		else
			printf("%s", (char*)p->data);

		if(p->dalsi != NULL)
			printf("->");
	}

	printf("}\n");
}
