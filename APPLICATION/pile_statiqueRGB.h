#include <stdio.h>
#include "elementRGB.h"

#define MAX 100

typedef struct
{
  ELEMENTRGB tab[MAX];
  int indice;
} PILERGB;


PILERGB init_PILERGB();
void affiche_PILERGB(PILERGB p);
int PILE_estVideRGB(PILERGB p);
int PILE_estPleineRGB(PILERGB p);
PILERGB emPILERGB(PILERGB p, ELEMENTRGB a);
PILERGB dePILERGB(PILERGB p,ELEMENTRGB *a);
//PILE saisir_PILE();