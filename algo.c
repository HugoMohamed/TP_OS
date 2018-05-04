/*********************************
 *                               *
 *  Algorithmes de remplacement  *
 *  de page                      *
 *                               *
 *  Auteur : Hugo MOHAMED        *
 *                               *
 ********************************/

#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

void usage(char* s);

// First In First Out
int fifo(int nbAcces,int *valide, int *acces, int caseRAM);

// Less Rencently Use
int lru(int nbPage,int nbAcces,int *valide, int *acces, int caseRAM);

// Algorithme de l'Horloge
int horloge(int nbPage, int nbAcces,int *valide, int *acces, int caseRAM);

// Optimal
int optimal(int nbPage, int *acces, int *valide, int caseRAM, int nbAcces);

int main(int argc, char* argv[])
{
    if(argc < 5)
	usage(argv[0]);

    int algo = atoi(argv[1]);
    int caseRAM = atoi(argv[2]);

    if(caseRAM < 1)
    {
	fprintf(stderr,"Erreur, nombre de case invalide\n");
	exit(EXIT_FAILURE);
    }

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
    int i = 0;
    int page;
    char ligne[10];

    fgets(ligne,10,acces_mem);
    nbAcces = atoi(ligne);
    fgets(ligne,10,acces_mem);
    nbPage = atoi(ligne);

    acces = (int*)malloc(nbAcces * sizeof(int));
    valide = (int*)malloc(nbPage * sizeof(int));
    if(acces == NULL || valide == NULL)
    {
	fprintf(stderr,"Erreur lors de l'allocation mémoire.\n");
	exit(EXIT_FAILURE);
    }

    // On remplit le tableau des acces mémoire
    while(fgets(ligne,10,acces_mem) != NULL)
    {
	acces[i] = atoi(ligne);
	printf("%d ",acces[i]);
	i++;
    }

    // On initialise valide a 0
    for(i=0;i<caseRAM;i++)
	valide[i] = 0;

    // FIFO
    if(algo == 1)
		nbDefPage = fifo(nbAcces, valide, acces, caseRAM);

    // LRU
    else if(algo == 2)
		nbDefPage = lru(nbPage, nbAcces, valide, acces, caseRAM);

    // Horloge
    else if(algo == 3)
		nbDefPage = horloge(nbPage,nbAcces,valide,acces,caseRAM);

    // optimal
    else if(algo == 4)
		nbDefPage = optimal(nbPage,acces,valide,caseRAM,nbAcces);

    printf("\nDefauts de page : %.2f%%\n", (1.0*nbDefPage/nbAcces)*100);

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


int fifo(int nbAcces,int *valide, int *acces, int caseRAM)
{
    int i, j=0, nbDefPage=0;
    int page;
    liste pageRAM = liste_vide();

    // on parcours les acces mémoire
    for(i=0;i<nbAcces;i++)
    {
	page = acces[i];

	// On test si la page n'est pas déjà en RAM
	if(valide[page] == 0)
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
    free(pageRAM);
    return nbDefPage;
}

int lru(int nbPage,int nbAcces,int *valide, int *acces, int caseRAM)
{
    int i, j, k, nbDefPage=0;
    int nbRam = 0;
    int pageLRU;
    int plus_vieux = 0;
    int page;
    int *dernier_acces;

    dernier_acces = (int*)calloc(nbPage, sizeof(int));

    // on parcours les acces mémoire
    for(i=0;i<nbAcces;i++)
    {
	page = acces[i];

	// On incremente la valeur de chaque acces
	// et on met celui qu'on traite a 0
	for(j=0;j<nbPage;j++)
	{
	    dernier_acces[j]++;
	    dernier_acces[page] = 0;
	}

	// Si la page n'est pas en RAM
	if(!valide[page])
	{
	    valide[page] = 1;
	    // Si on a encore de la place
	    if(nbRam < caseRAM)
		nbRam++;

	    else
	    {
		// Sinon, défaut de page
		nbDefPage++;

		// -> remplacement LRU
		for(k=0;k<nbPage;k++)
		{
		    // On parcours le tableau pour trouver le moins recemment utilisé en mémoire
		    if(k != page)
			if(plus_vieux <= dernier_acces[k] && valide[k])
			{
			    plus_vieux = dernier_acces[k];
			    pageLRU = k;
			}
		}

		valide[pageLRU] = 0;
	    }

    	}
    }
    return nbDefPage;
}

int horloge(int nbPage, int nbAcces,int *valide, int *acces, int caseRAM)
{
    int *b_acces;
    liste pageRAM = liste_vide();
    int page;
    int i,x,j = 0;
    int pointeur;
    int nbDefPage = 0;

    b_acces = (int*)calloc(nbPage,sizeof(int));
    if(b_acces == NULL)
    {
		fprintf(stderr,"Erreur mémoire\n");
		exit(EXIT_FAILURE);
    }

    // On parcours les accès
    for(i=0;i<nbAcces;i++)
    {
		page = acces[i];
		b_acces[page] = 1;

		// Si la page n'est pas en RAM
		if(!valide[page])
		{
		    valide[page] = 1;

		    // Si on a encore de la place
		    if(j < caseRAM)
		    {
				// Si on est sur la derniere case -> on boucle
				if(j == caseRAM-1)
				{
					pageRAM = enfiler(pageRAM,page);
					pageRAM->suivant = pageRAM;
				}
				else
				    pageRAM = enfiler(pageRAM,page);

				j++;
		    }

		    // Sinon -> défaut de page
		    else
		    {
				nbDefPage++;
				pointeur = 0;

			// On test si on peut inserer
				while(!pointeur)
				{
					x = renvoie_premier_liste(pageRAM);

					// Si bit = 0
					if(!b_acces[x])
				    {
						// On remplace
						valide[x] = 0;
						pageRAM->objet = page;
						pointeur = 1;
				    }
				    // Si bit = 1
				    else
				  	{
						// On fait tourner l'horloge
						b_acces[x] = 0;
						pageRAM = pageRAM->suivant;
				    }
				}
		    }
		}
    }

    free(pageRAM);
    return nbDefPage;
}

int optimal(int nbPage, int *acces, int *valide, int caseRAM, int nbAcces)
{
    int nbDefPage = 0;
    int i,j=0,k,l;
    int page;
	int plus_loin, a_suppr;

    // Pour calculer le prochain acces
    int *prochain;
    prochain = (int*)calloc(nbPage,sizeof(int));

    // On parcours les acces
    for(i=0;i<nbAcces;i++)
    {
		page = acces[i];

		// Si la page n'est pas en RAM
		if(!valide[page])
		{
		    valide[page] = 1;

		    // Si on a encore de la place
		    if(j < caseRAM)
				j++;

			// Sinon -> défaut de page
		    else
		    {
				nbDefPage++;
				plus_loin = 0;
				// On parcous les pages
				for(k=0;k<=nbPage;k++)
				{
					// On met a 0 dans prochain, celle qui sont en RAM
					if(valide[k] && k != page)
					{
						prochain[k] = 0;
						l = i+1;

						while(acces[l] != k && l < nbAcces)
						{
							l++;
							prochain[k]++;
						}
					}
				}
				// On cherche la page en RAM qui sera utilisée la plus tard
				for(k=0;k<=nbPage;k++)
				{
					if(valide[k] && k!=page)
					{
						if(plus_loin <= prochain[k])
						{
							plus_loin = prochain[k];
							a_suppr = k;
						}
					}
				}
				// Et on la remplace
				valide[a_suppr] = 0;
		    }
		}
    }
	free(prochain);
	return nbDefPage;
}
