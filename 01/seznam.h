/*
 *  seznam.h
 *  Abstraktni datovy typ - spojovy seznam se zarazkami
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 1
 *  Datum: 04.11.2008
 */
#ifndef __SEZNAM_H
#define __SEZNAM_H


/** Struktura nesouci jeden prvek seznamu. Obsahuje refernci na dalsi prvek a
 *  ukazatel na data (void*) aby byl seznam opravdu abstraktni */
typedef
struct _t_prvek
{
	void*               data;
	struct _t_prvek*    dalsi;
} t_prvek;


/** Struktura zapouzdrujici jednu "instanci" seznamu. Obsahuje ukazatele na
 *  aktualni, prvni a posledni prvek a informaci o poctu prvku. */
typedef
struct _t_seznam
{
	t_prvek*            prvni;
	t_prvek*            posledni;
	t_prvek*            kurzor;
	int                 pocet;
} t_seznam;


/*
 *  Funkce pro praci s vyse uvedenymi strukturami.
 */
extern t_seznam*    seznam_init();
extern int          seznam_empty(t_seznam*);
extern void         seznam_delete(t_seznam*);
extern void         seznam_first(t_seznam*);
extern void         seznam_last(t_seznam*);
extern void         seznam_next(t_seznam*);
extern void         seznam_prev(t_seznam*);
extern void         seznam_insert(t_seznam*, void*);


#endif /* __SEZNAM_H */
