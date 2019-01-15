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
    /*
    do
    {
      printf("Que voulez-vous comparer ? (1) textes, (2)images\n ");
      type_fichier = test_int();
      //scanf("%d", &type_fichier);

    }while( type_fichier != 1 && type_fichier != 2);

    switch (type_fichier)
    {
      case 1 : printf("Vous avez choisi les textes\n");
      do
      {
        printf("Que voulez-vous faire ? (1) Recherche mots-clé, (2) Comparaison \n");
        action = test_int();

      }while(action != 1 && action != 2);
      if(action == 1){
        Recherche_par_mot_cle();
      }else if(action == 2){
        ChoixDuFichier();
      }
      break;

      case 2 : printf("Vous avez choisi les images. \n");
      printf("Vous entrez donc en mode comparaison\n");


      break;

      default :
      break;
    }

    break;*/

    case 2 : printf("Vous avez choisi le mode administrateur\n");
      menu_admin();
    /*
    param_index_texte();
    param_index_image();
    menu_index();
    menu_chemins();
    system("cat Param/param_indexation.txt");
    param_recherche_texte();
    system("cat Param/param_recherche.txt");
    param_compar_texte();
    menu_comparaison();
    system("cat Param/param_comparaison.txt");
    */
    //menu_index();
    //system("/Bureau/LOGICIEL_V1/Mode_administrateur/");
    break;

    default :
    break;
  }
}


void main()
{

  char *CHEMIN = malloc(1000*sizeof(char));
  FILE * ptr_Chemin;
  IndexationComplet();
  ptr_Chemin = fopen("../APPLICATION/FILES/CHEMIN","r");
  if(ptr_Chemin != NULL){
    fscanf(ptr_Chemin,"%s",CHEMIN);
  }else fprintf(stderr, "Erreur pointeur chemin\n");

  //IndexationComplet("../Textes/");
  //IndexationAutomatique("../Textes/");
  menu();
  //system("rm *.temp");
}
