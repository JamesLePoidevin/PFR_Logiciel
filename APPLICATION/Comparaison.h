#include "indexationAuto.h"
#include <unistd.h>

//structude des resultat avec similitude et id
typedef struct type_resultattext
{
	float sim;
	int id;
}type_resultattext;

void triTableauResultat1(type_resultattext* tab ,int taille);

void ChoixDuFichier();