/***************************************************
*                                                  *
*  allocation.c                                    *
*  fonctions facilitant l'utilisation des mallocs  *
*  Auteur : Hugo Mohamed                           *
*  Date de création : 06/02/2018                   *
*                                                  *
***************************************************/

#ifndef ALLOCATION_C
#define ALLOCATION_C

#include "allocation.h"

void * allocation_mem(size_t nobjets,size_t taille)
{
    void * pt;
    pt = malloc(taille * nobjets);

    // On test si la mémoire à été allouée
    if(pt == NULL)
    {
	fprintf(stderr,"Erreur : impossible d'allouer la mémoire %d * %d\n",nobjets,taille);
	exit(EXIT_FAILURE);
    }

    return pt;
}

void * allocation_mem_init0(size_t nobjets,size_t taille)
{
    void * pt;
    pt = calloc(nobjets,taille);

    // On test si la mémoire à été allouée
    if(pt == NULL)
    {
	fprintf(stderr,"Erreur : impossible d'allouer la mémoire %d * %d\n",nobjets,taille);
	exit(EXIT_FAILURE);
    }

    return pt;
}

void* reallocation_mem(void **pt, size_t nobjets,size_t taille)
{
    void *pt_realloc = realloc(*pt, nobjets * taille);

    if (pt_realloc != NULL)
	*pt = pt_realloc;
    else
    {
	fprintf(stdout,"Impossible de reallouer la memoire %d * %d a l’adresse %p\n",nobjets,taille,*pt);
	exit(EXIT_FAILURE);
    }
    
    return pt_realloc;
}

void libere_mem(void *pt)
{
    void ** adr_pt=(void **) pt;
    if((*adr_pt)!=NULL)
	free(*adr_pt); /*liberation de *pt */
    *adr_pt=NULL; /* *pt pointe maintenant sur NULL, cad rien*/
}

#endif
