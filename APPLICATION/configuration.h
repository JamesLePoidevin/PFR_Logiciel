#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "menuUser.h"

//FONCTIONS POUR VERIFIER LES TYPES
float test_pourcentage();

//VISUALISER LES DESCRIPTEURS
//Textes
void affiche_descripteur_texte();
//Images noir et blanc
void affiche_descripteur_image_NB();
//Images Couleur
void affiche_descripteur_image_coul();
//Menu pour visualiser les descripteurs
void menu_descripteur();

//PARAMETRAGE RECHERCHE
void param_recherche_texte();

//PARAMETRAGE COMPARAISON
//Textes
void param_compar_texte();
//Images Noir et Blanc
void param_compar_img_nb();
//Images Couleur
void param_compar_img_coul();
//Menu pour comparaison
void menu_comparaison();

//PARAMETRAGE INDEXATION
// Texte
void param_index_texte();
//Image
void param_index_image();
//Menu indexation (choix entre texte ou image)
void menu_index();
//Chemin d'accès des textes
void chemin_texte();
//Chemin d'accès des images noir et blanc
void chemin_image_nb();
//Chemin d'accès des images couleur
void chemin_image_coul();
//Menu modification chemins (choix entre texte, image noir et blanc, image couleur)
void menu_chemins();

void menu_admin();
