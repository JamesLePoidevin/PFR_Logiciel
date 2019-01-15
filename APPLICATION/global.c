#include "global.h"

char CHEMIN[1000] = "../APPLICATION/";
char CHEMIN2[1000] = "../APPLICATION/FILES/";

void vider_buffer()
{
  buffer = 0;
  while (buffer != '\n' && buffer != EOF)
  {
      buffer = getchar();
  }
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
  fscanf(ptr_fic,"%d",&nb_mots);
  fclose(ptr_fic);

  return nb_mots;
}

void Ouverture(char* chemin_fic, char* fic_a_ouvrir)
{
  strcpy(ouverture,"cat ");
  strcat(ouverture,chemin_fic);
  printf("%s\n",fic_a_ouvrir );
  strcat(ouverture,fic_a_ouvrir);
  //strcat(ouverture," &");

  system(ouverture);
}
