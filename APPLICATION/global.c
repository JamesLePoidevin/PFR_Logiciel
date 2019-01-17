#include "global.h"

char CHEMIN[1000] = "./"; //CHemin source
char CHEMIN2[1000] = "./FILES/"; //Chemin vers MotCles, Descripteur ...
char CHEMIN3[1000] = "./Param/"; //Chemin vers MotCles, Descripteur ...

void vider_buffer()
{
  buffer = 0;
  while (buffer != '\n' && buffer != EOF)
  {
      buffer = getchar();
  }
}

void init_chemin4(){
  strcpy(CHEMIN4,lirechemin());
}

int compter_mots(char* chemin_fic, char* fic_a_compter)
{
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
    fscanf(ptr_fic,"%d",&nb_mots);
  }
  fclose(ptr_fic);

  return nb_mots;
}

void Ouverture(char* chemin_fic, char* fic_a_ouvrir)
{
  strcpy(ouverture,"cat ");
  strcat(ouverture,chemin_fic);
  strcat(ouverture,fic_a_ouvrir);
  system(ouverture);

  printf("\n\n");
}
