#ifndef TRAITER_MOT_CLE_H_INCLUS     /*--  Inclusion conditionnelle --> si pas déjà inclus           */
#define TRAITER_MOT_CLE_H_INCLUS    /*--  alors créer la constante symbolique TRAITER_MOT_CLE_H_INCLUS */

#include "Recup_textes.h"

char mot_cle[50];

char minuscules[1000];
char recherche[1000];
char wc[1000];
char cut[1000];
char cp[1000];
char choix[1000];
char affichage[1000];
char quantite_mots[1000];
char echo[1000];
char recup_lignes[1000];

int validation;
int nb_mots;
int boucle;
int depart;

char * test;
char* res;


char resultat[1000];

int i;

char mot_de_base[100];
char mot_a_comparer[100];

void Recup_mots();
void affichage_mots(char* chemin_fic, char* nom_fic);
void Compare_mots();
void Recherche_extrait();
void Recherche_mot_exact();
void Recherche();

#endif
