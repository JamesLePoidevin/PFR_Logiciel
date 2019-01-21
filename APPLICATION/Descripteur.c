#include "Descripteur.h"

/**
 * recupere dans le fichier de parametre le nombre de mot par descripteur
 * @return le nombre de mot
 */
int recuperer_Valuer_Descripteur(){
	int nb;

	//prend ce qui est a la ligne 2 de Param/param_indexation et le met dans un fichier temporaire
	system("sed '2,2!d' Param/param_indexation > file.tmp");

  
  	FILE *ptr_fichierTEMP;

  	//ouvre le fichier file.tmp
  	ptr_fichierTEMP =fopen("file.tmp","r");

  	//si le fichier c'est bien ouvert
  	if(ptr_fichierTEMP !=NULL){
  		//lit le nombre de mot a 
    	fscanf(ptr_fichierTEMP,"%d",&nb);
  	}else fprintf(stderr, "ERREUR pointeur file.tmp\n");

  	//ferme le poiteur de fichier temp
  	fclose(ptr_fichierTEMP);

  	//renvoie le nombre de mot
  	return nb;

}

/**
 * initilalise un descripteur de texte
 * @return renvoie le descripteur initiliser
 */
type_des init_des(){

	//creer un descripteur de texte
	type_des A;

	//tableau de type_mot avec le nombre de mot lu dans le fichier de configuration
	A.tab = malloc(recuperer_Valuer_Descripteur() * sizeof(type_mot));

	//initialisation de chaque mot
	for (int i = 0; i < recuperer_Valuer_Descripteur(); i++){
		A.tab[i] = init_mot();
	}

	//renvoie du descripteur creer
	return A; 
}


/**
 * Focntion qui creer un descripteur a partir un tableau de type_mot
 * et d'une reference
 * @param  ref          id/reference du descripteur a creer
 * @param  tableauDeMot tableau de type_mot a mettre dans le descripteur
 * @return              renvoie le descripteur une fois creer
 */
type_des CreerDescriteur(int ref,type_mot tableauDeMot[]){

	//creation du nouvelle descripteur
	type_des A = init_des();

	//remplisage du descripteur
	A.ref = ref;
	for (int i = 0; i < recuperer_Valuer_Descripteur(); i++){
		A.tab[i] = tableauDeMot[i];
	}

	//renvoie le descripteur creer
	return A;
}

void Trier_tab_mot(type_mot tab[],type_mot tab2[], int length){

   int i, j;
   int indice = 0;

   //on parcourt tous la longeur du tableau
   for (i = 0; i < length; i++){

   		//creation d'un element auxiliaire
       type_mot elem =init_mot();
       
       //mis de chaque case du tableau dans l'element auxilaire a chaque
       //tours de boucle
       strcpy(elem.mot,tab[i].mot);
       elem.occurence = tab[i].occurence;
       
       for (j = i; j > 0 && tab[j-1].occurence > elem.occurence; j--){
           strcpy(tab[j].mot,tab[j-1].mot);
           tab[j].occurence = tab[j-1].occurence;
       }

         strcpy(tab[j].mot,elem.mot);
         tab[j].occurence = elem.occurence; 
   }
   
   //inverse le tableau pour affichier dans l'odre decroissante et le met dans le tableau2
   for (i = length-1; i>= 0; i--) {
  	strcpy(tab2[indice].mot,tab[i].mot);
  	tab2[indice].occurence = tab[i].occurence;
  	indice++;
	}
}

/**
 * on fait appelle a cette focntion si on veut que l'utilisateur rentre qu'un
 * un entier / n'affiche pas d'erreur si l'utilisateur rentre un char 
 * @return l'entier choisi
 */
int test_int(){      
    char nombre[50] = "";
    scanf("%s", nombre);
    if(strchr(nombre, '.') != 0){
         return 0;
     }
    return atoi(nombre);
}