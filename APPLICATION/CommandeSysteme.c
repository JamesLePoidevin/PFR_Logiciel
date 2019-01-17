#include "CommandeSysteme.h"


void listeDeFichiers(char *adresseDeBase,char *fichierDArriver){
	char commande[1024];
	strcpy(commande, "ls -l ");
	strcat(commande, adresseDeBase);
	strcat(commande, " >");
	strcat(commande, fichierDArriver);
	system(commande);
}


void CompterMot(char *AdresseDuFichier,char *fichierDArriver){
	char commande[1024];
	strcpy(commande, "wc -w ");
	strcat(commande, AdresseDuFichier);
	strcat(commande, " > ");
	strcat(commande, fichierDArriver);
	system(commande);
}

void SupprimerFichier(char *AdresseDuFichier){
	char commande[1024];
	strcpy(commande, "rm ");
	strcat(commande, AdresseDuFichier);
	system(commande);
}

void OuvrirFichier(char *AdresseDuFichier){
	char commande[1024];
	strcpy(commande, "gedit ");
	strcat(commande, AdresseDuFichier);
	system(commande);
}

void clean(){
	remove("NombreDeMotFichier");
	remove("nbmot");
	remove("FichierAux1");
	remove("descripteur");
	remove("adresse");
	remove("FILES/NomDeFichieraux");
	system("make clean");


}
