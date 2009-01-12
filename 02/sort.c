/*
 *  radix.c
 *  Stabilni O(n) razeni v [0, n^2]
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 2
 *  Datum: 10.12.2008
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "sort.h"


/* --------------------------------------------------------------------------
 *                                  MAKRA
 * -------------------------------------------------------------------------- */


/** Ladici makro. Ma stejnou signaturu funkce printf(), vypisuje udaj o miste
 *  volani, funkci a formatovanou chybovou hlasku.
 *  @param format           text obsahujici formatovaci sekvence (jako printf)
 *  @param arg...           argumenty (jako printf)
 *  @see printf() */
#ifdef DEBUG
#define debug(format, arg...) \
{ \
	fprintf(stderr, "debug: %s, line %4d %s():" format "\n", __FILE__, __LINE__, __func__, ##arg); \
}
#else
#define debug(format, arg...)
#endif /* DEBUG */


/** Makro ktere vypise hlasku o chybe a ukonci program.
 *  @param retval           navratova hodnota 
 *  @param fromat           text obsahujici formatovaci sekvence (jako printf)
 *  @param arg...           argumenty (jako printf)
 *  @see printf() */
#define error(retval, format, arg...) \
{ \
	perror(__func__); \
	fprintf(stderr, "error: " format "\nExiting (%d).", ##arg, retval); \
	exit(retval); \
}

/* --------------------------------------------------------------------------
 *                             POMOCNE FUNKCE
 * -------------------------------------------------------------------------- */


/** Funkce pro alokaci pameti s osetrenim chyb a reportingem.
 *  @param size_t n         velikost alokovane pameti
 *  @return void*           ukazatel na alokovany blok */
void*
xmalloc(size_t n)
{
	void* r; 
	if(!(r = malloc(n)))
		error(-1, "chyba alokace pameti");

	debug("alokovano %d bytu pameti", (int)n);
	return r;
}


/** Funkce pro uvolnovani pameti s reportingem.
 *  @param void*            ukazatel na uvolnovanou pamet */
void
xfree(void* ptr)
{
	if(!ptr)
	{
		debug("pokus o uvolneni jiz uvolnene pameti");
		return;
	}
	free(ptr);
}


/* --------------------------------------------------------------------------
 *                     IMPLEMENTACE RADICIHO ALGORITMU
 * -------------------------------------------------------------------------- */

// Zvolil jsem Counting sort protoze:
// ne radix protoze: radix trva O(Kn), kde K je pocet bitu cisla. Cisla v
// rozsahu [1, n^2] maj 2log(n) bitu. Takze celkova slozitost je O(nlogn)

/** Seradi pole orig[] tak, ze nejprve spocita pocet okurenci prvku v puvodnim
 *  poli a pak vzestupne pres tyto hodnoty prislusnymi pocty naplni vysledne
 *  pole.
 *  @param orig[]           puvodni pole (ukazatel na zacatek)
 *  @param n                delka puvodniho pole (indexace 0..n)
 *  @param max_val          maximalni hodnota prvku */
void
sort(long orig[] , size_t n, long max_val)
{
	long i;
	int j;
	int sort_pos = 0;

	// pole poctu vyskytu hodnoty
	int* count = xmalloc(sizeof(int) * max_val);
	for(i=0; i < n; i++)
	{
		count[orig[i]]++;
	}

	// presoupani vysledneho pole
	for(i=1; i <= max_val; i++)
		for(j=0; j < count[i]; j++)
		{
			orig[sort_pos] = i;
			sort_pos++;
		}

	xfree(count);
}
