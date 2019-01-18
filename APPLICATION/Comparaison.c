#include "Comparaison.h"

void ChoixDuFichier(){
//Déclaration des varible
	//pointeur fichier pour le fichier avec les nom des fichier et le num de descripteur correspondant
	FILE *ptr_NomDesFichiers; 

	char NomDesFichiers[1024][1024];
	
	int des[1024];

	int indice =0;
	int choix;

	//message de départ
	printf("Veuillez choisir un des fichiers  \n");

	ptr_NomDesFichiers =fopen("../APPLICATION/FILES/NomDesFichiers","r");
	
	//si le fichier existe et peut etre ouvert
	if(ptr_NomDesFichiers!=NULL){
		while(!feof(ptr_NomDesFichiers)){
			//lire le nom de chaque fichier et le numero de descripteur et les met dans deux tableau au meme indice
			fscanf(ptr_NomDesFichiers,"%s %d",NomDesFichiers[indice],&des[indice]);

			//indice égal au nombre de fichiers - 1 pour la case 0
			indice ++;	 
		}
	}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers (Comparaison.c l.25)\n" ); //sinon affichier erreur
	fclose(ptr_NomDesFichiers); //fermer le pointeur de fichier


	//affichage des choix de fichier
	for (int i = 0; i < indice-1;i++){

		// afficher le nom des fichiers et un numero que l'utiliseur dois rentrer pour choisir le fichier
		printf("[%d] %s\n",i,NomDesFichiers[i]);
	}

	//sécuriser la saisi pour faire en sorte que l'utilisateur choisi un numero contenu entre 0 et indice
	do{
		//scan les choix entrer au clavier
		scanf("%d",&choix);

	}while(choix>indice || choix <0);	//tant que c'est pas entre 0 et indice

system("clear"); //enleve ce qu'il y a sur le terminale

printf("Les fichiers qui ont une ressemblence supérieur à 0 pourcent pour le fichier:\n %s\n",NomDesFichiers[choix] );

/*A refaire*/
//Liste de descripteur
type_des listeDescripteur[indice-2];

for (int i = 0; i < indice; i++)
{
	listeDescripteur[i] = init_des();
}
/*Car prend le descripteur*/

//pointeur vers le fichier aves les déscripteur
FILE *ptr_Descripteur;

//Nouvelle indice avec un descripteur de moins(celui a comparer)
int indice1 =indice-1;

//Descripteur auxiliaire pour placer les descrpteur lors de la comparaison
type_des Auxiliaire = init_des();

ptr_Descripteur =fopen("../APPLICATION/FILES/Descripteur","r"); //ouverture du fichier avec les descripteur
if(ptr_Descripteur!=NULL){	//si le fichier c'est bien ouvert
	//tant qu'il y a encore des de
	while(fscanf(ptr_Descripteur,"%d",&Auxiliaire.ref)==1){
		listeDescripteur[indice1].ref =Auxiliaire.ref;
		for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
		{	
			fscanf(ptr_Descripteur,"%1023s%d",Auxiliaire.tab[i].mot,&Auxiliaire.tab[i].occurence);
		}
		
		
		for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
		{
			strcpy(listeDescripteur[indice1].tab[i].mot,Auxiliaire.tab[i].mot);
			listeDescripteur[indice1].tab[i].occurence =Auxiliaire.tab[i].occurence ; 
		}
		indice1 --;
	}
}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers\n" );
fclose(ptr_Descripteur);

float pourcentage=0;
type_des comp = init_des(); 
comp = listeDescripteur[choix+1];

//calcule
//A ranger
for (int i = 0; i < indice; i++){
	for (int j = 0; j < recuperer_Valuer_Descripteur(); j++){
		for (int k = 0; k < recuperer_Valuer_Descripteur(); k++){
			if(strcmp(listeDescripteur[i].tab[k].mot,comp.tab[j].mot)==0){
				pourcentage = pourcentage + (100/recuperer_Valuer_Descripteur());
			}
		}
	}
	if(pourcentage >0 && i != des[choix]){
		printf("%s %f\n",NomDesFichiers[i-1],pourcentage );
	}
	pourcentage =0;
 }
}