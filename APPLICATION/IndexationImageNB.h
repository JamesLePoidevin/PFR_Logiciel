#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pile_statiqueNB.h"


void lecture_image(FILE* ptr,int ligne,int colonne,float tab[2]);
void listeDeFichiers1(char *adresseDeBase,char *fichierDArriver);
int NomDesFichiers1(char *CHEMIN);
char *cheminImage();
//void indexationCompleteNB();