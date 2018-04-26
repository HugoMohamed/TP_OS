#ifndef FILE_C
#define FILE_C

#include "file.h"

file file_vide()
{
    return liste_vide();
}

int est_file_vide(file f)
{
    return est_liste_vide(f);
}

file enfiler(file f, element e)
{
    liste lnew = inserer_element_liste(liste_vide(),e);
    liste lcourant = f;

    if(est_file_vide(f))
	return lnew;

    while(lcourant->suivant != liste_vide())
    {
	lcourant = lcourant->suivant;
    }

    lcourant->suivant = lnew;

    return f;
}

element debut_file(file f)
{
    return renvoie_premier_liste(f);
}

file defiler(file f)
{
    return supprimer_premier_liste(f);
}

int taille_file(file f)
{
    int n = 0;
    liste lcourant = f;

    while(lcourant)
    {
	n++;
	lcourant = lcourant->suivant;
    }

    return n;
}

#endif
