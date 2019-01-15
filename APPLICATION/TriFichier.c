#include "TriFichier.h"


/**
 * Range le fichier qui se trouve à CHEMIN par ordre alphabétique
 * @param  CHEMIN Chemin du fichier
 */
void programme(char* CHEMIN)
{
  //lecture de nombre de mot
  FILE *ptrFichierMC;
  ptrFichierMC = fopen(CHEMIN,"r");
  CompterMot(CHEMIN,"nbmot");
  fclose(ptrFichierMC);

  //lecture du nombre de mots dans le fichiers apres le wc -w
  FILE *ptrNBMOT;
  ptrNBMOT =fopen("nbmot","r");
  int NBmot = NombreDeMot(ptrNBMOT);
  NBmot = NBmot/2;
  fclose(ptrNBMOT);

  int i,j;
  int indice = 0;
  type_MC nom[NBmot];
  type_MC tri[NBmot];
  type_MC temporary;

  ptrFichierMC = fopen(CHEMIN,"r");
  type_MC A;
  while ( fscanf(ptrFichierMC,"%s %d",A.mot,&A.refer)==1){
    tri[indice] = A;
    indice ++;
  }
  fclose(ptrFichierMC);

  //tri par bulles
  for(j = 0; j < NBmot; j++){
    for(i = 0; i < NBmot;i++){
      if(stringcompare(tri[i].mot, tri[i+1].mot) > 0)
      {
        temporary = tri[i];
        tri[i] = tri[i+1];
        tri[i+1] = temporary;
      }
    }
  }

  //rangement du fichier MotsClés
  FILE *ptrChemin;
  ptrChemin = fopen(CHEMIN,"w");
  for(i = 0; i <= NBmot; i++)
  {
    fprintf(ptrChemin,"%s %d\n", tri[i].mot,tri[i].refer);
  }
  fclose(ptrChemin);
}


/**
 * Comparateur de chaine de char
 * @param  s1 Chaine de char 
 * @param  s2 Chaine de char
 * @return    1 si pas pareil 0 sinon
 */
int stringcompare(char *s1, char *s2)
{
  int i = 0;

  while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
  i++;
  if(s1[i] > s2[i])
  return 1;
  else
  return 0;
}
