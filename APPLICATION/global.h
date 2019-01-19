#ifndef GLOBAL_H_INCLUS     /*--  Inclusion conditionnelle --> si pas déjà inclus           */
#define GLOBAL_H_INCLUS    /*--  alors créer la constante symbolique GLOBAL_H_INCLUS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Comparaison.h"
#include "comparaisonImage.h"

char CHEMIN[1000]; //contient le chemin source du code
char CHEMIN2[1000]; //contient le chemin vers les fichiers MotsCles, Descripteur ...
char CHEMIN3[1000]; //contient le chemin vers les textes à ouvrir

int STOP; //une variable qui servira de condition pour quitter le programme

char mot_choisi[50]; //contiendra le mot que l'utilisateur choisit à la fin pour sa recherche

void vider_buffer();
int compter_mots(char* chemin_fic, char* fic_a_compter);
void Ouverture(char* chemin_fic, char* fic_a_ouvrir);
void init_chemins();

#endif
