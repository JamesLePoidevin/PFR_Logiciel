#include <stdio.h>
#include "element.h"

void affiche_ELEMENT(ELEMENT f)
{
	printf("%d\n",f.ref);
	for (int i = 0; i < recuperer_Valuer_Descripteur(); ++i)
	{
		printf("%s %d\n",f.tab[i].mot,f.tab[i].occurence );
	}
}

ELEMENT affect_ELEMENT(ELEMENT f,type_des a)
{
	f = a;
	return f;
}

/*ELEMENT saisir_ELEMENT(ELEMENT f)
{
	float a;
	printf("Veuiller saisir un element\n");
	scanf("%f",&a);
	f=affect_ELEMENT(f,a);
	return f;
}
*/
int compare_ELEMENT(ELEMENT f1,ELEMENT f2)
{
	if (f1.ref==f2.ref){
		return 1;
	} else return 0;
}
