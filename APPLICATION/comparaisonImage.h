#include "IndexationImage.h"


//structure permetant de faciliter le traitement des reultat
typedef struct type_resultat
{
	int sim;
	int id;
}type_resultat;

int AffichageFichier();

//int test_pourcentage();
int test_entier();

float min(float a , float b);

void triTableauResultat(type_resultat* res ,int taille);

void compair(int choix);

void ouvrirImageNB(char * nom);

void ouvrirImageRGB(char * nom);