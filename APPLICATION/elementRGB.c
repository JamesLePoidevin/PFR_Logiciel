#include <stdio.h>
#include "elementRGB.h"

void affiche_ELEMENTRGB(ELEMENTRGB f)
{
	printf("%d\n",f.ref);
	for (int i = 0; i < 10; ++i)
	{
		printf("%f\n %f\n",f.tab[0],f.tab[1] );
	}
}

ELEMENTRGB affect_ELEMENTRGB(ELEMENTRGB f,type_descRGB a)
{
	f = a;
	return f;
}

int compare_ELEMENTRGB(ELEMENTRGB f1,ELEMENTRGB f2)
{
	if (f1.ref==f2.ref){
		return 1;
	} else return 0;
}
