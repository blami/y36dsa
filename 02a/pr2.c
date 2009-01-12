#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_DELKA 25.0
#define MAX_HODNOTA 100.0

typedef
struct _t_prvek
{
	int data;
	struct _t_prvek* dalsi;
} t_prvek;


// globalni promenne
t_prvek* hlava = NULL;


t_prvek*
seznam_vloz(int data)
{
	t_prvek *p = malloc(sizeof(t_prvek));
	p->data = data;
	p->dalsi = NULL;

	if(hlava == NULL)
		hlava = p;
	else
	{
		t_prvek *i;
		for(i = hlava; i; i = i->dalsi) 
		{
			if(!i->dalsi)
				break;
		}

		i->dalsi = p;
	}

	return p;
}


void
seznam_vypis_bc()
{
	t_prvek* i;
	printf("Seznam bez cyklu: {");
	for(i = hlava; i; i = i->dalsi)
	{
		printf("%d", i->data);
		if(i->dalsi)
			printf("->");
	}
	printf("}\n");
}


int
seznam_delka_c()
{
	if(!hlava)
		return 0;

	int n = 0; // delka do zacatku cyklu
	int k = 0; // delka cyklu
	int i = 0; // pomocna promenna

	// iteratory
	t_prvek* p = hlava;
	t_prvek* r1 = hlava;
	t_prvek* r2 = hlava;

	while((p != NULL) && // pomaly iterator
		((r1 = r2->dalsi) && (r2 = r1->dalsi))) // rychly iterator
	{
		if(p == r1 || p == r2)
			break;

		p = p->dalsi;
	}

	// p je ukazatel na prvek kde se iteratory protly
	// zmerim delku cyklu
	k++;
	r1 = p->dalsi;
	while(r1 != p)
	{
		r1 = r1->dalsi;
		k++;
	}
	printf("Delka cyklu je: %d\n", k);

	// najdu zacatek cyklu
	r1 = hlava;
	r2 = hlava;
	for(i=0; i<k; i++)
		r1 = r1->dalsi;

	while(r1 != r2)
	{
		r1 = r1->dalsi;
		r2 = r2->dalsi;
	}
	p = r1;

	// spocitam prvky do zacatku cyklu
	r1 = hlava;
	while(r1 != p)
	{
		r1 = r1->dalsi;
		n++;
	}

	return n+k;
}


int
main(int argc, char** argv)
{

	// Generovani nahodne dlouheho seznamu:
	t_prvek* posl;
	srand((unsigned int)time(NULL));

	int pocet = 1 + (int)(MAX_DELKA * rand() / (RAND_MAX + 1.0));
	printf("Seznam delky: %d\n", pocet);

	int i;
	for(i=0; i<pocet; i++)
	{
		posl = seznam_vloz(i);
	}

	seznam_vypis_bc();

	// Umisteni reference posl->{nahodny}
	int poz_nahodny = (int)(rand() / (((double)RAND_MAX + 1) / pocet));

	t_prvek* p;
	i = 0;
	for(p = hlava; p; p = p->dalsi, i++)
	{
		if(i == poz_nahodny)
			break;
	}

	posl->dalsi = p;
	printf("Prvek posl->dalsi je na pozici: %d (obsah: {%d})\n", poz_nahodny, p->data);

	int c_pocet = seznam_delka_c();
	printf("Pocet prvku v cyklickem seznamu je: %d\n", c_pocet);

	return 0;
}
