#ifndef RECUP_TEXTES_H_INCLUS     /*--  Inclusion conditionnelle --> si pas déjà inclus           */
#define RECUP_TEXTES_H_INCLUS    /*--  alors créer la constante symbolique RECUP_TEXTES_H_INCLUS */


#include "global.h"

int i;
int nb_occ_min;
int* position;
int* place_descripteur;

char cut[1000];
char isolement[1000];
char association[1000];
char nl[1000];
char recup_occ[1000];

int liste_descripteurs[1000];
int occurences[1000];
int tri_descripteurs[1000];
char titre[1000];

FILE* ptr_fic;

int nb_descripteurs;
int ligne;

int occ;
int z;

void Recup_descripteurs();
void Enregistrer_descripteurs();
void Isoler_descripteur(int num);
void Occurences_par_descripteurs(char* mot);
int Recup_occurences(int pos);

void Recup_Titres(int num);
void afficher_liste_textes();
void Recup_textes();

#endif
