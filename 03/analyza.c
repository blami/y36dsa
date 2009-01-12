/*
 *  analyza.c
 *  Analyza pozic cifer v souboru klice_in.txt
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 3
 *  Datum: 10.1.2008
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int cetnosti[6][10]; // pole cetnosti

int
main(int argc, char* argv[])
{
	FILE *f;
	char buf[8];

	// vynuluju pole
	int i,j;
	for(i = 0; i<6; i++)
		for(j = 0; j<10; j++)
			cetnosti[i][j] = 0;


	f = fopen("./klice_in.txt", "r");

	while(!feof(f))
	{
		fgets(buf, 8, f);
		for(i=0; i<6; i++)
		{
			switch(buf[i])
			{
			case '0':
				cetnosti[i][0]++;
				break;
			case '1':
				cetnosti[i][1]++;
				break;
			case '2':
				cetnosti[i][2]++;
				break;
			case '3':
				cetnosti[i][3]++;
				break;
			case '4':
				cetnosti[i][4]++;
				break;
			case '5':
				cetnosti[i][5]++;
				break;
			case '6':
				cetnosti[i][6]++;
				break;
			case '7':
				cetnosti[i][7]++;
				break;
			case '8':
				cetnosti[i][8]++;
				break;
			case '9':
				cetnosti[i][9]++;
				break;
			}
		}
	}
	fclose(f);

	// vypisu napocitane cetnosti
	for(i = 0; i<6; i++)
	{
		printf("Pozice %i: ", i+1);
		for(j = 0; j<10; j++)
			printf("%i:%3i ", j, cetnosti[i][j]);

		printf("\n");
}
	return 1;
}
