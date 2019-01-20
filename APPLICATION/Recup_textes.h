#ifndef RECUP_TEXTES_H_INCLUS     /*--  Inclusion conditionnelle --> si pas déjà inclus           */
#define RECUP_TEXTES_H_INCLUS    /*--  alors créer la constante symbolique RECUP_TEXTES_H_INCLUS */

#include "global.h"

int* liste_descripteurs; //Contiendra la liste des descripteurs contenant le mot choisi par l'utilisateur.
int* occurrences; //Contiendra la liste des occurrences par descripteur triée par ordre décroissant
int* tri_descripteurs; //Contiendra la liste des descripteurs triés en fonction de leurs occurrences.
//La taille des 3 tableaux ci-dessus sera allouée dynamiquement en fonction du nombe de descripteurs correspondants à la recherche.

int nb_descripteurs;//Correspond au nombre de descripteurs contenant le mot choisi.

int nb_titres; //nombre de titres déjà récupérés;

void Recup_descripteurs();
void Enregistrer_descripteurs();
void Isoler_descripteur(int num);
void occurrences_par_descripteurs(char* mot);
int Recup_occurrences(int pos);

void Recup_Titres(int num);
void afficher_liste_textes();
void Recup_textes();

#endif
