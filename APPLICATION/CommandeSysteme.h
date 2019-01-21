#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Ce fichier sert a mettre tous les fonction unix nécessaire pour l'application
tous le long de CommandeSysteme.c les seul fonction utiliser sont
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