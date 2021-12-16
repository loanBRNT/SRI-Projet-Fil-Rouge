#include <stdio.h>
#include <stdlib.h>
#include "img.h"


int main(int argc, char const *argv[])
{
    Descripteur descripteur;

	printf("Tout commence ici....\n");
    descripteur = indexer_image("/NB/53.txt");
        printf("{%d,%d,", descripteur.ID, descripteur.t_max);
        for (int i = 0; i < descripteur.t_max; i++) {
            printf("%d ", descripteur.histogramme[i]);
        }
        printf("}\n");
	return 0;
}