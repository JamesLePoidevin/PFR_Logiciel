#ifndef TRAITER_MOT_CLE_H_INCLUS     /*--  Inclusion conditionnelle --> si pas déjà inclus           */
#define TRAITER_MOT_CLE_H_INCLUS    /*--  alors créer la constante symbolique TRAITER_MOT_CLE_H_INCLUS */

#include "global.h"

char mot_cle[50]; //Contiendra le mot saisi par l'utilisateur.

int nb_mots; //variable qui permet de connaître le nombre de mots correspondant à la recherche de l'utilisateur.
int boucle; //Variable qui sera utilisée comme condition pour sortir d'une boucle
int depart; /*On doit connaître la valeur de cette variable à tout moment pour enregistrer les mots correspondants à la recherche de l'utilisateur au départ dans un fichier temporaire.
             Ce fichier ne sera plus modifié, ces mots pourront donc être reproposés en cas d'erreur de saisie.*/

void Recup_mots();
void affichage_mots(char* chemin_fic, char* nom_fic);
void Compare_mots();
void Recherche_extrait();
void Recherche_mot_exact();
void Recherche();

#endif
