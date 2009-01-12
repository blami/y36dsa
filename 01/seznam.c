/*
 *  seznam.c
 *  Abstraktni datovy typ - spojovy seznam se zarazkami
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 1
 *  Datum: 04.11.2008
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "seznam.h"


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
 *                        FUNKCE PRO PRACI SE SEZNAMEM
 * -------------------------------------------------------------------------- */


//  po:
//  {[(null)] -> (null)}
//
/** Vytvori novy seznam. Naalokuje strukturu seznamu, prida zarazky v podobe
 *  prazdnych prvku na zacatek a konec a nastavi pocet prvku na 0. Vraci 
 *  ukazatel na strukturu seznamu.
 *  @return t_seznam*       ukazatel na vytvoreny seznam */
t_seznam*
seznam_init()
{
	t_seznam*   s;
	t_prvek*    p;

	s = xmalloc(sizeof(t_seznam));

	// zarazka na konci
	p = xmalloc(sizeof(t_prvek));
	p->data = NULL;
	p->dalsi = NULL;
	s->posledni = p;

	// zarazka na pocatku
	p = xmalloc(sizeof(t_prvek));
	p->data = NULL;
	p->dalsi = s->posledni;
	s->prvni = p;

	s->kurzor = s->prvni;

	s->pocet = 0;

	return s;
}


/** Vrati 1 pokud je seznam prazdny (obsahuje jen zarazky) v jinem pripade vrati
 *  0 (seznam obsahuje alespon jeden prvek).
 *  @param t_seznam* s      ukazatel na existujici seznam
 *  @return int             1 prazdny, 0 plny */
int
seznam_empty(t_seznam* s)
{
	if(!s)
		error(-1, "seznam neni zinicializovan");

	if(s->pocet == 0)
		return 1;

	return 0;
}


//  pred:                                   po:
//  {(null) -> [a] -> b -> (null)}          {(null) -> b -> (null)}
//
/** Vymaze prvek na ktery ukazuje kurzor (pokud nejde o zarazku). Kurzor je
 *  nastaven na dalsi prvek. Mazani v jednoprvkovem seznamu vzdy konci na zadni
 *  zarazce. Pokud je seznam nast
 *  @param t_seznam* s      ukazatel na existujici seznam */
void
seznam_delete(t_seznam *s)
{
	t_prvek* p;

	if(!s)
		error(-1, "seznam neni zinicializovany");

	if(s->kurzor == s->prvni || s->kurzor == s->posledni)
	{
		debug("pokus o vymazani zarazky");
		return;
	}

	// do p ulozime ukazatel na predchozi prvek
	for(p = s->prvni; p->dalsi != s->kurzor; p = p->dalsi)
		;
	// opravime seznam (vynechame kurzor), diky zarazkam bude vzdy fungovat
	p->dalsi = s->kurzor->dalsi;
	xfree(s->kurzor);

	// opravime pozici kurzoru
	s->kurzor = p->dalsi;

	// opravime pocet prvku
	s->pocet--;

	debug("vymazan prvek");
	debug("pocet prvku v seznamu je nyni: %d", s->pocet);
}


//  pred:                                   po:
//  {(null) -> a -> [b] -> (null)}          {[(null)] -> a -> b -> (null)}
//
/** Premisti kurzor na pocatek seznamu (nastavi na predni zarazku). Vyuzivame
 *  vlastnosti spojoveho seznamu se zarazkou v hlave - ta se nikdy nemeni a vzdy
 *  existuje - proto vime ze na ni bezpecne kdykoliv muzeme nastavit kurzor.
 *  @param t_seznam* s      ukazatel na existujici seznam */
void
seznam_first(t_seznam *s)
{
	if(!s)
		error(-1, "seznam neni zinicializovany");

	s->kurzor = s->prvni;
	debug("kurzor byl nastaven na predni zarazku");
}


//  pred:                                   po:
//  {[(null)] -> a -> b -> (null)}          {(null) -> a -> b -> [(null)]}
//
/** Premisti kurzor na konec seznamu (nastavi na zadni zarazku). Opet vyuzivame
 *  vlastnosti spojoveho seznamu se zarazkou, tentokrat v pate. Tez vime ze bude
 *  vzdy k dispozici a proto na ni muzeme kurzor primo nastavit.
 *  @param t_seznam* s      ukazatel na existujici seznam */
void
seznam_last(t_seznam *s)
{
	if(!s)
		error(-1, "seznam neni zinicializovany");

	s->kurzor = s->posledni;
	debug("kurzor byl nastaven na zadni zarazku");
}


//  pred:                                   po:
//  {(null) -> a -> [b] -> (null)}          {(null) -> a -> b -> [(null)]}
//
/** Posune kurzor na dalsi prvek, v pripade ze jiz neni na zadni zarazce.
 *  Nastavi kurzor na dalsi aktualniho kurzoru.
 *  @param t_seznam* s      ukazatel na existujici seznam */
void
seznam_next(t_seznam *s)
{
	if(!s)
		error(-1, "seznam neni zinicializovany");

	if(s->kurzor != s->posledni)
	{
		s->kurzor = s->kurzor->dalsi;
		debug("kurzor byl posunut na dalsi prvek");
	}
	else
		debug("kurzor nebyl posunut (je jiz na zadni zarazce)");
}


//  pred:                                   po:
//  {(null) -> a -> [b] -> (null)}          {(null) -> [a] -> b -> (null)}
//
/** Posune kurzor na predchozi prvek v pripade ze jiz neni na hlave. Zjisteni
 *  predchoziho prvku je provedeno cyklickym projitim seznamu od pocatecni
 *  zarazky k prvku jehoz dalsi je kurzor.
 *  @param t_seznam* s      ukazatel na existujici seznam */
void
seznam_prev(t_seznam *s)
{
	if(!s)
		error(-1, "seznam neni zinicializovany");

	if(s->kurzor != s->prvni)
	{
		t_prvek* p;
		for(p = s->prvni; p->dalsi != s->kurzor; p = p->dalsi)
			;
		s->kurzor = p;
		debug("kurzor byl posunut na predchozi prvek");
	}
	else
		debug("kurzor nebyl posunut (je jiz na predni zarazce)");
}


//  pred:                                   po:
//  {(null) -> a -> [b] -> (null)}          {(null) -> a -> c -> [b] -> (null)}
//  {[(null)] -> a -> (null)}               {[(null)] -> X -> a -> (null)}
//
/** Vlozi prvek do seznamu na pozici pred kurzor a kurzor ponecha tam kde "je"
 *  (na prvku). V seznamu jsou vzdy minimalne dva specialni elementy - zarazky.
 *  Specialni pripad je vkladani na zacatek seznamu, kdyz je kurzor nastaven na
 *  predni zarazku - musi probehnout vlozeni za ni (coz ne uplne odpovida
 *  semantice pokud zarazku povazujeme za bezny prvek) a pozice kurzoru se
 *  nezmeni.
 *  @param t_seznam* s      ukazatel na existujici seznam
 *  @param void* data       ukazatel na data vkladaneho elementu */
void
seznam_insert(t_seznam* s, void* data)
{
	if(!s)
		error(-1, "seznam neni zinicializovan");

	t_prvek* p = xmalloc(sizeof(t_prvek));

	// zacatek seznamu (specialni pripad)
	if(s->kurzor == s->prvni)
	{
		p->data = data;
		p->dalsi = s->prvni->dalsi;
		s->prvni->dalsi = p;
		debug("pridan prvek na zacatek seznamu");
	}
	// neprazdny seznam nebo konec seznamu (odpovida semantice)
	else
	{
		p->data = s->kurzor->data;
		p->dalsi = s->kurzor->dalsi;
		s->kurzor->data = data;
		s->kurzor->dalsi = p;
		s->kurzor = p;
		debug("pridan prvek na konec/do tela seznamu");
	}

	// zvysit pocet prvku o jeden
	s->pocet++;
	debug("pocet prvku v seznamu je nyni: %d", s->pocet);
}
