#include "global.h"

void vider_buffer() //permet de vider le buffer pour éviter les saisies parasites
{
  char buffer = '0';
  while (buffer != '\n' && buffer != EOF)
  {
      buffer = getchar();
  }
}

void init_chemins() //Permet d'initialiser les chemins
{
  strcpy(CHEMIN,"./");
  strcpy(CHEMIN2,"./FILES/"); //Chemin vers MotCles, Descripteur ..
  strcpy(CHEMIN3, lirechemin());
}

int compter_mots(char* chemin_fic, char* fic_a_compter) //fonction qui permet de renvoyer le nombre de mots d'un fichier passé en paramètre
{
  int nb_mots; //pour récupérer le nombre de mots du fichier passé en paramètre
  FILE* ptr_fic;
  char comptage[1000]; //Contiendra la commande permettant de compter les mots et envoyer le total dans un fichier.

  strcpy(comptage, "wc -w ");
  strcat(comptage, chemin_fic);
  strcat(comptage,fic_a_compter);
  strcat(comptage, " > ");
  strcat(comptage, chemin_fic);
  strcat(comptage, "total.temp");
  system(comptage);

  ptr_fic = fopen("total.temp","r");
  if(ptr_fic != NULL)
  {
    fscanf(ptr_fic,"%d",&nb_mots); //On récupère le nombre de mots dans le fichier précédemment créé.
  }
  fclose(ptr_fic);

  return nb_mots;
}

void Ouverture(char* chemin_fic, char* fic_a_ouvrir) //Permet d'ouvrir en console le fichier passer en paramètre.
{
  char ouverture[1000]; //Contiendra la commande d'ouverture.

  strcpy(ouverture,"cat ");
  strcat(ouverture,chemin_fic);
  strcat(ouverture,fic_a_ouvrir);
  system(ouverture);
}
