/*
 *  phash.c
 *  Perfektni hashovaci funkce pro staticky set klicu
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 3
 *  Datum: 10.1.2008
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* hash_t[1000];

int
vrat_cislo(char zn)
{
	switch(zn)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
	}

	return -1;
}


/** Perfektni hashovaci funkce h(k) pro klic k je
 *  k[1]*100 + k[3] * 10 + k[5] * 1 */
int
h(char* klic)
{
	return (
		(vrat_cislo(klic[1]) * 100) +   // na pozici 2 jsou stovky
		(vrat_cislo(klic[3]) * 10) +    // na pozici 4 jsou desitky
		(vrat_cislo(klic[5]) * 1)       // na pozici 6 jsou jednotky
	);
}


int
main(int argc, char* argv[])
{
	FILE *f;
	char buf[8];
	int i;
	int j = 0;

	// inicializace vysledne tabulky
	for(i = 0; i < 1000; i++)
	{
		hash_t[i] = NULL;
	}

	f = fopen("./klice_in.txt", "r");

	while(fgets(buf, 8, f) != NULL)
	{
		// ziskani indexu (hashe) z klice
		i = h(buf);
		j++;

		if(!hash_t[i])
		{
			hash_t[i] = malloc(sizeof(char) * 7);
			strncpy(hash_t[i], buf, 6);
			hash_t[i][6] = '\0';
		}
		else
		{
			//buf[7] = '\0';
			printf("Radek %d: konflikt na indexu: %d ([%s] x %s)",
				j,
				i,
				hash_t[i],
				buf
			);
		}
	}
	fclose(f);

	// vypisu zahesovane klice
	printf("k:     h(k):\n");
	printf("------------\n");
	for(i = 0; i<1000; i++)
	{
		printf("%s %i\n", hash_t[i], i);
	}

	// vycisteni tabulky
	for(i = 0; i < 1000; i++)
	{
		if(hash_t[i])
			free(hash_t[i]);
	}

	return 1;
}
