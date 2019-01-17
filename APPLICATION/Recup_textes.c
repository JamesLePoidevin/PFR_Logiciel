#include "Recup_textes.h"

//char CHEMIN3[1000] = "~/Documents/PFR/Textes/"; //Chemin d'accès aux textes à ouvrir.


//récupère la liste des descripteurs correspondants au mot choisi.
void Recup_descripteurs()
{
  strcpy(cut, "cut -f2 -d ' ' ");
  strcat(cut,CHEMIN);
  strcat(cut, "resultat.temp > ");
  strcat(cut,CHEMIN);
  strcat(cut,"descripteurs_correspondants.temp");
  system(cut);
}

//on enregistre tous les descripteurs correspondant au mot dans un tableau.
void Enregistrer_descripteurs()
{
  ptr_fic = fopen("descripteurs_correspondants.temp","r");

  if(ptr_fic != NULL)
  {
    for(i=0;i < nb_descripteurs;i++)
    {
      fscanf(ptr_fic,"%d ",&liste_descripteurs[i]);
    }
  }

  fclose(ptr_fic);
}

//On isole un descripteur pour pouvoir le traiter.
void Isoler_descripteur(int num)
{
    char num_descripteur[1000];

    sprintf(num_descripteur,"%d",num);

    strcpy(isolement,"grep -x -i -n ");
    strcat(isolement,num_descripteur);
    strcat(isolement," ");
    strcat(isolement,CHEMIN2);
    strcat(isolement,"Descripteur > ");
    strcat(isolement,CHEMIN);
    strcat(isolement,"ligne_descripteur.temp");

    system(isolement);

    //on rècupère la ligne où se trouve le descripteur dans le fichier Descripteur.
    strcpy(association,"cut -f1 -d ':' ");
    strcat(association,CHEMIN);
    strcat(association,"ligne_descripteur.temp >> ");
    strcat(association,CHEMIN);
    strcat(association,"ligne_descripteur.temp");

    system(association);

    ptr_fic = fopen("ligne_descripteur.temp","r");

    if(ptr_fic != NULL)
    {
      fscanf(ptr_fic,"%*s %d",&ligne);
    }

    fclose(ptr_fic);

    char num_ligne[10];
    sprintf(num_ligne,"%d",ligne+10);

    strcpy(isolement,"head ");
    strcat(isolement,"-");
    strcat(isolement,num_ligne);
    strcat(isolement," ");
    strcat(isolement,CHEMIN2);
    strcat(isolement,"Descripteur | tail -11 > ");
    strcat(isolement,CHEMIN);
    strcat(isolement,"descripteur_isole.temp");

    system(isolement);
}

//On récupère le nombre d'occurences du mot choisi dans un descripteur.
void Occurences_par_descripteurs(char * mot)
{
  strcpy(recup_occ,"grep -w -i ");
  strcat(recup_occ,mot);
  strcat(recup_occ," ");
  strcat(recup_occ,CHEMIN);
  strcat(recup_occ,"descripteur_isole.temp | cut -f2 -d ' ' > ");
  strcat(recup_occ,CHEMIN);
  strcat(recup_occ,"occ_par_des.temp");

  system(recup_occ);

}

//On enregistre le nombre d'occurences de chaque descripteur dans un tableau en les triant en associant le même indice pour le descripteur et son ocurrence.
//On trie le nombre d'occurences ce qui nous permet de trier les descripteurs dans un troisième tableau grâce aux indices.
int Recup_occurences(int pos)
{
  occ = 0;

  ptr_fic = fopen("occ_par_des.temp","r");

  if(ptr_fic != NULL)
  {
    fscanf(ptr_fic,"%d",&occ);

    for(int i = pos; i >= 0 ; i--)
    {
      if(occ > occurences[i])
      {
      occurences[i+1] = occurences[i];
      occurences[i] = occ;
      tri_descripteurs[i+1] = tri_descripteurs[i];
      tri_descripteurs[i] = liste_descripteurs[pos];
      }
      else
      {
      occurences[i+1] = occ;
      tri_descripteurs[i+1] = liste_descripteurs[pos];
      break;
      }
    }
  }

  fclose(ptr_fic);
  return occ;
}

//On récupère les titres correspondants à nos descripteurs.
void Recup_Titres(int num)
{
  int num_texte;
  char num_descripteur[1000];

  sprintf(num_descripteur,"%d",num);

  strcpy(association,"cut -f2 -d ' ' ");
  strcat(association,CHEMIN2);
  strcat(association,"NomDesFichiers | grep -x -n -i ");
  strcat(association,num_descripteur);
  strcat(association," > ");
  strcat(association,CHEMIN);
  strcat(association,"ligne_descripteur.temp");
  system(association);

  strcpy(association,"cut -f1 -d ':' ");
  strcat(association,CHEMIN);
  strcat(association,"ligne_descripteur.temp >> ");
  strcat(association,CHEMIN);
  strcat(association,"ligne_descripteur.temp");
  system(association);

  ptr_fic = fopen("ligne_descripteur.temp","r");

  if(ptr_fic != NULL)
  {
    fscanf(ptr_fic,"%*s %d",&ligne);
  }

  fclose(ptr_fic);

  char num_ligne[10];
  sprintf(num_ligne,"%d",ligne);

  strcpy(association,"head ");
  strcat(association,"-");
  strcat(association,num_ligne);
  strcat(association," ");
  strcat(association,CHEMIN2);
  strcat(association, "NomDesFichiers | tail -1 | cut -f1 -d ' '");

  if(z == 0)
  {
    strcat(association, " > ");
    z = 45;
  }
  else
  {
    strcat(association, " >> ");
  }
  strcat(association, CHEMIN);
  strcat(association, "fichiers_bons.temp");

  system(association);
}

//On affiche la liste des textes par ordre de pertinence.
void afficher_liste_textes()
{
  printf("Voici les textes en rapport avec %s :\n\n",mot_choisi);

  strcpy(nl,"nl ");
  strcat(nl,CHEMIN);
  strcat(nl,"fichiers_bons.temp");
  system(nl);

  printf("\n\n");
}

//La fonction qui permet de rechercher tous les textes correspondants à la recherche de l'utilisateur.
void Recup_textes()
{
    z = 0;
    int num_texte;
    int nouveau_texte;
    int nb_descripteurs_variable;
    nb_occ_min = 5;

    Recup_descripteurs();
    nb_descripteurs = compter_mots(CHEMIN,"descripteurs_correspondants.temp");
    nb_descripteurs_variable = nb_descripteurs;

    Enregistrer_descripteurs();

    for(i=0;i < nb_descripteurs;i++)
    {
      Isoler_descripteur(liste_descripteurs[i]);
      Occurences_par_descripteurs(mot_choisi);
      int x = Recup_occurences(i);

      printf("%d ",x);

      if(x < nb_occ_min)
      {
        nb_descripteurs_variable--;
      }
    }

    printf("%d",nb_descripteurs_variable);

    for(i=0;i < nb_descripteurs_variable;i++)
    {
      Recup_Titres(tri_descripteurs[i]);
    }

    ptr_fic = fopen("fichiers_bons.temp","r");

    if(ptr_fic != NULL)
    {
      fscanf(ptr_fic,"%s",titre);
    }

    afficher_liste_textes();
    num_texte = 1;

    fclose(ptr_fic);


    //strcpy(CHEMIN3,lirechemin());

    Ouverture(CHEMIN3,titre);

    if(nb_descripteurs_variable > 1)
    {
      do
      {
        afficher_liste_textes();

        printf("Ouvert : texte n°%d \n", num_texte);
        printf("Autre fichier ? Tapez son numéro (de 1 à %d) ou 0 pour terminer : ",nb_descripteurs_variable);

        while(scanf("%d",&nouveau_texte) != 1)
        {
          printf("Je n'ai pas compris\n\n");
          printf("Ouvert : texte n°%d \n", num_texte);
          printf("Autre fichier ? Tapez son numéro (de 1 à %d) ou 0 pour terminer : ",nb_descripteurs_variable);
          vider_buffer();
        }

        if(nouveau_texte != 0)
        {
          if(nouveau_texte <0 || nouveau_texte > nb_descripteurs)
          {
            printf("Numéro inconnu !! \n\n");
          }
          else
          {
            num_texte = nouveau_texte;
            ptr_fic = fopen("fichiers_bons.temp","r");

            if(ptr_fic != NULL)
            {
              for(i=1;i<num_texte;i++)
              {
                fscanf(ptr_fic,"%*s");
              }
              fscanf(ptr_fic,"%s",titre);
            }

            fclose(ptr_fic);

            //strcpy(CHEMIN3,lirechemin());
            Ouverture(CHEMIN3,titre);
          }
        }
      }while(nouveau_texte != 0);
    }
}