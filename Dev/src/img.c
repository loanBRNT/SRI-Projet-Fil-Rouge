#include "img.h"

Descripteur initDescripteur(int nb_composantes){
    Descripteur descri;
    descri.t_max = pow(2,(n*nb_composantes));
    descri.histogramme = NULL;
    descri.histogramme = malloc(descri.t_max*sizeof(int));
    if(descri.histogramme == NULL) {
        printf("Erreur du malloc");
        exit(0);
    }
    for (int i = 0 ; i < descri.t_max; i++) {
        descri.histogramme[i] = 0;
    }
    return descri;
}

void quantificationRGB(int longueur, int hauteur, Descripteur *des, FILE* fichier){
    int val;
    TAB tempo;

    tempo = malloc(longueur*hauteur*sizeof(long));
    for (int cptemp = 0; cptemp < longueur*hauteur; cptemp ++){     //Sauvegarde de la quantification rouge dans temporaire
        fscanf(fichier,"%d", &val);
        tempo[cptemp] = ( (val & conversion_masques[n-1]) >> 2 );
    }

    for (int cptemp = 0; cptemp < longueur*hauteur; cptemp ++){     //Sauvegarde de la quantification verte dans temporaire
        fscanf(fichier, "%d", &val);
        tempo[cptemp] = tempo[cptemp] + ( (val & conversion_masques[n-1]) >> 4 );
    }

    for (int cptemp = 0; cptemp < longueur*hauteur; cptemp ++){     //Sauvegarde de la quantification bleu dans temporaire
        fscanf(fichier, "%d", &val);
        tempo[cptemp] = tempo[cptemp] + ( (val & conversion_masques[n-1]) >> 6 );
    }

    for (int cptemp = 0; cptemp < longueur*hauteur; cptemp ++){
        (*des).histogramme[tempo[cptemp]]++;
    }
    free(tempo);
}

void quantificationNB(Descripteur *descripteur, int longueur, int hauteur, FILE* fichier){
    int val;
    for (int cpt = 0; cpt < longueur*hauteur; cpt++){
            fscanf(fichier,"%d", &val);
            val = ( (val & conversion_masques[n-1]) >> (8-n));
            (*descripteur).histogramme[val] ++;
    }
}

Descripteur indexer_image(char* nom){

    // Declaration varibales
    int longueur , hauteur, d;
    Descripteur descripteur;
    FILE* fichier = NULL;

    //Récupération de la valeur n du .config

    // Ouverture de l'image
    fichier = fopen("../Database/Image/NB/test.txt","r");
    if (fichier != NULL) {

        // Récupération des données image
        fscanf(fichier,"%d %d %d", &longueur, &hauteur, &d);
        // Initialisation en fonction du fichier
        descripteur = initDescripteur(d);
        descripteur.ID = 234;

        switch(d){
            case 1 : // Quantification NB
                quantificationNB(&descripteur,longueur,hauteur,fichier);
                break;
            case 3 : // Quantification RGB
                quantificationRGB(longueur,hauteur,&descripteur,fichier);
                break;
         default : printf("Format de l'image pas supporté\n");
        }
        fclose(fichier);
    }
    else
        printf("Echec de l'ouverture de l'image à indexer");

    return descripteur;
}