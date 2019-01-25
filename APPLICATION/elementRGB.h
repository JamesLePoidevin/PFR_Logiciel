////////////////////////////////////////////////////////////////////////////
//Auteur : Amaia Camino 	                                              //
//                                                                        //
//Indexation IMAGE (RGB)                                                  //
//Description: Fichier fait en cours  pour utliser dans la pile, un    	  //
// Element dans notre cas est descripteur de d'image RGB 				  //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "descripteurRGB.h"


typedef type_descRGB ELEMENTRGB;

void affiche_ELEMENTRGB(ELEMENTRGB f);

ELEMENTRGB affect_ELEMENTRGB(ELEMENTRGB f,type_descRGB a);

int compare_ELEMENTRGB(ELEMENTRGB f1,ELEMENTRGB f2);