#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "file.h"
#include "MLV/MLV_all.h"

void affichage(liste l);

int main(int argc, char *argv[])
{
    liste l = liste_vide();
    pile p = pile_vide();
    file f = file_vide();
    int i,n;
    for(i=1;i<argc;i++)
    {
	n = atoi(argv[i]);
	l = inserer_element_liste(l,n);
	p = empiler(p,n);
	f = enfiler(f,n);
    }

    fprintf(stdout,"Après insertion des éléments, on a :\n");

    fprintf(stdout,"Liste :\n");
    affichage(l);
    fprintf(stdout,"A pour premier élément %d\n", renvoie_premier_liste(l));
    l = supprimer_premier_liste(l);
    fprintf(stdout,"Apres suppression du premier élément :\n");
    affichage(l);
    printf("\n");

    fprintf(stdout,"Pile :\n");
    affichage(p);
    fprintf(stdout,"A pour premier élément %d\n", sommet(p));
    p = depiler(p);
    fprintf(stdout,"Apres suppression du premier élément :\n");
    affichage(l);
    printf("taille = %d\n",taille_pile(p));
    printf("\n");

    fprintf(stdout,"file :\n");
    affichage(f);
    fprintf(stdout,"A pour premier élément %d\n", debut_file(f));
    f = defiler(f);
    fprintf(stdout,"Apres suppression du premier élément :\n");
    affichage(l);
    printf("taille = %d\n", taille_file(f));

    exit(EXIT_SUCCESS);
}

void affichage(liste l)
{
    while(l)
    {
	fprintf(stdout,"%d ",l->objet);
	l = l->suivant;
    }
    
    fprintf(stdout,"\n");
}
