#include "CommandeSysteme.h"


void listeDeFichiers(char *adresseDeBase,char *fichierDArriver){
	char commande[1024];
	strcpy(commande, "ls -l ");
	strcat(commande, adresseDeBase);
	strcat(commande, " >");
	strcat(commande, fichierDArriver);
	system(commande);
}

/*void EnleverBalise(char *AdresseDuFichier,char *fichierDArriver){
	char commande[1024];
	char adresse[1024];

	strcpy(commande, "sed 's/<[^<]*>//g' ");
	strcat(commande, AdresseDuFichier);
	strcat(commande, " >");
	strcat(commande, fichierDArriver);
	system(commande);
	//"'&~\"#{}()[]_^@°+$£¤%\!\§:/;.,?'"

	//char variable[]="'&~\"#{}()[]_`^@°+$£¤%!§:/;.,?'";
	strcpy(commande,"tr " );
	strcat(commande,"\"'\" ");
	strcat(commande,"\" \" < ");
	strcat(commande,fichierDArriver);
	strcat(commande," > test2.tmp && mv test2.tmp ");
	strcat(commande,fichierDArriver);
	system(commande);

	strcpy(commande,"tr " );
	strcat(commande,"\".,:\" ");
	strcat(commande,"\" \" < ");
	strcat(commande,fichierDArriver);
	strcat(commande," > test2.tmp && mv test2.tmp ");
	strcat(commande,fichierDArriver);
	system(commande);

	strcpy(commande,"tr " );
	strcat(commande,"\"()\" ");
	strcat(commande,"\" \" < ");
	strcat(commande,fichierDArriver);
	strcat(commande," > test2.tmp && mv test2.tmp ");
	strcat(commande,fichierDArriver);
	system(commande);

}*/

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
/*
int main(int argc, char *argv[]){

	char *adresseDeBase = "../Textes";
	char *adresseDeBase2 = "../Textes/05-Edition___les_mots_et.xml";
	char *fichierDArriver = "Test_file";
	char *fichierDArriver2 = "Test_file2";

	//NomDeFichiers(adresseDeBase, fichierDArriver);
	EnleverBalise(adresseDeBase2, fichierDArriver);
	CompterMot(fichierDArriver,fichierDArriver2);
	SupprimerFichier(fichierDArriver2);
	OuvrirFichier(adresseDeBase2);
return 0;
}*/


/*
char commande[1024];
	char adresse[1024];
	//strcpy(adresse,fichierDArriver);
	//strcat(adresse,"2");

	strcpy(commande, "sed 's/<[^<]*>//g' ");
	strcat(commande, AdresseDuFichier);
	strcat(commande, " >");
	strcat(commande, fichierDArriver);
	system(commande);

 */
