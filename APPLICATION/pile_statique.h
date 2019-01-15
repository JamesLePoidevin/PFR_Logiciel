#include <stdio.h>
#include "element.h"

#define MAX 100

typedef struct
{
  ELEMENT tab[MAX];
  int indice;
} PILE;


PILE init_PILE();
void affiche_PILE(PILE p);
int PILE_estVide(PILE p);
int PILE_estPleine(PILE p);
PILE emPILE(PILE p, ELEMENT a);
PILE dePILE(PILE p,ELEMENT *a);
//PILE saisir_PILE();