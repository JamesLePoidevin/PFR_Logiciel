#include "IndexationImageRGB.h"

char CHEMIN_RGB [100] =  "../TEST_RGB/";

void listeDeFichiers2(char *adresseDeBase,char *fichierDArriver){
  char commande[1024];
  strcpy(commande, "ls -l ");
  strcat(commande, adresseDeBase);
  strcat(commande, " >");
  strcat(commande, fichierDArriver);
  system(commande);
}

//création liste fichiers
int NomDesFichiers2(char *CHEMIN){
  listeDeFichiers2(CHEMIN,"adresse");
  system("sed '/.jpg/d' adresse > adresse1");
  system("sed '/.bmp/d' adresse1 > adresse");
  system("rm adresse1");
  int IndiceDesNom = -1;
  char NomDuFichier[1024];

  FILE *ptr_fic;
  FILE *ptr_fichier;
  ptr_fic = fopen("adresse", "r");
  ptr_fichier = fopen("../Source/FILES/NomDesFichiersImage", "w");
  if(ptr_fichier != NULL){
    if( ptr_fic != NULL){
        fscanf( ptr_fic, "%*s %*s");      /* SAUTER LA PREMIERE LIGNE CONSTITUEE DE 2 CHAINES total xxxx */
      while ( fscanf( ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier)==1)
      {
        IndiceDesNom++;
        fprintf(ptr_fichier, "%s %d\n", NomDuFichier,IndiceDesNom);
      }
      fclose(ptr_fic);
      fclose(ptr_fichier);
    }else fprintf(stderr, "ERREUR :  PB avec liste_rep\n");
  }else fprintf(stderr, "ERREUR :  PB avec liste_rep\n");
  system("rm adresse");
  return IndiceDesNom;

}

void lectureImage2(FILE *ptr_fil,int ligne,int colonne,float *TABretour){
  int x,i;
  int index=0;

  int **TABR=malloc (ligne * sizeof (*TABR)); //déclare le nb de lignes de taille "nb de colonnes"
  for(i=0;i<ligne;i++){
    TABR[i]=malloc (colonne * sizeof (int)); //déclare le nb de colonnes
  }
  assert(TABR!=NULL);

  int **TABV=malloc (ligne * sizeof (*TABV));
  for(i=0;i<ligne;i++){
    TABV[i]=malloc (colonne * sizeof (int));
  }
  assert(TABV!=NULL);

  int **TABB=malloc (ligne * sizeof (*TABB));
  for(i=0;i<ligne;i++){
    TABB[i]=malloc (colonne * sizeof (int));
  }
  assert(TABB!=NULL);

  int **TAB=malloc (ligne * sizeof (*TAB));
  for(i=0;i<ligne;i++){
    TAB[i]=malloc (colonne * sizeof (int));
  }
  assert(TAB!=NULL);

  while(!feof(ptr_fil)){
    if(index!= ligne*colonne*3){
      fscanf(ptr_fil,"%d",&x);
      if(index<40000){
        TABR[index/ligne][index%colonne]=x;
      }else if(index <80000){

        TABV[(index/ligne)-ligne][index%colonne]=x;

      }else if(index < ligne*colonne*3){
        TABB[(index/ligne)-(2*ligne)][index%colonne]=x;
      }else break;
      index++;
    }else break;
  }

  int aux,aux1,aux2;
  int bitR;

  for (i = 0; i < ligne; i++){
    for (int j = 0; j < colonne; j++){
      aux=TABR[i][j]/128;
      if(aux>=1){
        aux1=1;
        TABR[i][j]=TABR[i][j]%128;
      }else aux1=0;
      aux=TABR[i][j]/64;
      if(aux>=1){
        aux2=1;
        TABR[i][j]=TABR[i][j]%64;
      }else aux2=0;
      TABR[i][j] = aux1*32+aux2*16;
      //printf("%d",TABR[i][j]);
  }
}

for (i = 0; i < ligne; i++){
  for (int j = 0; j < colonne; j++){
    aux=TABV[i][j]/128;
    if(aux>=1){
      aux1=1;
      TABV[i][j]=TABV[i][j]%128;
    }else aux1=0;
    aux=TABV[i][j]/64;
    if(aux>=1){
      aux2=1;
      TABV[i][j]=TABV[i][j]%64;
    }else aux2=0;
    TABV[i][j] = aux1*8+aux2*4;
}
}
for (i = 0; i < ligne; i++){
  for (int j = 0; j < colonne; j++){
    aux=TABB[i][j]/128;
    if(aux>=1){
      aux1=1;
      TABB[i][j]=TABB[i][j]%128;
    }else aux1=0;
    aux=TABB[i][j]/64;
    if(aux>=1){
      aux2=1;
      TABB[i][j]=TABB[i][j]%64;
    }else aux2=0;
    TABB[i][j] = aux1*2+aux2*1;
}
}
for (int i = 0; i < ligne; i++) {
  for (int j = 0; j < colonne; j++) {
  TAB[i][j]= TABR[i][j] + TABV[i][j] + TABB[i][j];
  }
}


 free(TABR);
 free(TABB);
 free(TABV);

 for(int i = 0; i < 63; i++)
 {
     TABretour[i] = 0;
 }
 for(int i = 0; i < ligne; i++)
 {
   for (int j = 0; j < colonne;j++)
   {
     TABretour[TAB[i][j]] ++;
   }
 }
}
 /*for (int i = 0; i < 63; ++i)
 {
   TABretour[i]=(TABretour[i]/(ligne*colonne))*100;
 }
}*/
/*
void indexationCompleteRGB(char*chemin){
  float tab[63];
  char*camino;
  FILE *ptr_chemin;
  int ligne,colonne,nbmatrice;
  int ref;
  type_descRGB RGB;
  PILERGB p = init_PILERGB();
  char* nomfic= malloc(150 * sizeof(char));;
  char* adr = malloc(150 * sizeof(char));
  nomfic=(char*)malloc(1024*sizeof(char));
  camino=(char*)malloc(1024*sizeof(char));
  strcpy(camino,CHEMIN_RGB); // à lire dans un fichier créé par Jean-Sébastien
  NomDesFichiers2(CHEMIN_RGB);

  ptr_chemin=fopen("../Source/FILES/NomDesFichiersImageRGB","r");
  if(ptr_chemin!=NULL){
    while(!feof(ptr_chemin)){
      float tab[63];
      fscanf(ptr_chemin,"%s %d",nomfic,&ref);
      strcpy(adr, camino);
      strcat(adr, nomfic);
      printf("%s",adr);

      FILE*ptr_fil;
      ptr_fil=fopen(adr,"r");
      fscanf(ptr_fil,"%d %d %d",&ligne,&colonne,&nbmatrice);

      lectureImage2(ptr_fil,ligne,colonne,tab);

      RGB.ref = ref;
      for (int i = 0; i < 64; i++)
      {
        RGB.tab[i]=tab[i];
      }
      p = emPILERGB(p, RGB);
    }
  }else fprintf(stderr,"ERREUR de pointeur NDFI");
  fclose(ptr_chemin);

  ptr_chemin=fopen("../Source/FILES/DescripteurImageRGB","w");
  while(PILE_estVideRGB(p)!=1){
    type_descRGB A;
    p = dePILERGB(p,&A);
    fprintf(ptr_chemin,"%d\n",A.ref );
    for (int i = 0; i < 63; i++)
    {
      fprintf(ptr_chemin, "%f \n",A.tab[i]);
    }
    
  }
  fclose(ptr_chemin);
  free(camino);
  free(nomfic);

}*/
/*
  int main(int argc, char const *argv[])
  {
    indexationCompleteRGB("../TEST_RGB/");
    return 0;
  }*/
