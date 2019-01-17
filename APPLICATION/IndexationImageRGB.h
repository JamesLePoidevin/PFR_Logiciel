#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "pile_statiqueRGB.h"


void listeDeFichiers2(char *adresseDeBase,char *fichierDArriver);
int NomDesFichiers2(char *CHEMIN);
void lectureImage2(FILE *ptr_fil,int ligne,int colonne,float *TABretour);
//void indexationCompleteRGB(char*chemin);