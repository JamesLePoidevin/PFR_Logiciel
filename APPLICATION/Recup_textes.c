#include "Recup_textes.h"

//récupère la liste des descripteurs correspondants au mot choisi.
void Recup_descripteurs()
{
  char cut[1000];//Contiendra la commande.

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
  FILE* ptr_fic;
  int i;

  ptr_fic = fopen("descripteurs_correspondants.temp","r");//On ouvre la liste des descripteurs contenant le mot choisi.

  if(ptr_fic != NULL)
  {
    for(i=0;i < nb_descripteurs;i++)
    {
      fscanf(ptr_fic,"%d ",&liste_descripteurs[i]); //on enregistre le numéro de chaque descripteur dans liste_descripteur (déclaré dans recup_textes.h)
    }
  }

  fclose(ptr_fic);
}

//On isole un descripteur pour pouvoir le traiter en donnant son numéro en paramètre.
void Isoler_descripteur(int num)
{
    FILE* ptr_fic;
    int nb_termes; //Nombre de termes dans un descripteur.
    int ligne; //ligne de début du descripteur (là où se trouve son numéro d'identification).
    char isolement[1000];//Contiendra la commande pour isoler le descripteur.
    char association[1000];//on associe le descripteur à sa ligne.
    char num_descripteur[100]; //On enregistre le numéro du descripteur en tant que chaine de caractère.
    char num_ligne[100];//Contiendra e tant que chaîne de caractère le numéro de la ligne où termine le descripteur.
    char taille_descripteur[100];//On y enregistre le nombre de mots clés par descripteur en tant que chaîne de caractère (+1 avec le numéro du descripteur).

    sprintf(num_descripteur,"%d",num); //On transforme le numéro du descripteur en une chaîne de caractères.

    //On recherche dans la base de descripteurs la ligne correspondant exactement au numéro du descripteur.
    //On enregistre cette ligne avec son numéro dans le fichier temporaire ligne_descripteur.temp.
    strcpy(isolement,"grep -x -i -n ");
    strcat(isolement,num_descripteur);
    strcat(isolement," ");
    strcat(isolement,CHEMIN2);
    strcat(isolement,"Descripteur > ");
    strcat(isolement,CHEMIN);
    strcat(isolement,"ligne_descripteur.temp");

    system(isolement);

    //on rècupère seulement le numéro de la ligne où se trouve le descripteur dans la base de descripteur à la suite de ligne_descripteur.temp..
    strcpy(association,"cut -f1 -d ':' ");
    strcat(association,CHEMIN);
    strcat(association,"ligne_descripteur.temp >> ");
    strcat(association,CHEMIN);
    strcat(association,"ligne_descripteur.temp");

    system(association);

    ptr_fic = fopen("ligne_descripteur.temp","r"); //On ouvre le fichier avec le numéro de ligne du descripteur voulu.

    if(ptr_fic != NULL)
    {
      fscanf(ptr_fic,"%*s %d",&ligne); //On passe la première ligne et on récupère le numéro de la ligne où commence le descripteur dans la base de descripteurs.
    }

    fclose(ptr_fic);

    system("sed '2,2!d' ./Param/param_indexation > file.temp"); /*On récupère le nombre de termes dans un descripteur depuis le fichier de paramètre.
                                                                  Et on l'envoie dans le fichier temporaire file.temp */


    FILE *ptr_fichierTEMP;

    ptr_fichierTEMP =fopen("file.temp","r");//On ouvre le fichier avec le nombres de termes par descripteur.
    if(ptr_fichierTEMP !=NULL){
    fscanf(ptr_fichierTEMP,"%d",&nb_termes); //On récupère le nombre de termes par descripteur.
    }else fprintf(stderr, "ERREUR pointeur file.temp\n");

    fclose(ptr_fichierTEMP);//On ferme le fichier

    sprintf(num_ligne,"%d",ligne+nb_termes); //On enregistre la ligne de fin du descripteur.
    sprintf(taille_descripteur,"%d",nb_termes+1); //On enregistre la taille d'un descripteur.

    //On isole le descripteur voulu dans le fichier temporaire descripteur_isole.temp.
    strcpy(isolement,"head ");
    strcat(isolement,"-");
    strcat(isolement,num_ligne);
    strcat(isolement," ");
    strcat(isolement,CHEMIN2);
    strcat(isolement,"Descripteur | tail -");
    strcat(isolement,taille_descripteur);
    strcat(isolement," > ");
    strcat(isolement,CHEMIN);
    strcat(isolement,"descripteur_isole.temp");

    system(isolement);
}

//On récupère le nombre d'occurrences du mot choisi (passé en paramètre) dans un descripteur grâce au fichier descripteur_isole.temp.
//On enregistre cette valeur dans le fichier temporaire occ_par_des.temp.
void occurrences_par_descripteurs(char * mot)
{
  char recup_occ[1000]; //Contiendra la commande pour récupérer le nombre d'occurrences

  strcpy(recup_occ,"grep -w -i ");
  strcat(recup_occ,mot);
  strcat(recup_occ," ");
  strcat(recup_occ,CHEMIN);
  strcat(recup_occ,"descripteur_isole.temp | cut -f2 -d ' ' > ");
  strcat(recup_occ,CHEMIN);
  strcat(recup_occ,"occ_par_des.temp");

  system(recup_occ);

}

//On enregistre le nombre d'occurrences de chaque descripteur dans un tableau en les triant en associant le même indice (position passée en paramètre) pour le descripteur et son ocurrence.
//On trie le nombre d'occurrences ce qui nous permet de trier les descripteurs dans un troisième tableau grâce aux indices.
int Recup_occurrences(int pos)
{
  FILE* ptr_fic;
  int occ; //On récupère le nombre d'occurrences du mot choisi dans le dernier descripteur à avoir été isolé.

  ptr_fic = fopen("occ_par_des.temp","r");

  if(ptr_fic != NULL)
  {
    fscanf(ptr_fic,"%d",&occ); //On lit le nombre d'occurrences du mot choisi.

    if(pos==0)//Si la on donne la position 0 il suffit d'enregistrer le descripteur et son nombre d'occurences à l'indice 0.
    {
      occurrences[pos] = occ;
      tri_descripteurs[pos] = liste_descripteurs[pos];
    }
    else
    {
      for(int i = pos-1; i >= 0 ; i--) //On part de la position du dernier descripteur déjà enregistré et on redescend jusqu'au début pour mettre le plus gros nombre d'occurrences au début.
      {
        if(occ > occurrences[i]) //Si le nombre d'occurrences est plus grand que le précédent on les échangent de place jusqu'à avoir placé le descripteur que l'on est entain de traiter.
        {
        occurrences[i+1] = occurrences[i];
        occurrences[i] = occ;
        tri_descripteurs[i+1] = tri_descripteurs[i]; //On tri le descripteur en même temps que son occurrence pour qu'ils aient le même indice.
        tri_descripteurs[i] = liste_descripteurs[pos];
        }
        else //Sinon on laisse l'occurrence et son descripteur à l'indice où ils sont et on sort de la boucle.
        {
        occurrences[i+1] = occ;
        tri_descripteurs[i+1] = liste_descripteurs[pos];
        break;
        }
      }
    }
  }

  fclose(ptr_fic);
  return occ; //On retourne le nombre d'occurrences que l'on vient de traiter.
}

//On récupère les titres correspondants à nos descripteurs en mettant l'identifiant du descripteur en paramètre.
void Recup_Titres(int num)
{
  int num_texte;
  int ligne; //Ligne où se trouve le titre du textes associé au descripteur.
  char num_descripteur[1000]; //recupère l'identifiant du descripteur en tant que chaîne de caractère.
  char association[1000];//Commande pour associer le descripteur à son titre.
  FILE* ptr_fic;

  sprintf(num_descripteur,"%d",num); //On transforme l'identifiant du descripteur en chaîne de caractères.

  //On récupère depuis le fichier avec les titres des textes la ligne où se trouve l'identifiant de notre descripteur (On l'envoie dans ligne_descripteur.temp).
  strcpy(association,"cut -f2 -d ' ' ");
  strcat(association,CHEMIN2);
  strcat(association,"NomDesFichiers | grep -x -n -i ");
  strcat(association,num_descripteur);
  strcat(association," > ");
  strcat(association,CHEMIN);
  strcat(association,"ligne_descripteur.temp");
  system(association);

  //On garde uniquement le numéro de la ligne ou se trouve le descripteur depuis ligne_descripteur.temp (on l'inscrit à la suite de ligne_descripteur.temp).
  strcpy(association,"cut -f1 -d ':' ");
  strcat(association,CHEMIN);
  strcat(association,"ligne_descripteur.temp >> ");
  strcat(association,CHEMIN);
  strcat(association,"ligne_descripteur.temp");
  system(association);

  ptr_fic = fopen("ligne_descripteur.temp","r"); //On ouvre le fichier avec le numéro de ligne.

  if(ptr_fic != NULL)
  {
    fscanf(ptr_fic,"%*s %d",&ligne);//On récupère le numéro de ligne.
  }

  fclose(ptr_fic);

  char num_ligne[10];//Contiendra le numéro de ligne en tant que chaîne de caractère.
  sprintf(num_ligne,"%d",ligne);//On transforme le numéro de ligne en chaîne de caractère.

  //On récupère le titre grâce au numéro de ligne et on fait une liste dans fichiers_bons.temp.
  strcpy(association,"head ");
  strcat(association,"-");
  strcat(association,num_ligne);
  strcat(association," ");
  strcat(association,CHEMIN2);
  strcat(association, "NomDesFichiers | tail -1 | cut -f1 -d ' '");

  //Si c'est le premier titre récupéré on l'envoie dans fichiers_bons.temp
  if(nb_titres == 0)
  {
    strcat(association, " > ");
  }
  else //Sinon on l'ajoute à la suite
  {
    strcat(association, " >> ");
  }
  strcat(association, CHEMIN);
  strcat(association, "fichiers_bons.temp");

  system(association);
  nb_titres++;//On augmente de 1 le nombre de titres récupérés
}

//On affiche la liste des textes par ordre de pertinence avec un numéro devant.
void afficher_liste_textes()
{
  char nl[1000]; //Contiendra la commande
  printf("\nVoici les textes en rapport avec %s :\n\n",mot_choisi);

  strcpy(nl,"nl ");
  strcat(nl,CHEMIN);
  strcat(nl,"fichiers_bons.temp");
  system(nl);

  printf("\n\n");
}



//La fonction qui permet de récupérer tous les textes correspondants à la recherche de l'utilisateur.
void Recup_textes()
{
  int i;
  nb_titres = 0; //On initialise le nombre de titres récupérés à 0;
  int occ_descripteur = 0; //on y enregistrera le nombre d'occurrences du descripteur en train d'être traité
  int seuil_occ; //Nombre d'occurrences minimum pour qu'on affiche le titre du texte
  int num_texte; // Numéro du texte ouvert (1 si le meilleur résultat)
  int nouveau_texte; //Numéro du texte à ouvrir.
  int nb_descripteurs_variable; //Le nombre de descripteurs dépassant le seuil d'occurrences
  char titre[1000];//Contiendra le titre du texte à ouvrir.
  FILE* ptr_fic;

  if(STOP==0) //SI STOP est toujours à 0 (après Recherche() de traiter_mot_cle.c) on fait cette étape.
  {
    system("sed '2,2!d' ./Param/param_recherche > file.temp"); //On envoie le seuil d'occurrences dans file.temp

    FILE *ptr_fichierTEMP;

    ptr_fichierTEMP =fopen("file.temp","r"); //On ouvre le fichier avec le seuil d'occurrences
    if(ptr_fichierTEMP !=NULL){
    fscanf(ptr_fichierTEMP,"%d",&seuil_occ); //On récupère le seuil d'occurrences
    }else fprintf(stderr, "ERREUR pointeur file.temp\n");

    fclose(ptr_fichierTEMP); //On ferme le fichier.

    Recup_descripteurs(); //On récupère la liste de tous les descripteurs contenant le mot choisi.
    nb_descripteurs = compter_mots(CHEMIN,"descripteurs_correspondants.temp"); //On compte le nombre de descripteurs contenant le mot choisi
    nb_descripteurs_variable = nb_descripteurs; //On initialise le nombre des descripteurs dépassant le seuil avec la totalité des descripteurs contenant le mot choisi.

    //On alloue la taille nécessaire aux tableaux qui vont contenir les descripteurs et leurs occurrences.
    liste_descripteurs = malloc(nb_descripteurs * sizeof(int));
    occurrences = malloc(nb_descripteurs * sizeof(int));
    tri_descripteurs = malloc(nb_descripteurs * sizeof(int));

    Enregistrer_descripteurs();

    for(i=0;i < nb_descripteurs;i++) //Jusqu'à avoir traité la totalité des descripteurs
    {
      Isoler_descripteur(liste_descripteurs[i]); //On isole un descripteur
      occurrences_par_descripteurs(mot_choisi); // On compte le nombre d'occurrences du mot choisi dans le descripteur.
      occ_descripteur = Recup_occurrences(i); //On récupère le nombre d'occurrences du mot dans le descripteur
      if(occ_descripteur<seuil_occ) //Si on ne dépasse pas le seuil d'occurrences
      {
        nb_descripteurs_variable --; //On décrémente le nombre de descripteurs à garder
      }
    }

    //On libère la liste des descripteurs non triés ainsi que la liste des occurrences dont on a plus besoin une fois le tri des descripteurs terminé.
    free(liste_descripteurs);
    free(occurrences);

    if(nb_descripteurs_variable == 0)  //Si aucun ne dépasse le seuil on affiche quand même le meilleur résultat
    {
      nb_descripteurs_variable ++;
    }

    for(i=0;i < nb_descripteurs_variable;i++) //On récupère les titres pour les descripteurs dépassant le seuil.
    {
      Recup_Titres(tri_descripteurs[i]);
    }

    afficher_liste_textes(); //On affiche la liste des textes correspondant à la recherche.

    ptr_fic = fopen("fichiers_bons.temp","r"); //On ouvre la liste des textes correspondant à la recherche.

    if(ptr_fic != NULL)
    {
      fscanf(ptr_fic,"%s",titre);//On récupère le titre du meilleur résultat.
    }

    num_texte = 1; //On prend le texte numéro 1.

    fclose(ptr_fic);

    Ouverture(CHEMIN3,titre); //On ouvre le texte correspondant au titre passé en paramètre.

    if(nb_descripteurs_variable > 1) //Si il y a plus qu'un résultat correspondant à la recherche
    {
      do //Tant que l'utilisateur ne demande pas à terminer la recherche.
      {
        afficher_liste_textes(); //On réaffiche la liste.

        printf("Ouvert : texte n°%d \n", num_texte); //On indique quel texte est ouvert.
        printf("\nAutre fichier ? Tapez son numéro (de 1 à %d) ou 0 pour terminer : ",nb_descripteurs_variable); /*On propose d'en ouvrir un autre en tapant son numéro
                                                                                                                   Ou de terminer la recherche en tapant 0.*/

        while(scanf("%d",&nouveau_texte) != 1) //Tant que la saisie n'est pas un entier on affiche un message d'erreur et on repropose d'ouvrir un texte
        {
          printf("\nJe n'ai pas compris\n\n");
          printf("\nOuvert : texte n°%d \n", num_texte);
          printf("\nAutre fichier ? Tapez son numéro (de 1 à %d) ou 0 pour terminer : ",nb_descripteurs_variable);
          vider_buffer();//On vide le buffer pour nettoyer la saisie.
        }

        if(nouveau_texte != 0) //Si l'utilisateur ne demande pas à terminer la recherche
        {
          if(nouveau_texte <0 || nouveau_texte > nb_descripteurs_variable) //Si aucun texte ne porte le numéro saisi on affiche une erreur
          {
            printf("\nNuméro inconnu !! \n\n");
          }
          else
          {
            ptr_fic = fopen("fichiers_bons.temp","r"); //Sinon on ouvre la liste des textes correspondants.

            if(ptr_fic != NULL)
            {
              for(i=1;i<nouveau_texte;i++) //jusqu'au texte qui nous interresse
              {
                fscanf(ptr_fic,"%*s"); //On passe tous les textes
              }
              fscanf(ptr_fic,"%s",titre); //Ensuite on récupère le titre du texte à ouvrir.
            }

            fclose(ptr_fic);

            Ouverture(CHEMIN3,titre); //On ouvre le bon texte
            num_texte = nouveau_texte; //On change le numéro du fichier ouvert;
          }
        }
      }while(nouveau_texte != 0); //Tant qu'on ne demande pas à quitter.
    }
    free(tri_descripteurs); //On peut libérer le tableau où sont rangés les descripteurs triés.
  }
}
