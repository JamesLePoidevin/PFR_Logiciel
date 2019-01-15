#include "Comparaison.h"

void ChoixDuFichier(){
	FILE *ptr_NomDesFichiers;
	char NomDesFichiers[1024][1024];
	int des[1024];
	int indice =0;
	int choix;

	printf("Veuillez choisir un des fichiers  \n");
	ptr_NomDesFichiers =fopen("../APPLICATION/FILES/NomDesFichiers","r");
	if(ptr_NomDesFichiers!=NULL){
		while(!feof(ptr_NomDesFichiers)){
			fscanf(ptr_NomDesFichiers,"%s %d",NomDesFichiers[indice],&des[indice]);
		indice ++;	//indice égal au nombre de fichiers 
	}
}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers\n" );
printf("%d\n",indice );
fclose(ptr_NomDesFichiers);
	//affichage des choix de fichier
for (int i = 0; i < indice-1;i++)
{
	printf("[%d] %s\n",i,NomDesFichiers[i]);
}
do{
	scanf("%d",&choix);
}while(choix>indice || choix <0);
system("clear");
printf("Les fichiers qui ont une ressemblence supérieur à 0 pourcent pour le fichier:\n %s\n",NomDesFichiers[choix] );

type_des A[indice-2];
for (int i = 0; i < indice; i++)
{
	A[i] = init_des();
}

FILE *ptr_Descripteur;
int indice1 =indice-1;
int i=0;
type_des B = init_des();

ptr_Descripteur =fopen("../APPLICATION/FILES/Descripteur","r");
if(ptr_Descripteur!=NULL){
	while(fscanf(ptr_Descripteur,"%d",&B.ref)==1){
		A[indice1].ref =B.ref;
		//printf("%d\n",B.ref );
		for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
		{	
			fscanf(ptr_Descripteur,"%s %d",B.tab[i].mot,&B.tab[i].occurence);
			//printf("%s %d\n", B.tab[i].mot,B.tab[i].occurence);
		}
		
		
		for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
		{
			strcpy(A[indice1].tab[i].mot,B.tab[i].mot);
			A[indice1].tab[i].occurence =B.tab[i].occurence ; 
		}
		indice1 --;
	}
}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers\n" );
fclose(ptr_Descripteur);

float pourcentage=0;
type_des comp = init_des(); 
comp = A[choix+1];

for (int i = 0; i < indice; i++){
	for (int j = 0; j < recuperer_Valuer_Descripteur(); j++){
		for (int k = 0; k < recuperer_Valuer_Descripteur(); k++){
			if(strcmp(A[i].tab[k].mot,comp.tab[j].mot)==0){
				//printf("\n%s %s\n",A[i].tab[k].mot,comp.tab[j].mot );
				pourcentage = pourcentage + (100/recuperer_Valuer_Descripteur());
			}
		}
	}
	if(pourcentage >0){
		//printf("%d\n", i);
		printf("%s %f\n",NomDesFichiers[i-1],pourcentage );
	}
	pourcentage =0;
}
//free(A);
//free(B);
	//return nbmot;
}