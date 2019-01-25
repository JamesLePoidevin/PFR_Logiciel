///////////////////////////////////////////////////////////////////////
//Auteur : James Le Poidevin										 //
//																	 //
//Comparaison Texte													 //
//Description: Fichier principale pour la comparaison de TEXTE		 //
//																	 //
///////////////////////////////////////////////////////////////////////

#include "Comparaison.h"

/**
 * Fonction qui sert à trier le tableau des resultats dans l'ordre croissant
 * Très similaire à triTableauResultat avec comme seule difference le type resultat
 * @param tab    tableau à trier
 * @param taille taille du tableau à trier
 */
void triTableauResultat1(type_resultattext* tab ,int taille){
//variables pour les for
	int i, j;

	for (i = 0; i < taille; i++) { //pour chque case du tableau

		type_resultattext elem; //element intermedaire
		elem.id = tab[i].id;	//prend les valeurs de chaque case l'un après l'autre
		elem.sim = tab[i].sim;	//prend les valeurs de chaque case l'un après l'autre

		for (j = i; j > 0 && tab[j-1].sim > elem.sim; j--){
			tab[j].sim = tab[j-1].sim;
			tab[j].id = tab[j-1].id;
		}
		tab[j].sim = elem.sim;
		tab[j].id = elem.id;
	}
}

void ChoixDuFichier(){
//Déclaration des variables
	//pointeur fichier pour le fichier avec les noms des fichiers et le num de descripteur correspondant
	FILE *ptr_NomDesFichiers; 

	char NomDesFichiers[1024][1024];
	
	int des[1024];

	int indice =0;
	int choix;

	//message de départ
	

	ptr_NomDesFichiers =fopen("../APPLICATION/FILES/NomDesFichiers","r");
	
	//si le fichier existe et peut être ouvert
	if(ptr_NomDesFichiers!=NULL){
		while(!feof(ptr_NomDesFichiers)){
			//lit le nom de chaque fichier et le numero de descripteur et les met dans deux tableaux au même indice
			fscanf(ptr_NomDesFichiers,"%s %d",NomDesFichiers[indice],&des[indice]);

			//indice égal au nombre de fichiers - 1 pour la case 0
			indice ++;	 
		}
	}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers (Comparaison.c l.25)\n" ); //sinon afficher erreur
	fclose(ptr_NomDesFichiers); //fermer le pointeur de fichier


	//affichage des choix de fichier
	for (int i = 0; i < indice-1;i++){

		// afficher le nom des fichiers et un numero que l'utiliseur dois rentrer pour choisir le fichier
		printf("[%d] %s\n",i,NomDesFichiers[i]);
	}

	//sécuriser la saisie pour faire en sorte que l'utilisateur choisit un numero contenu entre 0 et indice
	do{
		printf("\nVeuillez choisir un des fichiers en entrant un des numéros de gauche : \n");
		//scan les choix entrés au clavier
		choix = test_entier1();

	}while(choix>indice || choix<=0);	//tant que c'est pas entre 0 et l'indice

system("clear"); //enlève ce qu'il y a sur le terminal

printf("Les fichiers qui ont une ressemblance supérieure au seuil parametré:\n %s\n",NomDesFichiers[choix] );


//Liste de descripteurs
type_des listeDescripteur[indice];

for (int i = 0; i < indice-1; i++)
{
	listeDescripteur[i] = init_des();
}
/*Car prend le descripteur*/

//pointeur vers le fichier aves les descripteurs
FILE *ptr_Descripteur;

//Nouvel indice avec un descripteur de moins(celui à comparer)
int indice1 =indice-2;

//Descripteur auxiliaire pour placer les descripteurs lors de la comparaison
type_des Auxiliaire = init_des();

ptr_Descripteur =fopen("../APPLICATION/FILES/Descripteur","r"); //ouverture du fichier avec les descripteurs
if(ptr_Descripteur!=NULL){	//si le fichier s'est bien ouvert

	//tant qu'il y a encore des fichiers Descripteur
	while(fscanf(ptr_Descripteur,"%d",&Auxiliaire.ref)==1){	//lecture de l'identification du descripteur

		//mis dans la liste de descripteurs à la reference   
		listeDescripteur[indice1].ref =Auxiliaire.ref;

		//lit chaque mot et son occurence dans le fichier et le place dans un type_des auxiliaire
	for (int i = 0; i < recuperer_Valuer_Descripteur(); i++){	
		fscanf(ptr_Descripteur,"%1023s%d",Auxiliaire.tab[i].mot,&Auxiliaire.tab[i].occurence);
	}

		//mis de chque mot et leur occuence dans la liste de descrpteur
	for (int i = 0; i < recuperer_Valuer_Descripteur(); i++){
		strcpy(listeDescripteur[indice1].tab[i].mot,Auxiliaire.tab[i].mot);
		listeDescripteur[indice1].tab[i].occurence =Auxiliaire.tab[i].occurence;
	}

		//on diminue l'indice pour arriver a 0
	indice1 --;
}
}else fprintf(stderr, "ERREUR pointeur fichier NomDesFichiers/ Comparaison.c l.93\n" ); //message d'erreur

//fermeture du pointeur de fichier 
fclose(ptr_Descripteur);


float pourcentage=0;

//Nouveau descrpteur qui prend le descrpteur a comparer en parmettre 
type_des comp = init_des(); 
comp = listeDescripteur[choix+1];

//creation d'un tableau de type resultat qui prend le numero de descripteur et le similutude 
type_resultattext *listeresultat = malloc(indice * sizeof(type_resultattext)); 

//indice du tableau listeresultat  
int index = 0;

//Calcule de la similitude des fichiers
for (int i = 0; i < indice-2; i++){
	//on initialise pourcentage a 0 au debut de chaque nouveau descipteur
	pourcentage =0;
	for (int j = 0; j < recuperer_Valuer_Descripteur(); j++){
		for (int k = 0; k < recuperer_Valuer_Descripteur(); k++){
			
			//si le mot du descripteur a comparer est pareil que celui qui ce trouve au numero i 
			//du tableau listeDiscripteur 
			if(strcmp(listeDescripteur[i].tab[k].mot,comp.tab[j].mot)==0){

				//on ajoute (100 / le nombre de mot dans un descrpteur) a pourcentage
				pourcentage = pourcentage + (100/recuperer_Valuer_Descripteur());
			}
		}
	}

	//si le descrpteur est different de celui choisi
	if(i != choix+1){ 
		listeresultat[index].sim = pourcentage;	//on le met dans listeresultat
		listeresultat[index].id = des[i];		//on le met dans listeresultat
		index ++;	//on rajoute 1 a la taille du tableau
	}

}

 //tri le tableau de resultat par ordre decroissant des similitude
triTableauResultat1(listeresultat,index);

//nombre de fichier afficher
int nbFichierAfficher = 0;

char **nomfich=malloc(100 * sizeof(char*));
for (int i = 0; i < 100; i++)
{
	nomfich[i] = malloc(1024 * sizeof(char));
}

int pourcentageparam = lireparametrecompar();


printf("Voici la liste des fichiers dans l'ordre:\n");
	for (int i = index-1; i > 1; i--){ 
		/*si la similitude est supperieur au parametre alors on l'afficher*/
		if(listeresultat[i].sim > pourcentageparam){ 

			/*on cherche le nom du fichier a partir du listeresultat.id*/
			for (int j = 0; j < indice-1; j++){
				if(des[j] == listeresultat[i].id){
			
				printf("[%d] %s %f\n",index-i,NomDesFichiers[j],listeresultat[i].sim);

				//copie l'adresse dans un tableau pour l'affichage après
				strcpy(nomfich[nbFichierAfficher],NomDesFichiers[j]);

				//increment le comteur
				nbFichierAfficher++;
				}
			}
		}	
	}

	
	int boolean;
	if(nbFichierAfficher == 0){
		printf("Malheursement il n'y a aucune fichier qui correspondant a vos parametre de recherche\n");
		sleep(3);
	}else{
	//Menu d'affichage des possibilités
	do{
		printf("Quel fichier voulez-vous visualiser ? [0] pour quitter \n");

		do{
			//lit le choix de l'utilisateur
		boolean = test_entier1();

		}while(boolean !=0 && boolean > nbFichierAfficher);
		if(boolean != 0){

			//printf("test\n");
			//affichage du texte choisi
			char *commande = malloc(1000 * sizeof(char));
			strcpy(commande , "cat ");
			printf("%s\n", commande);
			strcat(commande , lirechemin());
			printf("%s\n", commande);
			strcat(commande , nomfich[boolean-1]);
			
			system(commande);
		}
	}while(boolean != 0);
}

}