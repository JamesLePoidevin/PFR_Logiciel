#include <stdio.h>
#include "elementNB.h"

#define MAX 100

typedef struct
{
  ELEMENTNB tab[MAX];
  int indice;
} PILENB;


PILENB init_PILENB();
void affiche_PILENB(PILENB p);
int PILE_estVideNB(PILENB p);
int PILE_estPleineNB(PILENB p);
PILENB emPILENB(PILENB p, ELEMENTNB a);
PILENB dePILENB(PILENB p,ELEMENTNB *a);
//PILE saisir_PILE();