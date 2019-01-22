#include "menuUser.h"


void menu_user(){
	system("clear");
	printf("Vous avez choisi le mode Utilisateur \n");
	int mode = 0;
	int action = 0;
	int type_fichier = 0;
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
          printf("Que voulez-vous faire ? (1) Recherche par mot-clé, (2) Comparaison \n");
          action = test_int();

        }while(action != 1 && action != 2);
        if(action == 1){
          Recherche_par_mot_cle();
        }else if(action == 2){
          ChoixDuFichier();
        }
        break;

      case 2 : printf("Vous avez choisi les images. \n");
       
        Indexation();
        int choix = AffichageFichier();
        compair(choix);
        break;

      default :
        break;
      }
}
