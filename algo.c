/**********************************
 *                                *
 *  Algorithmes de remplacements  *
 *  de page                       *
 *                                *
 *********************************/

#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void usage(char* s);

int main(int argc, char* argv[])
{
    if(argc < 5)
	usage(argv[0]);
    
    int algo = atoi(argv[1]);
    int caseRAM = atoi(argv[2]);
    int affichage = atoi(argv[3]);
    
    FILE* acces_mem = fopen(argv[4],"r");
    if(acces_mem == NULL)
    {
	fprintf(stderr,"Erreur lors de l'ouverture de <<%s>> :\nFichier introuvable.\n",argv[4]);
	exit(EXIT_FAILURE);
    }

    int nbPage;
    int *acces;
    int *valide;
    int *b_acces;
    liste pageRAM = liste_vide();
    int i = 0;
    int j;
    int page;
    char* ligne;

    fgets(ligne,10,acces_mem);
    nbPage = atoi(ligne);

    // FIFO
    if(algo == 1)
    {
	// on alloue le nombre de cases mémoire
	acces = (int*)malloc(caseRAM * sizeof(int));
        valide = (int*)malloc(nbPage * sizeof(int));
	if(acces == NULL)
	{
	    fprintf(stderr,"Erreur lors de l'allocation mémoire.\n");
	    exit(EXIT_FAILURE);
	}

	// on parcours le fichier des acces mémoire
	while(fgets(ligne,10,acces_mem) != NULL)
	{
	    // on insere la page dans la liste
	    pageRAM = enfiler(pageRAM,page);
	    i++;

	    // Si on doit remplacer la page
	    if(i >= caseRAM)
	    {
	        for(j = 0; j < caseRAM; j++)
		{
		    if(acces[j] == debut_file(pageRAM))
		    {
			acces[j] = page;
			
			valide[renvoie_premier_liste(pageRAM)] = 0;
			pageRAM = supprimer_premier_liste(pageRAM);
		    }
		}
	    }
	    else
		acces[i] = page;
	}
    }

    // LRU
    else if(algo == 2)
    {

    }

    // Horloge
    else if(algo == 3)
    {

    }

    // optimal
    else if(algo == 4)
    {

    }

    for(j=0;j<caseRAM;i++)
    {
	fprintf(stdout,"%d ", acces[j]);
    }

    exit(EXIT_SUCCESS);
}


void usage(char* s)
{
    fprintf(stderr,"Usage : %s <numéro algo> <nb case RAM> <mode affichage> <fichier acces>\n",s);
    fprintf(stderr,"Algo :\n    1) FIFO\n    2) LRU\n    3) Horloge\n    4) Optimal\n");
    fprintf(stderr,"Mode affichage :\n    d: debug\n    c: classique\n");

    exit(EXIT_FAILURE);
}
