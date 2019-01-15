#include <stdio.h>
#include <stdlib.h>
#include "configuration.h"




int mode = 0;
int action = 0;
int type_fichier = 0;


void menu()
{
 // system("clear");

  printf("\033[1;34m\n\n\n   Q ");
  printf("\033[33mW ");
  printf("\033[31mA ");
  printf("\033[36mN ");
  printf("\033[32mT ");
  printf("\033[35mé  ");
  printf("\033[0m");

  printf("vous souhaite la bienvenue sur son moteur de recherche. \n\n\n");

  do
  {
    printf("Veuillez choisir un mode, (1) utilisateur ou (2) administrateur : \n");
    mode = test_int();
    //scanf("%d",&mode);

  }while( mode != 1 && mode !=2);

  switch (mode)
  {
    case 1 : 
      menu_user();
      break;

    case 2 : printf("Vous avez choisi le mode administrateur\n");
      menu_admin();

    break;

    default :
    break;
  }
}


void main()
{

 // char *CHEMIN = malloc(1000*sizeof(char));
  //FILE * ptr_Chemin;
  IndexationComplet();
  /*ptr_Chemin = fopen("../APPLICATION/FILES/CHEMIN","r");
  if(ptr_Chemin != NULL){
    fscanf(ptr_Chemin,"%s",CHEMIN);
  }else fprintf(stderr, "Erreur pointeur chemin\n");
*/
  menu();
  //system("rm *.temp");
}
