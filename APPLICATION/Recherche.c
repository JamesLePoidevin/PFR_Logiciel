#include "Recherche.h"

void Recherche_par_mot_cle()
{
  int choix; //Connaître le choix de l'utilisateur concernant une nouvelle recherche.
  int boucle = 0; //variable de boucle artificielle

  init_chemins(); //On initialise les chemins.
  Recherche();//On débute le processus de recherche en demandant la saisie du mot (Dans traiter_mot_cle.c)
  Recup_textes();//On fini la recherche en récupèrant les textes pertinents (Dans recup_textes.c)

  system("rm *.temp");//On supprime tous les fichiers temporaires une fois que la recherche est terminée.

  do //On demande s'il veut effectuer une nouvelle recherche tant qu'il ne fait pas une saisie correcte.
  {
    printf("\nVoulez vous effectuer une nouvelle recherche ? (1)OUI ,(2)NON : ");

    if(scanf("%d",&choix) != 1) //Si la saisie n'est pas un entier, on affiche un message d'erreur.
    {
      printf("\nJe n'ai pas compris, veuillez taper 1 ou 2\n");
      vider_buffer();//on vide le buffer pour nettoyer.
    }
    else
    {
      switch(choix)
      {
        case 1 : boucle = 10; //S'il choisit OUI on change la valeur de la boucle pour en sortir à la fin.
                 vider_buffer();//On vide le buffer.
                 Recherche_par_mot_cle();//ON lance une nouvelle recherche par mot clé.
                 break;

        case 2 : boucle = 10; //S'il choisit NON on change la valeur de la boucle pour en sortir.
                 vider_buffer();//On vide le buffer
                 break;

        default : printf("\nJe n'ai pas compris, veuillez taper 1 ou 2\n"); //Sinon on affiche un message d'erreur.
                  vider_buffer();//On vide le buffer.
                  break;
      }
    }
  }while(boucle == 0); //On redemande tant que la variable de boucle = 0.
}
