#include "menuUser.h"


void menu_user(){
	system("clear");
	printf("Mode Utilisateur: \n");
	int mode = 0;
	int action = 0;
	int type_fichier = 0;
    do
    {
      printf("Que voulez-vous comparer ? (1)Textes (2)Images (3)Quitter le programme\n ");
      type_fichier = test_int();
      //scanf("%d", &type_fichier);

    }while( type_fichier != 1 && type_fichier != 2 && type_fichier !=3 && type_fichier !=4);

    switch (type_fichier)
    {
      case 1 : printf("Vous avez choisi les textes.\n");
        do
        {
          printf("Que voulez-vous faire ? (1)Recherche par mot-clé (2)Comparaison (3)Retour au menu Utilisateur (4)Quitter le programme\n");
          action = test_int();

        }while(action != 1 && action != 2 && action != 3 && action != 4);
        if(action == 1){
          Recherche_par_mot_cle();
          menu_user();

        }else if(action == 2){
          ChoixDuFichier();
          menu_user();
        }else if(action == 3){
          menu_user();
        }else if(action == 4){
          return;
        }
        break;

      case 2 : printf("Vous avez choisi les images. \n");
       
        Indexation();
        int choix = AffichageFichier();
        compair(choix);
        break;

      case 3 :
        return;
        break;

      default :
        break;
      }
}
