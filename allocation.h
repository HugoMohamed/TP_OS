/**********************************
*                                 *
*  allocation.h                   *
*  header de allocation.c         *
*  Auteur : Hugo Mohamed          *
*  Date de création : 06/02/2018  *
*                                 *
**********************************/

#ifndef ALLOCATION_H
#define ALLOCATION_H

#include <stdio.h>
#include <stdlib.h>

// comme un malloc mais avec test si la mémoire a bien été allouée.
void * allocation_mem(size_t nobjets,size_t taille);

// alloc_mem version avec calloc
void * allocation_mem_init0(size_t nobjets,size_t taille);

// Version avec realloc
void * reallocation_mem(void **pt, size_t nobjets,size_t taille);

// fonction de libération
void libere_mem(void *pt);
#endif
