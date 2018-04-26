#ifndef PILE_H
#define PILE_H

#include "liste.h"

typedef liste pile;

// Renvoie une liste vide
pile pile_vide();

// Renvoie 1 si la liste est vide et 0 sinon
int est_pile_vide(pile p);

// Ajoute l'élément e sur le sommet de p
pile empiler(pile p,element e);

// Renvoie l'élément au sommet de p
element sommet(pile p);

// Dépile l'élément au sommet de p
pile depiler(pile p);

// Renvoie la taille de p
int taille_pile(pile p);

#endif
