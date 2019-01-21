#include "CommandeSysteme.h"

/**
 * creer un liste des fichier dans un dossier et passe la liste dans un fichier
 * @param adresseDeBase   adresse du dossier a lister les fichier
 * @param fichierDArriver fichier a placer la liste
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
 * lire le pourcentage nécessaire pour afficher les fichier 
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
 * Compte les mot dans un fichier et place le nombre dans un fichier secondaire
 * @param AdresseDuFichier adresse du fichier a compter
 * @param fichierDArriver  adresse du fichier ou on place le nombre de mot
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
 * supprime un fichier passer en parametre 
 * @param AdresseDuFichier adresse du fichier a ouvrir
 */
void SupprimerFichier(char *AdresseDuFichier){
	char commande[1024];
	strcpy(commande, "rm ");
	strcat(commande, AdresseDuFichier);
	system(commande);
}


/**
 * Ouvre un fichier passer en parametre 
 * @param AdresseDuFichier adresse du fichier a ouvrir
 */
void OuvrirFichier(char *AdresseDuFichier){
	char commande[1024];
	strcpy(commande, "gedit ");
	strcat(commande, AdresseDuFichier);
	system(commande);
}


/**
 * Supprime les fichier en trop/temporaire
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
