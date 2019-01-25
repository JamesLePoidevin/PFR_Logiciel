////////////////////////////////////////////////////////////////////////////
//Auteur : Amaia Camino 	                                              //
//                                                                        //
//Indexation IMAGE (NB)                                                   //
//Description: Fichier fait en cours  pour utliser dans la pile, un    	  //   
// Element dans notre cas est descripteur de d'image NB 				  //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "elementNB.h"

void affiche_ELEMENTNB(ELEMENTNB f)
{
	printf("%d\n",f.ref);
	for (int i = 0; i < 10; ++i)
	{
		printf("%f\n %f\n",f.tab[0],f.tab[1] );
	}
}

ELEMENTNB affect_ELEMENTNB(ELEMENTNB f,type_descNB a)
{
	f = a;
	return f;
}

int compare_ELEMENTNB(ELEMENTNB f1,ELEMENTNB f2)
{
	if (f1.ref==f2.ref){
		return 1;
	} else return 0;
}
