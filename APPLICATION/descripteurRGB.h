////////////////////////////////////////////////////////////////////////////
//Auteur : Amaia Camino                                                   //
//                                                                        //
//Indexation Image NB                                                     //
//Description: Fichier Pour la structure en rapport avec les Descripteur  //
//Image NB                                                                //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Descripteur pour le image RGB
typedef struct type_descRGB
{
	int ref;
	float tab[63];
}type_descRGB;

