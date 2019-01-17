#include <stdio.h>
#include "pile_statiqueNB.h"


PILENB init_PILENB(){
	PILENB p;
	p.indice=-1;
	return p; 
} 


void affiche_PILENB(PILENB p){
	int i;
	if (p.indice==-1)
	{
		printf("Erreur : la pile est vide\n");
	}
	else
	{
		for (i = 0; i <= p.indice; i++)
		{
			affiche_ELEMENTNB(p.tab[i]);
		}
		printf("\n");
	}	

}


int PILE_estVideNB(PILENB p){
	if(p.indice==-1){
		return 1;
	}
	else {return 0;}
}


int PILE_estPleineNB(PILENB p){
	if (p.indice==MAX-1)
	{
		return 1;
	}
	else{return 0;}
}


PILENB emPILENB(PILENB p, ELEMENTNB a)
{	
	if(p.indice!=MAX){
		p.tab[p.indice+1]=a;
		p.indice++;
		return p;
	}	
	return p;
}


PILENB dePILENB(PILENB p,ELEMENTNB *a)
{	
	if (p.indice == -1)
	{
	}
	else{
		*a=p.tab[p.indice];
		p.indice -= 1;
		return p;
	}
	return p;
}


/*PILE saisir_PILE()
{
	PILE p;
	int saisir,a;
	p=init_PILE();
	printf("Combien de valeur.s voulez-vous saisir entre 0 et %d?\n",MAX);
	scanf("%d",&saisir);
	while(saisir>MAX || saisir<0){
			printf("Erreur : votre valeur est superieure ou inférieure à %d\n",MAX);
			printf("Combien de valeur.s voulez-vous saisir entre 0 et %d?\n",MAX);
			scanf("%d",&saisir);
	}
	for (int i = 0; i < saisir;i++)
	{
		printf("Entrez la valeur n° %d dans le pile\n",i+1);
		ELEMENT e = saisir_ELEMENT(e);
		p.tab[i]=e;
		p.indice++;
	}
	return p;
}*/