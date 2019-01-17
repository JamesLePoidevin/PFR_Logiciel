#ifndef GLOBAL_H_INCLUS     /*--  Inclusion conditionnelle --> si pas déjà inclus           */
#define GLOBAL_H_INCLUS    /*--  alors créer la constante symbolique GLOBAL_H_INCLUS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Comparaison.h"
#include "comparaisonImage.h"

char CHEMIN[1000];
char CHEMIN2[1000];
char CHEMIN3[1000];
char CHEMIN4[1000];
int STOP;

char comptage[1000];
char ouverture[1000];
char dossier[1000];
char fichier[1000];

char mot_choisi[50];
FILE* ptr_fic;
int nb_mots;
int buffer;

void vider_buffer();
int compter_mots(char* chemin_fic, char* fic_a_compter);
void Ouverture(char* chemin_fic, char* fic_a_ouvrir);
void Initialisation();
void init_chemin4();
#endif
