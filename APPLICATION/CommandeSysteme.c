#include "CommandeSysteme.h"

/**
 * Crée une liste des fichiers dans un dossier et passe la liste dans un fichier
 * @param adresseDeBase   adresse du dossier où se trouvent les fichiers
 * @param fichierDArriver fichier à placer dans la liste
 */
void listeDeFichiers(char *adresseDeBase,char *fichierDArriver){
	char commande[1024];
	strcpy(commande, "ls -l ");
	strcat(commande, adresseDeBase);
	strcat(commande, " >");
	strcat(commande, fichierDArriver);
	system(commande);
}

/**
 * lit le pourcentage nécessaire pour afficher les fichiers 
 * @return le pourcentage de comparasion
 */
int lireparametrecompar(){

  int paramcomp;

  system("sed '2,2!d' Param/param_comparaison > file.tmp");
  

  FILE *ptr_fichierTEMP;

  ptr_fichierTEMP =fopen("file.tmp","r");
  if(ptr_fichierTEMP !=NULL){
    fscanf(ptr_fichierTEMP,"%d",&paramcomp);
  }else fprintf(stderr, "ERREUR pointeur file.tmp / CommandeSysteme l.30\n");
  fclose(ptr_fichierTEMP);

  system("rm file.tmp");

  return paramcomp;

}

/**
 * Compte les mots dans un fichier et place le nombre dans un fichier secondaire
 * @param AdresseDuFichier adresse du fichier à compter
 * @param fichierDArriver  adresse du fichier où on place le nombre de mots
 */
void CompterMot(char *AdresseDuFichier,char *fichierDArriver){
	char commande[1024];
	strcpy(commande, "wc -w ");
	strcat(commande, AdresseDuFichier);
	strcat(commande, " > ");
	strcat(commande, fichierDArriver);
	system(commande);
}


/**
 * supprime un fichier passer en paramètre 
 * @param AdresseDuFichier adresse du fichier à ouvrir
 */
void SupprimerFichier(char *AdresseDuFichier){
	char commande[1024];
	strcpy(commande, "rm ");
	strcat(commande, AdresseDuFichier);
	system(commande);
}


/**
 * Ouvre un fichier passé en paramètre 
 * @param AdresseDuFichier adresse du fichier à ouvrir
 */
void OuvrirFichier(char *AdresseDuFichier){
	char commande[1024];
	strcpy(commande, "gedit ");
	strcat(commande, AdresseDuFichier);
	system(commande);
}


/**
 * Supprime les fichiers en trop/temporaire
 */
void clean(){
	remove("NombreDeMotFichier");
	remove("nbmot");
	remove("FichierAux1");
	remove("descripteur");
	remove("adresse");
	remove("FILES/NomDeFichieraux");
	system("make clean");


}
