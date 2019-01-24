#include "traiter_mot_cle.h"

//passe le fichier MotsCles en minuscules et crée un fichier temporaire de l'ensemble de tous les mots sans leurs descripteurs.
//permet d'éviter par exemple que "Bonjour" et "bonjour" soient considérés comme deux mots différents.
void Mise_En_Minuscules()
{
  char minuscules[1000]; //Contiendra la commande permettant de passer les mots clés en minuscules
  char cut[1000]; //Contiendra la commande permettant de séparer les mots -clés de leurs descripteurs.

  strcpy(minuscules,"tr [:upper:] [:lower:] < ");
  strcat(minuscules,CHEMIN2);
  strcat(minuscules,"MotsCles > ");
  strcat(minuscules,CHEMIN2);
  strcat(minuscules,"MotsClesMin");

  system(minuscules);

  strcpy(cut,"cut -f1 -d ' ' ");
  strcat(cut,CHEMIN2);
  strcat(cut,"MotsClesMin > ");
  strcat(cut, "MotsClesMinSansDescripteurs.temp");
  system(cut);
}

//On récupère les mots sans leurs occurrences dans un fichier temporaire.
void Recup_mots()
{
  char cut[1000]; //Contiendra la commande pour séparer les mots de leurs occurrences

  strcpy(cut, "cut -f1 -d ' ' ");
  strcat(cut,CHEMIN);
  strcat(cut, "resultat.temp > ");
  strcat(cut,CHEMIN);
  strcat(cut,"mots_totaux.temp");

  system(cut);
}

//Permet à l'utilisateur de voir les mots correspondants à sa recherche.
void affichage_mots(char* chemin_fic, char* nom_fic)
{
  char affichage[1000]; //Contiendra la commande pour afficher les mots à l'utilisateur.

  strcpy(affichage,"cat ");
  strcat(affichage, chemin_fic);
  strcat(affichage, nom_fic);
  system(affichage);
}

//On compare les mots trouvés pour ne les garder qu'une seule fois chacun dans un fichier temporaire..
void Compare_mots()
{
  char mot_a_comparer[100]; //Contiendra le mot a comparer pour savoir s'il est déjà présent.
  char compter_lignes[1000]; // Contiendra la commande pour savoir si un mot a déjà été récupérer.
  char echo[1000]; //Contiendra la commande pour écrire dans un fichier.
  char cp[1000]; //Contiendra la commande permettant de copier un fichier.
  int premier = 1; //Variable qui permet de savoir si on lit le tout premier des mots correspondants ou pas.
  int deja_vu; //variable pour savoir si le mot lu a déjà été récupéré auparavant.
  FILE* ptr_fic;
  FILE* ptr_fic2;

  if(compter_mots(CHEMIN,"resultat.temp") != 0) //On vérifie qu'au moins un mot correspond à la recherche.
  {
    Recup_mots();

    ptr_fic = fopen("mots_totaux.temp","r");//on ouvre le fichier temporaire contenant la totalité des mots correspondants à la recherche.
    if(ptr_fic != NULL)//On vérifie qu'on a bien réussi à ouvrir mots_totaux.temp
    {
      do
      {
        fscanf(ptr_fic,"%s",mot_a_comparer); //On lit le mot que l'on veut comparer.

           if(premier == 1) //Si c'est le premier mot de la liste on l'enregistre dans le fichier temporaire mots_trouves.temp.
           {
              strcpy(echo,"echo ");
              strcat(echo,mot_a_comparer);
              strcat(echo," > ");
              strcat(echo,CHEMIN);
              strcat(echo,"mots_trouves.temp");
              system(echo);
              premier = 66; //après on change la valeur pour signifier que l'on a dépassé le premier mot.
          }
          else //sinon on compte le nombre de ligne où le mot est présent dans mots_trouves.temp.
          {
                  strcpy(compter_lignes,"grep -x -c ");
                  strcat(compter_lignes,mot_a_comparer);
                  strcat(compter_lignes," ");
                  strcat(compter_lignes, CHEMIN);
                  strcat(compter_lignes,"mots_trouves.temp > deja_present.temp");

                  system(compter_lignes);

                  ptr_fic2 = fopen("deja_present.temp","r");//on ouvre le fichier temporaire contenant le nombre de ligne de présence du mot lu dans mots_trouves.temp.
                  if(ptr_fic2 != NULL)//On vérifie qu'on a bien réussi à ouvrir deja_present.temp
                  {
                      fscanf(ptr_fic2,"%d",&deja_vu); //On enregistre le nombre de ligne de présence dans la variable deja_vu.
                  }
                  fclose(ptr_fic2);

                  if(deja_vu == 0) //Si aucune ligne ne correspond au mot lu, on l'ajoute à la suite de mots_trouves.temp.
                  {
                      strcpy(echo,"echo ");
                      strcat(echo,mot_a_comparer);
                      strcat(echo," >> ");
                      strcat(echo,CHEMIN);
                      strcat(echo,"mots_trouves.temp");
                      system(echo);
                  }
          }
      }while(!feof(ptr_fic)); //On continue tant qu'on est pas arrivé à la fin de mots_totaux.temp
    }

    fclose(ptr_fic);
  }

  else //Si aucun mot ne correspondait à la recherche, le fichier temporaire mots_trouves.temp est créé vide.
  {
    strcpy(echo,"echo ' '> ");
    strcat(echo,CHEMIN);
    strcat(echo,"mots_trouves.temp");
    system(echo);
  }

  //Si c'était la première saisie de l'utilisateur on copie mots_trouves.temp dans un fichier temporaire mots_trouves_depart.
  //Ce fichier permettra de redonner les propositions à l'utilisateur en cas de saisie erronée ensuite.
  if(depart == 1)
  {
    strcpy(cp, "cp ");
    strcat(cp,CHEMIN);
    strcat(cp, "mots_trouves.temp ");
    strcat(cp,CHEMIN);
    strcat(cp,"mots_trouves_depart.temp");
    system(cp);

    depart = 20; //Ensuite on dit que ce n'est plus le départ pour ne plus modifier mots_trouves_depart.temp
  }

  nb_mots = compter_mots(CHEMIN,"mots_trouves.temp"); //on enregistre dans nb_mots(déclaré dans traiter_mot_cle.h) le nombre de mots contenus dans mots_trouves.temp.
}

//on permet de rechercher à partir d'un extrait de mot.
void Recherche_extrait()
{
  char recherche[1000];//Contiendra la commande pour rechercher le mot saisi.

  printf("\nSaisir un mot (0 pour Quitter) : ");
  scanf("%s",mot_cle); //On récupère la saisie dans mot_cle (déclaré dans traiter_mot_cle.h)
  if(mot_cle[0] != '0'){
  //On récupère dans le fichier temporaire resultat.temp tous les mots contenant la saisie de l'utilisateur.
  strcpy(recherche, "grep -i ");
  strcat(recherche,mot_cle);
  strcat(recherche," ");
  strcat(recherche, CHEMIN2);
  strcat(recherche,"MotsClesMin > ");
  strcat(recherche, CHEMIN);
  strcat(recherche, "resultat.temp");

  system(recherche);

  Compare_mots(); //On lance la comparaison du resultat pour proposer à l'utilisateur une seule fois chaque correspondance.
}
  vider_buffer();//On vide le buffer de saisie pour être sûr qu'il ne reste pas de saisie parasite.
}

//Il faut saisir le mot exact pour la recherche.
void Recherche_mot_exact()
{
  int nb_lignes,ligne,i;
  FILE* ptr_fic;
  char num_ligne[10];
  char recherche[1000];//Contiendra la commande pour rechercher le mot exact saisi.
  char recup_lignes[1000];//Contiendra la commande permettant de récupérer dans le fichier MotsClesMin les lignes correspondant à la recherche.

  printf("\nSaisir un mot complet (0 pour Quitter, 1 pour une nouvelle recherche): ");
  scanf("%s",mot_cle);
  if (mot_cle[0] != '0' && mot_cle[0]!='1'){

  //On regarde dans la liste des mots cles sans leurs descripteurs les lignes correspondants exactement à la recherche en récupérant aussi leur numéro de ligne.
  //Ensuite on garde uniquement les numéros de lignes.
  strcpy(recherche, "grep -x -n -i ");
  strcat(recherche,mot_cle);
  strcat(recherche," ");
  strcat(recherche, CHEMIN);
  strcat(recherche,"MotsClesMinSansDescripteurs.temp | cut -f1 -d ':' > ");
  strcat(recherche, CHEMIN);
  strcat(recherche, "lignes.temp");
  system(recherche);

  nb_lignes = compter_mots(CHEMIN,"lignes.temp"); //On compte le nombre de lignes total où se trouve le mot exact saisi.


  ptr_fic = fopen("lignes.temp","r");//On ouvre la liste des lignes où se trouve le mot dans le fichier MotsClesMin

  if(ptr_fic != NULL) //On vérfie qu'on a réussi à ouvrir la liste des lignes.
  {
    for(i=0;i<nb_lignes;i++)
    {
      fscanf(ptr_fic,"%d",&ligne); //On récupère le numero de la ligne dans la variable ligne.

      sprintf(num_ligne,"%d",ligne);//On transforme ce numéro en un tableau de char.

      if(i==0) //Si c'est la première ligne on la récupère et on l'envoie dans le fichier temporaire resultat.temp
      {
        strcpy(recup_lignes,"head ");
        strcat(recup_lignes,"-");
        strcat(recup_lignes,num_ligne);
        strcat(recup_lignes," ");
        strcat(recup_lignes,CHEMIN2);
        strcat(recup_lignes,"MotsClesMin | tail -1 > ");
        strcat(recup_lignes,CHEMIN);
        strcat(recup_lignes,"resultat.temp");
      }
      else //Sinon on l'ajoute à la suite du fichier resultat.temp
      {
        strcpy(recup_lignes,"head ");
        strcat(recup_lignes,"-");
        strcat(recup_lignes,num_ligne);
        strcat(recup_lignes," ");
        strcat(recup_lignes,CHEMIN2);
        strcat(recup_lignes,"MotsClesMin | tail -1 >> ");
        strcat(recup_lignes,CHEMIN);
        strcat(recup_lignes,"resultat.temp");
      }
      system(recup_lignes);
    }
  }

  fclose(ptr_fic);

  if(nb_lignes > 0) //Si le mot se trouve au moins une fois on utilise Compare_mots() pour ne l'afficher qu'une seule fois à l'utilisateur.
  {
    Compare_mots();
  }
  else //Sinon on met nb_mots à 0 (nombre de correspondance au mot saisi)
  {
    nb_mots = 0;
  }

  vider_buffer();//On vide le buffer pour éviter les saisies parasites.
}
}

//On confirme si c'est le bon mot ou non (Quand il n'y a qu'une seule correspondance).
void confirmation()
{
  int validation; //variable contenant la confirmation de l'utilisateur;.

  printf("\nVoulez-vous chercher ce mot ? (1)OUI (2)NON (3)Quitter la recherche\n");

  if(scanf("%d",&validation) != 1) //Si l'utilisateur saisit autre chose qu'un entier on affiche un message d'erreur.
  {
    printf("\nJe n'ai pas compris, veuillez taper 1 ou 2\n");
    vider_buffer();//On vide le buffer pour nettoyer la mauvaise saisie.
    confirmation();//On redemande la confirmation..
  }
  else //Sinon on traite la saisie.
  {
    switch(validation)
    {
      case 1 : boucle = 200; //S'il dit oui on sort de la boucle (où se trouve confirmation()) située dans la fonction Recherche() plus bas.
               vider_buffer(); //On vide le buffer.
               break;

      case 2 : depart = 1; //S'il dit non on réinitialise départ à 1 car on voudra faire une autre recherche.
               vider_buffer(); // On vide le buffer
               break;

      case 3 : STOP = 12; // On active le STOP pour quitter la recherche par mot_clé si l'utilisateur saisi 3.
               boucle = 200; //On sort de la boucle (où se trouve confirmation()) située dans la fonction Recherche() plus bas.
               vider_buffer(); //On vide le buffer
               return;
               break;

      default : printf("\nJe n'ai pas compris, veuillez taper 1 ou 2\n"); //Sinon on affiche un message d'erreur.
                vider_buffer();//On vide le buffer
                confirmation();//On redemande la confirmation.
                break;
    }
  }
}

//Lance la recherche en demandant les infos à l'utilisateur.
void Recherche()
{

  STOP = 0; //On utilise STOP à 0 (déclaré dans global.h).
  boucle = 0; //On utilise la variable de boucle à 0;
  depart = 1; // On initialise le départ à 1 (C'est la première saisie)
  FILE* ptr_fic;

  Mise_En_Minuscules();//On met les mots clés en minuscules.

  while(STOP==0) //Tant que STOP = 0 on continue la recherche.
  {
    do //On lance au moins une demande de saisie
    {
      Recherche_extrait(); //On recherche un extrait de mot.

      //Si l'utilisateur a saisi q ou Q pour quitter la recherche
      if(mot_cle[0] =='0' && mot_cle[1] == '\0' )
      {
        STOP = 12; //On change la valeur de STOP.
        break; //On quitte la boucle de saisie du mot
      }

      if(nb_mots < 1) //Si il n'y a pas de mots correpondant à la saisie
      {
        printf("\nAucune correspondance.\n");
        depart = 1;
      }

      else if(nb_mots == 1) //Si il y a une unique correspondance à la saisie.
      {

        printf("\nUne correspondance trouvée : \n");

        affichage_mots(CHEMIN,"mots_trouves.temp"); //On affiche le mot correspondant.

        confirmation();//On demande de confirmer si c'est bien ce mot que l'on doit chercher.
      }
      else //Sinon on passe à la suite
      {
        boucle = 200; //On sort de la boucle en modifiant cette valeur.
      }
    } while(boucle < 1); //On recommence la demande de saisie tant que boucle < 1;

    boucle = 0; // On remet la variable de boucle à 0 pour plus tard.

    if(STOP == 0) //Si STOP est toujours égal à 0 on passe à la suite de la recherche.
    {
      do
      {
        if(nb_mots > 1) // S'il y avait plusieurs correspondances on les propose à l'utilisateur
        {
          printf("\nVoici les choix possibles : \n");
          affichage_mots(CHEMIN,"mots_trouves_depart.temp");
          Recherche_mot_exact(); //On demande de saisir un mot exact pour le chercher.

          if(mot_cle[0] == '0' && mot_cle[1] == '\0' ) //Si l'utilisateur a saisi q ou Q pour quitter la recherche
          {
            STOP=12; //On change la valeur de STOP.
            break; // On quitte la boucle de saisie du mot.
          }

          //Si l'utilisateur n'est pas satisfait des propositions il peut lancer une nouvelle recherche en saisissant r ou R.
          if(mot_cle[0] == '1' && mot_cle[1] == '\0' )
          {
            Recherche();
            break; //On quitte la boucle de saisie du mot.
          }
        }
        else if(nb_mots < 1) //Si aucun mot ne correspond exactement à la nouvelle saisie.
        {
          printf("\nMot inconnu : \n");
          printf("\nVoici votre précédente recherche : \n");
          affichage_mots(CHEMIN,"mots_trouves_depart.temp");
          Recherche_mot_exact();

          if(mot_cle[0] == '0' && mot_cle[1] == '\0' ) //Si l'utilisateur a saisi q ou Q pour quitter la recherche
          {
            STOP=12; //On change la valeur de STOP.
            break; // On quitte la boucle de saisie du mot.
          }

          //Si l'utilisateur n'est pas satisfait des propositions il peut lancer une nouvelle recherche en saisissant r ou R.
          if(mot_cle[0] == '1' && mot_cle[1] == '\0' )
          {
            Recherche();
            break; //On quitte la boucle de saisie du mot.
          }
        }
        else //Si il y a une seule correspondance on passe à la suite
        {
          boucle = 8; //On modifie la valeur pour sortir de la boucle.
        }
    }while(boucle < 1);

    ptr_fic = fopen("mots_trouves.temp","r"); //On ouvre mots_trouves.temp

    if(ptr_fic != NULL)
    {
      fscanf(ptr_fic,"%s",mot_choisi); //On lit le mot choisi par l'utilisateur et on l'enregistre dans mot_choisi (défini dans global.h)
    }

    fclose(ptr_fic);//On ferme mots_trouves.temp
    break; //On quitte la boucle tant que pour passer à la suite du programme
    }
  }
}
