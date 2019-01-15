
#include "Comparaison.h"

//char *CHEMIN = "../Textes/";		//A venir lire dans le fichier de config 

int main(int argc, char *argv[]){
	//Lecture du chemin
	char *CHEMIN = malloc(1000*sizeof(char));
	FILE * ptr_Chemin;
	ptr_Chemin = fopen("../Source/FILES/CHEMIN","r");
	if(ptr_Chemin != NULL){
		fscanf(ptr_Chemin,"%s",CHEMIN);
	}else fprintf(stderr, "Erreur pointeur chemin\n");

	int choix = 0;
	system("clear");
	printf("%s\n", CHEMIN);
	printf("[1] Mode Automatique \n[2] Mode Manuel\n[3] Comparaison \nVeuillez entrer votre choix :\n");
	do{
		scanf("%d",&choix);
	}while(choix != 1 && choix != 2 && choix !=3);
	if(choix == 1){
		if (fopen("../Source/FILES/Descripteur","r")!=NULL && fopen("../Source/FILES/MotsCles","r")!=NULL && fopen("../Source/FILES/NomDesFichiers","r")!=NULL){
			printf("Le Mode Automatique a choisi une Indexation Partielle\n");
			IndexationAutomatique(CHEMIN);
		}else if(fopen("../Source/FILES/Descripteur","r")==NULL || fopen("../Source/FILES/MotsCles","r")==NULL || fopen("../Source/FILES/NomDesFichiers","r")==NULL){
			IndexationComplet(CHEMIN); 
			printf("Le Mode Automatique a choisi une Indexation Complète car il manquait des fichiers importants\n");
		}
	}else if(choix == 2){
		system("clear");
		printf("[1] Indexation Partielle \n[2] Indexation Complete\nVeuillez entrer votre choix :\n");
		do{
			scanf("%d",&choix);
		}while(choix != 1 && choix != 2);
		if (choix == 1)
		{
			IndexationAutomatique(CHEMIN);
		}else IndexationComplet(CHEMIN);
	}else if(choix == 3){
		//printf("Veuillez patienter pendant qu'on recherche des nouveaux fichiers");
		//IndexationComplet(CHEMIN);
		system("clear");
		ChoixDuFichier();
	}
	clean();
	//system("rm *.tmp");
	return 0;
}
