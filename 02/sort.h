/*
 *  radix.h
 *  Stabilni O(n) razeni v [0, n^2]
 *
 *  Autor: Ondrej Balaz <balazo1@fel.cvut.cz>
 *  Predmet: YD36DSA
 *  Uloha: 2
 *  Datum: 10.12.2008
 */
#ifndef __RADIX_H
#define __RADIX_H

void* xmalloc(size_t n);
void xfree(void* ptr);

void sort(long orig[] , size_t n, long max_val);

#endif /* __RADIX_H */
