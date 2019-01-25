//////////////////////////////////////////////////////////////////
//Auteur : James Le Poidevin									//
//																//
//Comparaison Image 											//
//Description: Fichier principale pour la comparaison d'image   //
//																//
//////////////////////////////////////////////////////////////////

#include "comparaisonImage.h"


/**
 * Tester qu'on rentre pas un mauvaise valeur quand on demande un entier
 * @return l'entier choisi
 */
int test_entier(){
	char nombre[50] = "";
	int num = 0;
	char zero[] = "0";

	scanf("%s", nombre);

	if (atoi(nombre) == 0 && strcmp(zero, nombre) != 0){
		return -1;
	}
	else return atoi(nombre);
}

/**
 * Lire le pourcentage necesaire pour affichier le similitude
 */
int lirepourcentage(){

	int pourcentage_nb;

	system("sed '4,4!d' Param/param_comparaison > file.tmp");


	FILE *ptr_fichierTEMP;

	ptr_fichierTEMP =fopen("file.tmp","r");
	if(ptr_fichierTEMP !=NULL){
		fscanf(ptr_fichierTEMP,"%d",&pourcentage_nb);
	}else fprintf(stderr, "ERREUR pointeur file.tmp\n");
	return pourcentage_nb;

}


/**
 * Lit le seuil pour minimum pour affichier un texte RGB
 * @return le seuil
 */
int lirepourcentageRGB(){
	int pourcentage_RGB;

	system("sed '6,6!d' Param/param_comparaison > file.tmp");


	FILE *ptr_fichierTEMP;

	ptr_fichierTEMP =fopen("file.tmp","r");
	if(ptr_fichierTEMP !=NULL){
		fscanf(ptr_fichierTEMP,"%d",&pourcentage_RGB);
	}else fprintf(stderr, "ERREUR pointeur file.tmp\n");
	return pourcentage_RGB;
}

/**
 * Focntion qui affiche tous les fichier possible pour la comparaison
 * @return renvoi le numero de descripteur correspondant au choix fait par l'utilisateur
 */
int AffichageFichier(){

	FILE *ptr_NomDesFichiers;
	
	//nom des fichiers lu dans NomDesFichiersImage 
	char NomDesFichiers[1024][1024];
	
	//Tableau avec tous les numero de descrpteur en focntion de leur nom dans NomDesFichiers
	int des[1024];


	int indice =0;
	int choix;

	
	ptr_NomDesFichiers =fopen("../APPLICATION/FILES/NomDesFichiersImage","r");
	if(ptr_NomDesFichiers!=NULL){

		//tant qu'il y a des chose dans le fichier
		while(!feof(ptr_NomDesFichiers)){
			
			//Lit le nom du fichier et le numero du descripteur correspondant et 
			//place dans les tableau
			fscanf(ptr_NomDesFichiers,"%s%d",NomDesFichiers[indice],&des[indice]);
			indice ++;	//indice égale au nombre de fichiers 
		}
	}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers\n" );

	//fermeture du pointeur NomDesFichier
	fclose(ptr_NomDesFichiers);


	for (int i = 0; i < indice-1;i++){
		//affichier un numero suivie du nom du fichier
		printf("[%d] %s\n",i,NomDesFichiers[i]);
	}

	printf("Veuillez choisir un des fichiers en entrant le numéro de gauche : ");


	do{ 

		//Lit la valeur saisi par l'utilisateur
		choix = test_entier();

	}while(choix>indice || choix <0); //tantqu'il est superieur au nombre de fichier et inferieur a 0

	//renvoie le numero du descrpteur choisi
	return des[choix];
}


/**
 * renvoie le plus petit des deux nombre
 * @param  a nombre 1
 * @param  b nombre 2
 * @return   Le plus petit des nombre
 */
float min(float a , float b){
	if(a < b){

		return a;

	}else return b;
}

/**
 * Tri un tableau passer en parametre
 * @param res    tableau  de resultat a trier
 * @param taille taille du tableau
 */
void triTableauResultat(type_resultat* res ,int taille){
	//type_resultat auxiliaire pour le changement
	type_resultat temporary; 


	for(int j = 0; j < taille; j++){
		for(int i = 0; i <taille-1;i++){
			
			//si case de res superieur a la case suivante les deux case change de place 
			if(res[i].sim> res[i+1].sim)
			{
				temporary = res[i];		//echange de passe a deux type_resultat
				res[i] = res[i+1];		//echange de passe a deux type_resultat
				res[i+1] = temporary;	//echange de passe a deux type_resultat
			}
		}
	} 
}


/**
 * Calcule la similitude entre un descrpteur passer en parametre (Fichier a comparer) avec tous les descripteur
 * d'une pile de descripteur
 * @param  P1  Pile remplit avec tous les descripteurs du systeme
 * @param  res tableau avec tous les resultat de similitude
 * @param  A   Descripteur a comparer avec tous les autre
 * @return     le nomnbre d'élement dans le tableau de res
 */
int calculeSimilitudeNB(PILENB P1,type_resultat* res,type_descNB A){
	//nombre d'élement dans res
	int ind =0;

	//type_descNB 
	type_descNB AUX;

	//Tant qu la pile n'est pas vide
	while(PILE_estVideNB(P1) !=1){
		P1 = dePILENB(P1,&AUX);
		res[ind].id = AUX.ref;
		res[ind].sim = (int)min(AUX.tab[0],A.tab[0]) + (int)min(AUX.tab[1],A.tab[1]);
		ind ++;
	}
	return ind;
}

/**
 * Ouverture d'un image NB avec feh
 * @param nom le tire du fichier a ouvertir
 */
void ouvrirImageNB(char * nom){
	char nomFic[50];
	char chemin[150];
	strcpy(nomFic,nom);
	

	char * mot = strtok(nomFic,".");	
	strcat(mot,".bmp");

	strcpy(chemin,"feh ");
	strcat(chemin,cheminImage());
	strcat(chemin,mot);
	strcat(chemin," &");

	system(chemin);
}

/**
 * Ouverture d'un image RGB avec feh
 * @param nom le tire du fichier a ouvertir
 */
void ouvrirImageRGB(char * nom){
	char nomFic[50];
	char chemin[150];
	strcpy(nomFic,nom);
	

	char * mot = strtok(nomFic,".");	
	strcat(mot,".jpg");

	strcpy(chemin,"feh ");
	strcat(chemin,cheminImage());
	strcat(chemin,mot);
	strcat(chemin," &");

	system(chemin);
}

void compair(int choix){

	FILE *ptr_NomDesFichiers;
	char NomDesFichiers[1024][1024];
	int des[1024];
	int indice;

	ptr_NomDesFichiers =fopen("../APPLICATION/FILES/NomDesFichiersImage","r");
	if(ptr_NomDesFichiers!=NULL){
		while(fscanf(ptr_NomDesFichiers,"%s",NomDesFichiers[indice])==1){
			fscanf(ptr_NomDesFichiers,"%d",&des[indice]);
		indice ++;	//indice égal au nombre de fichiers 
	}
}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers\n" );

fclose(ptr_NomDesFichiers);

//Déclaration des variable
FILE *ptrImageNB;
FILE *ptrImageRGB;

int id;
float tab1[2];
float tab2[64];
int NB = 0;

type_descNB AUX;
type_descNB A;
PILENB P1 = init_PILENB();
int nbrNB =0;

type_descRGB AUX2;
type_descRGB B;
PILERGB P2 = init_PILERGB();
int nbrRGB =0;

//ouverture du fichier avec les descripteur RGB
ptrImageNB =fopen("../APPLICATION/FILES/DescripteurImageNB","r");

//si le fichier c'est bien ouvert
if(ptrImageNB!=NULL){

	//tant qu'il y a des chose a scaner dans le fichier
	while(fscanf(ptrImageNB,"%d",&id)==1){

		// si l'id du descripteur correspond a chois
		if(id == choix){
			//on rempli le descripteur A
			A.ref = id;	
			fscanf(ptrImageNB,"%f%f",&A.tab[0],&A.tab[1]);

			NB=1; //indique le l'image a comparer est NB
		}else{ 
			//on rempli le descripteur Auxilaire
			AUX.ref = id;
			fscanf(ptrImageNB,"%f%f",&AUX.tab[0],&AUX.tab[1]);
			
			//on empile de descripteur pour etre traiter plus tard
			P1 =emPILENB(P1,AUX);

			//increment le nombre d'element dans pile
			nbrNB++;
		} 
	}
}else fprintf(stderr, "ERREUR pointeur DescripteurImageNB\n");
fclose(ptrImageNB);


if(NB == 1){	//si le fichier a comparer est Noir et blance
	
	//Calcul de la similitude 
	type_resultat* res = malloc(nbrNB*sizeof(type_resultat));
	int ind = calculeSimilitudeNB(P1,res,A);

	//Tri du tableau des resultats par ordre croissant pour être affiché dans
	//l'ordre décroissant
	triTableauResultat(res,ind);

	for (int i = 0; i < nbrNB; i++)
	{
		printf("%d %d \n",res[i].id,res[i].sim );
	}

	system("clear");

	int pourcentage_nb = lirepourcentage();


	int in = 1;
	//Affichage dans l'ordre décroissant 
	printf("Voici la liste des fichiers dans l'ordre:\n");
	for (int j = ind-1; j >0 ; j--){
		for (int i = 0; i < indice-1; i++){
			if(res[j].sim> pourcentage_nb){
				if (des[i]==res[j].id){
					printf("[%d] %s %d\n",in,NomDesFichiers[i],res[j].sim);
					in ++;
				}
			}
		}
	}

	int boolean;
	if(in != 0){
		do{
			do{
				printf("\nQuel fichier voulez-vous visualiseR?\nVeuillez rentrer le numero à gauche \n [0] pour quitter \n");

		//lit le choix de l'utilisateur
				boolean = test_entier();

			}while(boolean < 0 || boolean > in);
			if(boolean != 0){

			//affichage du texte choisi
				int choix1;

				for (int i = 0; i < indice-1; i++){
					if(choix == des[i]){
						choix1 = i;
					}
				}
				printf("%d\n", choix1);

				ouvrirImageNB(NomDesFichiers[choix1]);

				for (int i = 0; i < indice-1; i++){
					if (des[i]==res[ind-boolean].id){
						ouvrirImageNB(NomDesFichiers[i]);
					}
				}
			}
		}while(boolean != 0);
	}else printf("Il n'y a aucune fichier correspondant\n");sleep(2);

}else		//si l'image a comparer est rouge vert et bleu
{
	//ouverture du fichier avec les descripteur RGB
	ptrImageRGB =fopen("../APPLICATION/FILES/DescripteurImageRGB","r");

	//si le fichier c'est bien ouvert
	if(ptrImageRGB!=NULL){

		//tant qu'il y a des chose a scaner dans le fichier
		while(fscanf(ptrImageRGB,"%d",&id)==1){

			// si l'id du descripteur correspond a chois
			if(id == choix){

				//on rempli le descripteur Auxilaire
				B.ref = id;
				for (int i = 0; i < 64; i++){
					fscanf(ptrImageRGB,"%f",&B.tab[i]);
				}

				//indique le l'image a comparer est RGB
				NB=2;

			}else{

				//on rempli le descripteur Auxilaire
				AUX2.ref = id;
				for (int i = 0; i < 64; i++){
					fscanf(ptrImageRGB,"%f",&AUX2.tab[i]);
				}

				//on empile de descripteur pour etre traiter plus tard
				P2 =emPILERGB(P2,AUX2);

				//increment le nombre d'element dans pile
				nbrRGB++;
			} 
		}
	}else fprintf(stderr, "ERREUR pointeur DescripteurImageRGB\n");
	fclose(ptrImageRGB);

	//Tant que la pile n'est pas vide on calcule la similitude
	int ind =0;
	type_resultat *res = malloc(nbrRGB*sizeof(type_resultat)); 
	while(PILE_estVideRGB(P2) !=1){	//Tant que la pile n'est pas vide

		//on depile la pile et le place dans un type_descRGB auxiliaire
		P2 = dePILERGB(P2,&AUX2);

		//on remplit le tableau de resultat
	res[ind].id = AUX2.ref;
	res[ind].sim = 0;

		//calcule de la similitude
	for (int i = 0; i < 64; i++){
		res[ind].sim = res[ind].sim + (int)min(AUX2.tab[i],B.tab[i]);
	}
	ind ++;
}

system("clear");
	//Tri du tableau des resultats par ordre croissant pour être affiché dans
	//l'ordre décroissant
triTableauResultat(res,ind);

int in = 1;

int valeursim = lirepourcentageRGB();

	//Affichage dans l'ordre décroissant 
printf("Voici la liste des fichiers dans l'ordre:\n");
for (int j = ind-1; j >0 ; j--){
	for (int i = 0; i < indice-1; i++){
		if(valeursim < res[j].sim){
			if (des[i]==res[j].id){
				printf("[%d] %s %d\n",in,NomDesFichiers[i],res[j].sim);
				in ++;
			}
		}
	}
}

int boolean;

if(in != 0){
do{

	do{

		printf("\nQuel fichier voulez vous visualiser?\n Veuillez rentrer le numero à gauche : \n [0] pour quitter \n");
			//lit le choix de l'utilisateur

		boolean = test_entier();

	}while(boolean < 0 || boolean > in);
	if(boolean != 0){

		//affichage du texte choisi
		int choix1;

		for (int i = 0; i < indice-1; i++){
			if(choix == des[i]){
				choix1 = i;
			}
		}
		printf("%d\n", choix1);

		ouvrirImageRGB(NomDesFichiers[choix1]);
		for (int i = 0; i < indice-1; i++){
			if (des[i]==res[ind-boolean].id){
				ouvrirImageRGB(NomDesFichiers[i]);
			}
		}
	}
}while(boolean != 0);
}else printf("Il n'y a aucune fichier correspondant\n");sleep(2);
}
}


