/*********************************
 *                               *
 *  Algorithmes de remplacement  *
 *  de page                      *
 *                               *
 ********************************/

#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

void usage(char* s);

int main(int argc, char* argv[])
{
    if(argc < 5)
      usage(argv[0]);

    int algo = atoi(argv[1]);
    int caseRAM = atoi(argv[2]);

    FILE* acces_mem = NULL;
	acces_mem = fopen(argv[4],"r");
    if(acces_mem == NULL)
    {
		fprintf(stderr,"Erreur lors de l'ouverture de <<%s>>\n",argv[4]);
		exit(EXIT_FAILURE);
    }

    int nbPage;
	int nbAcces;
	int nbDefPage = 0;
    int *acces;
    int *valide;
    int *b_acces;
    liste pageRAM = liste_vide();
    int i = 0, k = 0;
    int j;
    int page;
    char* ligne;

    fgets(ligne,10,acces_mem);
	nbAcces = atoi(ligne);
	fgets(ligne,10,acces_mem);
    nbPage = atoi(ligne);

	// on alloue le nombre de cases mémoire
	acces = (int*)malloc(caseRAM * sizeof(int));
	valide = (int*)malloc(nbPage * sizeof(int));

	while(fgets(ligne,10,acces_mem) != NULL)
	{
		acces[k] = atoi(ligne);
		k++;
	}

    // FIFO
    if(algo == 1)
    {
		if(acces == NULL || valide == NULL)
		{
		    fprintf(stderr,"Erreur lors de l'allocation mémoire.\n");
		    exit(EXIT_FAILURE);
		}

		// on parcours le fichier des acces mémoire
		for(i=0;i<nbAcces;i++)
		{
			page = acces[i];

			// On test si la page n'est pas déjà en RAM
			if(!valide[page])
			{
				valide[page] = 1;

				// Si on a encore de la place en RAM
				if(j < caseRAM)
				{
					pageRAM = inserer_element_liste(pageRAM,page);
					j++;
				}

				// Si on a plus de place -> defaut de page
				else
				{
					nbDefPage++;

					// Remplacement FIFO
					valide[renvoie_premier_liste(pageRAM)] = 0;
					pageRAM = supprimer_element_liste(pageRAM);
					pageRAM = inserer_element_liste(pageRAM,page);
				}
			}

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
	printf("\nDefauts de page : %d\n", nbDefPage);

	free(pageRAM);
	fclose(acces_mem);

    exit(EXIT_SUCCESS);
}


void usage(char* s)
{
    fprintf(stderr,"Usage : %s <numéro algo> <nb case RAM> <mode affichage> <fichier acces>\n",s);
    fprintf(stderr,"Algo :\n    1) FIFO\n    2) LRU\n    3) Horloge\n    4) Optimal\n");
    fprintf(stderr,"Mode affichage :\n    d: debug\n    c: classique\n");

    exit(EXIT_FAILURE);
}
