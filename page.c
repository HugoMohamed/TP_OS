#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
	fprintf(stderr,"Usage: %s <nbPage> <nomFichier>\n",argv[0]);
	exit(EXIT_FAILURE);
    }
    int nbPage = atoi(argv[1]);
    int x,i = 0;
    int taille = 10000;
    FILE* fich = fopen(argv[2],"w");
    if(fich == NULL)
    {
	fprintf(stderr,"Problème lors de la création/ouverture du fichier\n");
	exit(EXIT_FAILURE);
    }
    srand(time(NULL));

    fprintf(fich,"%d\n",taille);
    fprintf(fich,"%d\n",nbPage);

    while(i < taille - 2)
    {
	x = rand() % nbPage;
	fprintf(fich,"%d\n",x);
	i++;
    }

    fclose(fich);
    exit(EXIT_SUCCESS);
}
