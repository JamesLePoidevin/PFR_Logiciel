#include "Descripteur.h"



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
	int max=0;											//max d'apparitions
	int indice = 0;										//indice de tab2
	for (int j = 0; j < length; j++)					//recherche du max
	{
		max =0;
		for (int i = 0; i < length; i++)
		{
			if(tab[i].occurence>max){
				max = tab[i].occurence;
			}
		}
		for (int i = 0; i < length; i++)
		{
			if (tab[i].occurence == max && max != 0)
			{
				strcpy(tab2[indice].mot,tab[i].mot);
				tab2[indice].occurence=tab[i].occurence;
				indice =indice + 1;
				tab[i].occurence =0;
			}		
		}
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