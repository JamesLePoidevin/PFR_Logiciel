#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Ce fichier sert à mettre toutes les fonctions unix nécessaires pour l'application
tout le long de CommandeSysteme.c Les seules fonctions utilisées sont
	-strcat(char*,char*);
	-strcpy(char*,char*);
	-systeme(char*);
*/
int lireparametrecompar();

void listeDeFichiers(char *adresseDeBase,char *fichierDArriver);

void CompterMot(char *AdresseDuFichier,char *fichierDArriver);

void SupprimerFichier(char *AdresseDuFichier);

void OuvrirFichier(char *AdresseDuFichier);

void clean();