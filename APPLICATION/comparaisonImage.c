#include "comparaisonImage.h"

int AffichageFichier(){
	FILE *ptr_NomDesFichiers;
	char NomDesFichiers[1024][1024];
	int des[1024];
	int indice;
	int choix;

	printf("Veuillez choisir un des fichiers  \n");
	ptr_NomDesFichiers =fopen("../APPLICATION/FILES/NomDesFichiersImage","r");
	if(ptr_NomDesFichiers!=NULL){
		while(!feof(ptr_NomDesFichiers)){
			fscanf(ptr_NomDesFichiers,"%s %d",NomDesFichiers[indice],&des[indice]);
		indice ++;	//indice égale au nombre de fichiers 
	}
}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers\n" );
//printf("%d\n",indice );

fclose(ptr_NomDesFichiers);
for (int i = 0; i < indice-1;i++)
{
	printf("[%d] %s\n",i,NomDesFichiers[i]);
}
do{
	scanf("%d",&choix);
}while(choix>indice || choix <0);
return des[choix];
}

float min(float a , float b){
	if(a < b){
		return a;
	}else return b;
}

void triTableauResultat(type_resultat* res ,int taille){
	type_resultat temporary; 
	for(int j = 0; j < taille; j++){
		for(int i = 0; i <taille-1;i++){
			if(res[i].sim> res[i+1].sim)
			{
				temporary = res[i];
				res[i] = res[i+1];
				res[i+1] = temporary;
			}
		}
	} 
}

int calculeSimilitudeNB(PILENB P1,type_resultat* res,type_descNB A){
	int ind =0;
	type_descNB AUX;
	while(PILE_estVideNB(P1) !=1){
		P1 = dePILENB(P1,&AUX);
		res[ind].id = AUX.ref;
		res[ind].sim = (int)min(AUX.tab[0],A.tab[0]) + (int)min(AUX.tab[1],A.tab[1]);
		ind ++;
	}
	return ind;
}

void compair(int choix){

	FILE *ptr_NomDesFichiers;
	char NomDesFichiers[1024][1024];
	int des[1024];
	int indice;

	ptr_NomDesFichiers =fopen("../APPLICATION/FILES/NomDesFichiersImage","r");
	if(ptr_NomDesFichiers!=NULL){
		while(!feof(ptr_NomDesFichiers)){
			fscanf(ptr_NomDesFichiers,"%s %d",NomDesFichiers[indice],&des[indice]);
		indice ++;	//indice égal au nombre de fichiers 
	}
}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers\n" );


fclose(ptr_NomDesFichiers);

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

ptrImageNB =fopen("../APPLICATION/FILES/DescripteurImageNB","r");
if(ptrImageNB!=NULL){
	while(fscanf(ptrImageNB,"%d",&id)==1){
		if(id == choix){
			A.ref = id;
			fscanf(ptrImageNB,"%f%f",&A.tab[0],&A.tab[1]);
			NB=1;
		}else{
			AUX.ref = id;
			fscanf(ptrImageNB,"%f%f",&AUX.tab[0],&AUX.tab[1]);
			P1 =emPILENB(P1,AUX);
			nbrNB++;
		} 
	}
}else fprintf(stderr, "ERREUR pointeur DescripteurImageNB\n");
fclose(ptrImageNB);
	//printf("%f%f\n",A.tab[0],A.tab[1] );

if(NB == 1){
	
	//Calcul de la similitude 
	type_resultat* res = malloc(nbrNB*sizeof(type_resultat));
	int ind = calculeSimilitudeNB(P1,res,A);

	//Tri du tableau des resultats par ordre croissant pour être affiché dans
	//l'ordre décroissant
	triTableauResultat(res,ind);

	//Affichage dans l'ordre décroissant 
	printf("Voici la liste des fichiers dans l'ordre:\n");
	for (int j = ind-1; j >ind-6 ; j--){
		for (int i = 0; i < indice-1; i++){
			if (des[i]==res[j].id){
				printf("%s %d\n",NomDesFichiers[i],res[j].sim);
			}
		}
	}
}else
{
	ptrImageRGB =fopen("../APPLICATION/FILES/DescripteurImageRGB","r");
	if(ptrImageRGB!=NULL){
		while(fscanf(ptrImageRGB,"%d",&id)==1){
			if(id == choix){
				B.ref = id;
				for (int i = 0; i < 64; i++)
				{
					fscanf(ptrImageRGB,"%f",&B.tab[i]);
				}
				NB=2;
			}else{
				AUX2.ref = id;
				for (int i = 0; i < 64; i++)
				{
					fscanf(ptrImageRGB,"%f",&AUX2.tab[i]);
				}
				P2 =emPILERGB(P2,AUX2);
				nbrRGB++;
			} 
		}
	}else fprintf(stderr, "ERREUR pointeur DescripteurImageRGB\n");
	fclose(ptrImageRGB);

	//Tant que la pile n'est pas vide on calcule la similitude
	int ind =0;
	type_resultat *res = malloc(nbrRGB*sizeof(type_resultat)); 
	while(PILE_estVideRGB(P2) !=1){	//Tant que la pile n'est pas vide
		P2 = dePILERGB(P2,&AUX2);
		res[ind].id = AUX2.ref;
		res[ind].sim = 0;
		for (int i = 0; i < 64; i++){
			res[ind].sim = res[ind].sim + (int)min(AUX2.tab[i],B.tab[i]);
		}
		ind ++;
	}


	//Tri du tableau des resultats par ordre croissant pour être affiché dans
	//l'ordre décroissant
	triTableauResultat(res,ind);

	//Affichage dans l'ordre décroissant 
	printf("Voici la liste des fichiers dans l'ordre:\n");
	for (int j = ind-1; j >ind-6 ; j--){
		for (int i = 0; i < indice-1; i++){
			if (des[i]==res[j].id){
				printf("%s %d\n",NomDesFichiers[i],res[j].sim);
			}
		}
	}
}
}


