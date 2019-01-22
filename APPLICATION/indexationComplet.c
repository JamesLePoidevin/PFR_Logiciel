#include "indexationComplet.h"

char* Chemin_text = "../Textes/";

/**Verifie si le mot passer en parametre contien un point ou virgule
 * @param mot à traiter
 */ 
void enleverPointEtVirgule(char* mot){

  /*pointeur pour l'adresse de point et virgule*/
  char * ptr_adressepoint,* ptr_adressevirgule;

  /*Verifie si dans le mot passer en parametre il y a point ou virgule*/
  ptr_adressepoint = strchr(mot,'.');
  ptr_adressevirgule = strchr(mot,',');

  if(ptr_adressepoint || ptr_adressevirgule){
    /*Si ya un point ou virugle dans mot*/
    if(mot == ptr_adressepoint || mot == ptr_adressevirgule){
      strcpy(mot,mot+1);
    }else if(mot[strlen(mot)-1] == '.'){
      /*si le mot fini par une point on remplace par un \0*/
      strcpy(ptr_adressepoint,"\0");

    }else if(mot[strlen(mot)-1] == ','){
      /*si le mot fini par une virgule on remplace par un \0*/
      strcpy(ptr_adressevirgule,"\0");

    }else if(ptr_adressepoint != NULL){
      /*trouver une eutre facon de faire */
      strcpy(ptr_adressepoint , "\0");
    }else strcpy(ptr_adressevirgule,"\0");

  }
}

/*Faire conction Blacklist que viens lire les mot dans BlackListe et met dans un tableau*/
int Blacklist(char **tab){
  system("wc -l BLACKLIST > nbmot.temp");

  int nombreDeMotBlackList;

  FILE *ptrnb;
  ptrnb = fopen("nbmot.temp","r");
  if(ptrnb != NULL){
    fscanf(ptrnb,"%d %*s",&nombreDeMotBlackList);
  }else fprintf(stderr, "ERREUR nombre mot BLAKLIST\n");
  fclose(ptrnb);
  
  /*Supprimer le fichier temporaire avec le nombre de mot dans la Blacklist*/
  system("rm nbmot.temp");

  FILE *ptrBLACKLIST;
  int i =0;

  ptrBLACKLIST = fopen("/BLACKLIST","r");
  if(ptrBLACKLIST != NULL){
    while(fscanf(ptrBLACKLIST,"%s",tab[i])==1){
      i++;
    }
  }else fprintf(stderr, "ERREUR pointeur BLACKLIST\n");
  fclose(ptrBLACKLIST);

  return nombreDeMotBlackList;
}


/*puis un autre que comprat et les laisse passer ou non*/


/**
 * Verifie si le mot passer en parametre contien une appostrophe, si oui le mot commence alors après l'appostrophe
 * @param mot Mot a traiter
 */
void enleverAppostrophe(char* mot){
  //Verifie si il y a ' dans le mot passer en parametre si oui l'adresse de ' est mis dans ptr_adesseApp'
  char * ptr_adresseApp; 
  ptr_adresseApp = strchr(mot,'\'');

  if(ptr_adresseApp){
    strcpy(mot, ptr_adresseApp+1);
  }
}

void enleverParenthese(char * mot){

  char * ptr_adresseParentheseOuvrante, *ptr_adresseParentheseFermante ; 
  /*Verifie si le mot contient des parenthese*/
  ptr_adresseParentheseOuvrante = strchr(mot,'(');
  ptr_adresseParentheseFermante = strchr(mot,')');

  /*Si il y a une parathese*/
  if(ptr_adresseParentheseOuvrante || ptr_adresseParentheseFermante){
    /* Cas ou on a : (MOT */
    if(ptr_adresseParentheseOuvrante){
      strcpy(mot,ptr_adresseParentheseOuvrante+1);
    }
    /* Cas ou on a : MOT)*/
    if(ptr_adresseParentheseFermante){
      strcpy(ptr_adresseParentheseFermante,"\0");
    }
  }

}

int misDeMotDansTableau(char* mot, int indiceTabMot, type_mot tab[]){
  int etat = -1;
  
  /*Mis dans un tableau de type_mot (de type char*mot , int occurance)*/
  /*il faut que le mot sois superieur a 2 lettre*/
  if(strlen(mot) > 2){

    /*Si c'est le premier mot il va directement dans le tabeleau*/
    if(indiceTabMot ==0){
      strcpy(tab[indiceTabMot].mot,mot);  //copie du mot
      tab[indiceTabMot].occurence =1;   //occurance mis a 1
      indiceTabMot ++;
    }else{
    /*Si c'est pas le premier mot on parcour le tableau de mot en comparant chaque mot du 
    tableau avec le mot en quesiton*/
      //printf("%d\n", indiceTabMot);
      for (int i = 0; i < indiceTabMot; i++)
      {
        if(strcmp(tab[i].mot,mot)==0){
          etat = i;
        } 
      }
      /*S'il y est on ajoute un au accurance*/

      if(etat != -1){
        tab[etat].occurence ++;

      }else{
      /*Sinon on le met dans une nouvelle case et on aguement le tableau de 1 case*/
        strcpy(tab[indiceTabMot].mot,mot);
        tab[indiceTabMot].occurence = 1;
        indiceTabMot ++;
      }
    }
  }
  return indiceTabMot;
}


/**
 * Enlver les balise d'un fichier et aussi fait appelle a enleverPointEtVirgule et enleverAppostrophe
 * @param ptr_fic Fichier a traiter
 */
int enleverBalise2(FILE * ptr_fic,type_mot tab[]){
  /*Sauter la premier ligne*/
  fscanf(ptr_fic, "%*s %*s %*s");

  int indiceTabMot =0;

  /*Mot de maximent de 50 lettre*/
  char *mot = malloc(50 * sizeof(char));

  char ** tab12 = malloc(50 * sizeof(char*));
    for (int i = 0; i < 50; i++)
    {
      char *tab12 = malloc(50 * sizeof(char));
    }
  //int nbmotBLACK = Blacklist(tab12);
  

  while(fscanf(ptr_fic,"%s",mot)==1){


    /*ptr_debut_tag = adresse de '<' // ptr_fin_tag = adresse de '>' */
    char * ptr_debut_tag, *ptr_fin_tag, *ptr_avant;

    /*Cherche le caractère '>'<' dans le mot*/
    /*Renvoie l'adresse de ce caractère ou null si ya pas*/
    ptr_debut_tag = strchr(mot, '<');
    ptr_fin_tag = strchr(mot, '>') ;

    if(ptr_debut_tag && ptr_fin_tag){ /* on a une balise à enlever */
      /*Si on a <balise> ou <balise>TEXTE_COLLE <balise><balise>*/

    if(ptr_debut_tag == mot){
        /*Si on a <balise> ou <balise><balise>*/

      if(mot[strlen(mot)-1] == '>'){
        strcpy(mot,"l");
      }else {
          /*Si on a <balise>TEXTE_COLLE // > est a l'adresse ptr_fin_tag donc + 1 est la cas apres*/
        strcpy(mot,ptr_fin_tag + 1);
      }
      }else strcpy(ptr_debut_tag,"\0"); /*Si on a TEXTE_COLLE<balise>*/
    }
    

    enleverPointEtVirgule(mot);
    enleverAppostrophe(mot);
    enleverParenthese(mot);

    
    if(strlen(mot)>3){
    /*met le mot dans tableau tab et verifier si le mot est deja dans le tableau*/
    indiceTabMot = misDeMotDansTableau(mot,indiceTabMot,tab);

    } 
    
  }
  return indiceTabMot;
}


/**
 * Met les descripteur dans le fichier Descipteur
 * @param descripteur Descripteur a rajouter
 */
void ecritureDescripteur(type_des descripteur){
  FILE * ptrdescripteur;

    /*Ouvre le le fichier ou ce trouve les déscripteur en ajoute*/
    ptrdescripteur = fopen("FILES/Descripteur","a");

    if(ptrdescripteur != NULL){

      fprintf(ptrdescripteur,"%d\n",descripteur.ref);
      /*De 0 a nombre de valeur a dans descripteur, Lu dans un fichier apart*/
      for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
      {
        /* Ecrit dans le fichier Descripteur MOT OCCURENCE */
        fprintf(ptrdescripteur,"%s %d\n",descripteur.tab[i].mot,descripteur.tab[i].occurence);
      }
    }

  fclose(ptrdescripteur);
}

void ecritureMotCles(type_des descripteur){
  FILE * ptrMotCles;

    /*Ouvre le fichier où se trouvent les descripteurs en ajoute*/
    ptrMotCles = fopen("FILES/MotsCles","a");

    if(ptrMotCles != NULL){

      
      /*De 0 à nombre de valeurs dans le descripteur, Lu dans un fichier à part*/
      for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
      {
        /* Ecrit dans le fichier Descripteur MOT OCCURENCE */
        fprintf(ptrMotCles,"%s %d\n",descripteur.tab[i].mot,descripteur.ref);
      }
    }

  fclose(ptrMotCles);
}

char* lirechemin(){

  char* chemin = malloc(100 *sizeof(char));

  system("sed '6,6!d' Param/param_indexation > file.tmp");
  

  FILE *ptr_fichierTEMP;

  ptr_fichierTEMP =fopen("file.tmp","r");
  if(ptr_fichierTEMP !=NULL){
    fscanf(ptr_fichierTEMP,"%s",chemin);
  }else fprintf(stderr, "ERREUR pointeur file.tmp\n");
  return chemin;

}

type_des FaireDescripteur(FILE * ptr_fic,int reference){
  int nbmot;
   type_des descripteur = init_des();
   type_mot *tab = malloc(5000 * sizeof(type_mot));

    for (int i = 0; i < 5000; i++)
    {
      tab[i] = init_mot();
    }

      if(ptr_fic != NULL){
        
        /*nbmot nombre de mot dans tab sans les balise*/
        nbmot = enleverBalise2(ptr_fic,tab);

      }else fprintf(stderr, "ERREUR pointeur Fichier a lire\n");
      fclose(ptr_fic);
      
      type_mot *tab2 = malloc(nbmot * sizeof(type_mot));
      for (int i = 0; i < nbmot; i++)
      {
        tab2[i] = init_mot();
      }
      
      /*tri le tableau dans l'ordre décroissant en fonction de l'occurence */
      Trier_tab_mot(tab,tab2,nbmot);
      
      /*Creer un descripteur a partir des réference et tableau ranger*/
      descripteur=CreerDescriteur(reference,tab2);

      //creer des erreur
      for (int i = 0; i < 5000; i++){
        free(tab[i].mot);
      }
      free(tab);

      for (int i = 0; i < nbmot; i++)
      {
        free(tab2[i].mot);
      }
      free(tab2);

      return descripteur;

}

void IndexationComplet(){
  char* nomdufichier =malloc(100 * sizeof(char));
  char* adresse = malloc(1000 * sizeof(char));

  FILE * ptr_adresse;
  FILE * ptr_fic;

  int reference;

  type_des descripteur = init_des();
  
  /*pour l'indexation complète on supprime les fichier pour recommencer a 0*/
  if(fopen("FILES/Descripteur","w")){
    system("rm FILES/Descripteur");
  }
  if(fopen("FILES/MotsCles","w")){
    system("rm FILES/MotsCles");
  } 

  ptr_adresse = fopen("FILES/NomDesFichiers","r");
  if(ptr_adresse !=NULL){
    while(fscanf(ptr_adresse,"%s",nomdufichier)==1){
      fscanf(ptr_adresse,"%d",&reference);

      /*fonction qui vient lire le chemin a la ligne 2*/
      Chemin_text = lirechemin();

      strcpy(adresse,Chemin_text);
      strcat(adresse,nomdufichier);

      FILE * ptr_fic;
      ptr_fic = fopen(adresse,"r");

      descripteur = FaireDescripteur(ptr_fic,reference);
      
      /*Ecrit dans le fichier Descripteur*/
      ecritureDescripteur(descripteur);
      
      /*Ecrit dans le fichier Mots-cles*/
      ecritureMotCles(descripteur);

    }
}else fprintf(stderr, "ERREUR pointeur Fichier nomDesFichiers\n");


free(nomdufichier);
free(adresse);

}

