#include "liste.h"

liste liste_vide()
{
  return NULL;
}

int est_liste_vide(liste l)
{
  if(l==liste_vide())
    return 1;
  return 0;
}

liste inserer_element_liste(liste l,element elem)
{
  liste lnew=(liste)malloc(sizeof(struct_cellule));
  lnew->objet = elem;
  lnew->suivant=l;
  return lnew;
}

liste enfiler(liste l,element elem)
{
    
    liste lnew=inserer_element_liste(liste_vide(),elem);
    liste p = l;

    if(est_liste_vide(l))
    {
	return lnew;
    }

    while(p->suivant != liste_vide())
    {
	printf("here\n");
	p = p->suivant;
    }
  
    p->suivant = lnew;

    return l;
}

element renvoie_premier_liste(liste l)
{
  if(est_liste_vide(l))
    printf("Erreur la liste est vide dans la fonction renvoie_premier\n");
  return l->objet;
}

liste supprimer_element_liste(liste l)
{
  liste lsuivant=l->suivant;
  free(l);
  return lsuivant;
}


