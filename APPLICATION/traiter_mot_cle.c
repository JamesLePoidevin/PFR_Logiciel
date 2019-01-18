#include "traiter_mot_cle.h"

//passe le fichier MotsCles en minuscules.
void Mise_En_Minuscules()
{
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

//Pour avoir les mots sans leurs occurences.
void Recup_mots()
{
  strcpy(cut, "cut -f1 -d ' ' ");
  strcat(cut,CHEMIN);
  strcat(cut, "resultat.temp > ");
  strcat(cut,CHEMIN);
  strcat(cut,"mots_totaux.temp");

  system(cut);
}


void affichage_mots(char* chemin_fic, char* nom_fic)
{
  strcpy(affichage,"cat ");
  strcat(affichage, chemin_fic);
  strcat(affichage, nom_fic);
  system(affichage);
}

//On compare les mots trouves pour les garder une seule fois chacun.
void Compare_mots()
{
    int premier = 1;

    if(compter_mots(CHEMIN,"resultat.temp") != 0)
    {
      Recup_mots();

      ptr_fic = fopen("mots_totaux.temp","r");
      if(ptr_fic != NULL)
      {
        do
        {
          fscanf(ptr_fic,"%s",mot_a_comparer);

             if(premier == 1)
             {
                strcpy(mot_de_base, mot_a_comparer);
                strcpy(echo,"echo ");
                strcat(echo,mot_de_base);
                strcat(echo," > ");
                strcat(echo,CHEMIN);
                strcat(echo,"mots_trouves.temp");
                system(echo);
                premier = 66;
            }
            else
            {
                if(strcmp(mot_de_base,mot_a_comparer) != 0)
                {
                    strcpy(mot_de_base, mot_a_comparer);

                    strcpy(echo,"echo ");
                    strcat(echo,mot_de_base);
                    strcat(echo," >> ");
                    strcat(echo,CHEMIN);
                    strcat(echo,"mots_trouves.temp");
                    system(echo);
                }
            }
        }while(!feof(ptr_fic));
      }

      fclose(ptr_fic);
    }

    else
    {
      strcpy(echo,"echo > ");
      strcat(echo,CHEMIN);
      strcat(echo,"mots_trouves.temp");
      system(echo);
    }

    if(depart == 1)
    {
      strcpy(cp, "cp ");
      strcat(cp,CHEMIN);
      strcat(cp, "mots_trouves.temp ");
      strcat(cp,CHEMIN);
      strcat(cp,"mots_trouves_depart.temp");
      system(cp);

      depart = 20;
    }

    nb_mots = compter_mots(CHEMIN,"mots_trouves.temp");
}

//on permet de rechercher à partir d'un extrait de mot.
void Recherche_extrait()
{

  printf("Saisir un mot (q pour Quitter) : ");
  scanf("%s",mot_cle);

  strcpy(recherche, "grep -i ");
  strcat(recherche,mot_cle);
  strcat(recherche," ");
  strcat(recherche, CHEMIN2);
  strcat(recherche,"MotsClesMin > ");
  strcat(recherche, CHEMIN);
  strcat(recherche, "resultat.temp");

  system(recherche);

  Compare_mots();

  vider_buffer();
}

//Il faut saisir le mot exact pour la recherche.
void Recherche_mot_exact()
{
  int nb_lignes,ligne,i;
  char num_ligne[10];

  printf("Saisir un mot complet (q pour Quitter): ");
  scanf("%s",mot_cle);  

  /**/
  strcpy(recherche, "grep -x -n -i ");
  strcat(recherche,mot_cle);
  strcat(recherche," ");
  strcat(recherche, CHEMIN);
  strcat(recherche,"MotsClesMinSansDescripteurs.temp | cut -f1 -d ':' > ");
  strcat(recherche, CHEMIN);
  strcat(recherche, "lignes.temp");

  system(recherche);

  nb_lignes = compter_mots(CHEMIN,"lignes.temp");

  ptr_fic = fopen("lignes.temp","r");

  if(ptr_fic != NULL)
  {
    for(i=0;i<nb_lignes;i++)
    {
      fscanf(ptr_fic,"%d",&ligne);

      sprintf(num_ligne,"%d",ligne);

      if(i==0)
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
      else
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

  nb_mots = compter_mots(CHEMIN,"lignes.temp");

  if(nb_mots > 0)
  {
    Compare_mots();
  }

  vider_buffer();

}

//On confirme si c'est le bon mot ou non.
void confirmation()
{
  printf("Voulez vous cherchez ce mot : (1) OUI, (2) NON, (3) QUITTER\n");

  if(scanf("%d",&validation) != 1)
  {
    printf("Je n'ai pas compris, veuillez taper 1 ou 2\n");
    vider_buffer();
    confirmation();
  }
  else
  {
    switch(validation)
    {
      case 1 : boucle = 200;
                vider_buffer();
                break;

      case 2 : depart = 1;
                vider_buffer();
                break;

      case 3 : STOP = 12;
               boucle = 200;
               vider_buffer();
               break;

      default : printf("Je n'ai pas compris, veuillez taper 1 ou 2\n");
                vider_buffer();
                confirmation();
                break;
    }
  }
}

//Lance la recherche en demandant les infos à l'utilisateur.
void Recherche()
{
    STOP = 0;
    boucle = 0;
    depart = 1;
    int boucle_validation = 0;

    Mise_En_Minuscules();

    for(;STOP==0;)
    {
      do
      {
        Recherche_extrait();

        if((mot_cle[0] == 'q' || mot_cle[0] == 'Q') && mot_cle[1] == '\0' )
        {
          STOP = 12;
          break;
        }

        if(nb_mots < 1)
        {
          printf("Aucune correspondance.\n");
        }

        else if(nb_mots == 1)
        {

          printf("Une correspondance trouvée : \n");

          affichage_mots(CHEMIN,"mots_trouves.temp");

          confirmation();
        }
        else
        {
          boucle = 200;
        }
      } while(boucle < 1);

      boucle = 0;

      if(STOP == 0)
      {
        do
        {
          if(nb_mots > 1)
          {
            printf("Voici les choix possibles : \n");

            affichage_mots(CHEMIN,"mots_trouves_depart.temp");

            Recherche_mot_exact();

          }
          else if(nb_mots < 1)
          {
            printf("Mot inconnu : \n");

            printf("Voici votre precedente recherche : \n");
            
            affichage_mots(CHEMIN,"mots_trouves_depart.temp");
            /**/
            Recherche_mot_exact();

          }
          else
          {
            boucle = 8;
          }
      }while(boucle < 1);

      ptr_fic = fopen("mots_trouves.temp","r");

      if(ptr_fic != NULL)
      {
        fscanf(ptr_fic,"%s",mot_choisi);
      }

      fclose(ptr_fic);
      break;
    }
  }
}
