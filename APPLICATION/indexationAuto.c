#include "indexationAuto.h"

/**
 * fonction qui rajoute un descripteur dans le fichier FILES/Descripteur et les mots cles des 
 * descripteur dans le fichier ../APPLICATION/FILES/MotsCles	
 * @param A descripteur a ajouter
 */
void AjouterDES(type_des A){

	//poitneur de fichier
	FILE *ptr_FichierDes;
	FILE *ptrFichierMC;

	//ouverture des fichier ../APPLICATION/FILES/MotsCles et ../APPLICATION/FILES/Descripteur
	ptrFichierMC=fopen("../APPLICATION/FILES/MotsCles","a");
	ptr_FichierDes =fopen("../APPLICATION/FILES/Descripteur", "a");

	//si les fichiers ce sont bien ouvert
	if(ptrFichierMC != NULL && ptr_FichierDes != NULL){

		//on ecrit la reference dans le fichier mot cles
		fprintf(ptr_FichierDes,"%d\n",A.ref );

			//pour 0 jusqu'a nombre de mot on les ecrit a la suite dans ptr_FichierDes et ptrFichierMC
			for (int i = 0; i < recuperer_Valuer_Descripteur(); i++) {
				fprintf(ptr_FichierDes, "%s %d\n",A.tab[i].mot,A.tab[i].occurence);
				fprintf(ptrFichierMC, "%s %d\n",A.tab[i].mot,A.ref);
			}

			//message d'erreur
	}else fprintf(stderr, "ERREUR pointeur motslces ou Descripteur / indexationAUTO l.25\n");

	//fermeture des fichiers ouvert
	fclose(ptr_FichierDes);
	fclose(ptrFichierMC);
}


/**
 * fonction qui verifie si depuis le dernier lancement du programme il y a eu des descripteur Ajouter
 * @param CHEMIN des fichier a indexer
 */
void AjouteDESManquant(char* CHEMIN){

	char NomFichier[1024];
	char NomFichier1[1024];
	char commande[1024];
	char adresse[1000];

	int reference;
	int reference1;

	int etat=0;

	FILE * ptr_test;
	FILE * ptr_test1;

	//il de type_des 
	PILE p = init_PILE();

	//creer un fichier avec le nom des fichier dans le fichier NomDesFichiersaux et indice
	//correspond au nombre de fichier
	int indice = NomDesFichiers(CHEMIN,"NomDesFichiersaux");

	//ajouter descripteur manquant
	ptr_test =fopen("../APPLICATION/FILES/NomDesFichiersaux", "r");

	//si le fichier c'est bien ouvert
	if(ptr_test != NULL){
		//tant que le fichier n'est pas vide
		while ( !feof(ptr_test) ){


			fscanf(ptr_test, "%s %d",NomFichier,&reference);
			etat =0;

			//on ouvre l'ancien fichier des nomDEs Fichier
			ptr_test1 =fopen("../APPLICATION/FILES/NomDesFichiers", "r");

			//si le fichier est bien ouvert
			if(ptr_test1 != NULL){
				//tant qu'on a pas tous traiter
				while ( !feof(ptr_test1) ){
					//on stocke le nom du fichier et la reference
					fscanf(ptr_test1, "%s %d",NomFichier1,&reference1);
					//on compar pour voir si les fichier est dans les deux fichier
					if (strcmp(NomFichier,NomFichier1)==0){
						//si le fichier est deja indexer
						etat = 1;
					}
				}
			}
			fclose(ptr_test1);
			if (etat ==0)	//Si le fichier n'est pas trouver dans l'ancienne liste
			{
				ptr_test1 =fopen("../APPLICATION/FILES/NomDesFichiers", "a");
				printf("Le fichier %s a été ajouté\n",NomFichier );
				fprintf(ptr_test1, "%s %d\n",NomFichier,reference1+1);
				strcpy(adresse,CHEMIN);
				strcat(adresse,NomFichier);

				type_des A = init_des();
				FILE * ptr_adresse;
				ptr_adresse = fopen(adresse,"r");

				A = FaireDescripteur(ptr_adresse,reference1+1);
				AjouterDES(A);
				fclose(ptr_test1);

			}

		}
	}
	fclose(ptr_test);
}

void SuppresionDESEnTrop(char* CHEMIN){
	FILE *ptr_test1;
	FILE *ptr_test2;
	char NomFichier[1024];
	char NomFichier1[1024];
	char commande[1024];
	int reference;
	int reference1;
	int etat;
	//suppresion des descripteurs en trop
	ptr_test1 =fopen("../APPLICATION/FILES/NomDesFichiers", "r");
	if(ptr_test1 != NULL){
		while ( !feof(ptr_test1) ){
			fscanf(ptr_test1, "%s %d",NomFichier,&reference);
			etat = 0;
			FILE *ptr_test3;
			ptr_test3 =fopen("../APPLICATION/FILES/NomDesFichiersaux", "r");
			if(ptr_test3 != NULL){
				while ( !feof(ptr_test3) ){
					fscanf(ptr_test3, "%s %d",NomFichier1,&reference1);
					if (strcmp(NomFichier,NomFichier1)==0)
					{
						etat = 1;
					}
				}
				fclose(ptr_test3);
			}
			
			if (etat ==0)
			{
				int ligne;
				char aux[1024];
				sprintf(aux, "%d",reference);
				printf("Le fichier %s sera supprimé\n",NomFichier );
				strcpy(commande,"grep -x -n ");
				strcat(commande,aux);
				strcat(commande," FILES/Descripteur > test.tmp");
				system(commande);

				strcpy(commande,"cut -f1 -d ':' test.tmp > test1.tmp");
				system(commande);

				ptr_test2 =fopen("../APPLICATION/test1.tmp", "r");
				if(ptr_test2 != NULL){
					while ( !feof(ptr_test2) ){
						fscanf(ptr_test2,"%d",&ligne);
					}
				}
				fclose(ptr_test2);

				char aux1[1024];
				char aux2[1024];
				char aux3[1024];

				sprintf(aux1,"%d",ligne);
				sprintf(aux2, "%d",ligne +recuperer_Valuer_Descripteur());
				
				strcpy(commande,"sed '");
				strcat(commande,aux1);
				strcat(commande,",");
				strcat(commande,aux2);
				strcat(commande,"d' FILES/Descripteur>Descripteur.tmp && mv Descripteur.tmp FILES/Descripteur");
				
				system(commande);
				
				sprintf(aux3," %s",aux);

				strcpy(commande, "sed '");
				strcat(commande, aux);
				strcat(commande, "d' FILES/NomDesFichiers > NomDesFichiers.tmp && mv NomDesFichiers.tmp FILES/NomDesFichiers");
				
				system(commande);

				FILE *ptr_MC1;
				FILE *ptr_MC2;
				char MC[1024];
				int referenceaux;

				ptr_MC1 = fopen("../APPLICATION/FILES/MotsCles","r");
				ptr_MC2 = fopen("../APPLICATION/FILES/MotsCles.tmp","w");

				if(ptr_MC1 != NULL){
					while (!feof(ptr_MC1)){
						fscanf(ptr_MC1, "%s %d",MC,&referenceaux);
						if(reference != referenceaux){
							fprintf(ptr_MC2, "%s %d\n",MC,referenceaux);
						}
					}
				}
				fclose(ptr_MC1);
				fclose(ptr_MC2);
				system("mv ../APPLICATION/FILES/MotsCles.tmp ../APPLICATION/FILES/MotsCles");
			}
		}
	}
	fclose(ptr_test1);
}

void IndexationAutomatique(char* CHEMIN){
	AjouteDESManquant(CHEMIN);
	SuppresionDESEnTrop(CHEMIN);
	system("rm FILES/NomDesFichiersaux");	
}
