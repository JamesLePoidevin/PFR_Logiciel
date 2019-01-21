#include "Descripteur.h"

/**
 * recupere dans le fichier de parametre le nombre de mot par descripteur
 * @return le nombre de mot
 */
int recuperer_Valuer_Descripteur(){
	FILE* ptr;
	int a;
	ptr =fopen("../APPLICATION/FILES/parametre","r");
	if(ptr!=NULL){
		fscanf(ptr,"%d",&a);
	}else fprintf(stderr, "Erreur pointeur parametre\n");
	fclose(ptr);
	return a;
}

type_des init_des(){
	type_des A;
	A.tab = malloc(recuperer_Valuer_Descripteur() * sizeof(type_mot));
	for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
	{
		A.tab[i] = init_mot();
	}
	return A; 
}

type_des CreerDescriteur(int ref,type_mot tableauDeMot[]){
	type_des A = init_des();
	A.ref = ref;
	for (int i = 0; i < recuperer_Valuer_Descripteur(); i++)
	{
		A.tab[i] = tableauDeMot[i];
	}
	return A;
}

void Trier_tab_mot(type_mot tab[],type_mot tab2[], int length){

   int i, j;
   int indice = 0;
   for (i = 0; i < length; i++) {
       type_mot elem =init_mot();
       strcpy(elem.mot,tab[i].mot);
       elem.occurence = tab[i].occurence;
       for (j = i; j > 0 && tab[j-1].occurence > elem.occurence; j--){
           strcpy(tab[j].mot,tab[j-1].mot);
           tab[j].occurence = tab[j-1].occurence;
       }

         strcpy(tab[j].mot,elem.mot);
         tab[j].occurence = elem.occurence; 
   }
   
   for (i = length-1; i>= 0; i--) {
  	strcpy(tab2[indice].mot,tab[i].mot);
  	tab2[indice].occurence = tab[i].occurence;
  	indice++;
	}
}



int test_int(){          // cas où on souhaite seulement un entier
    char nombre[50] = "";
    scanf("%s", nombre);
    if(strchr(nombre, '.') != 0){
         return 0;
     }
    return atoi(nombre);
}