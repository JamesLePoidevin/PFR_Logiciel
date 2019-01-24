#include "configuration.h"


float test_pourcentage(){      // cas où on souhaite un entier ou un float
  char nombre[50] = "";
  int num = 0;
  char zero[] = "0";

  scanf("%s", nombre);

  if (atof(nombre) == 0 && strcmp(zero, nombre) != 0){
    return 150;
  }
  else return atof(nombre);
}


//VISUALISER LES DESCRIPTEURS
//Pour les descipteurs de texte
void affiche_descripteur_texte(){
  system("clear");
  system("cat ./FILES/Descripteur");
}

//Pour les descripteurs image noir et blanc
void affiche_descripteur_image_NB(){
  system("clear");
  system("cat ./FILES/DescripteurImageNB");
}

//Pour les descipteurs image couleur
void affiche_descripteur_image_coul(){
  system("clear");
  system("cat ./FILES/DescripteurImageRGB");
}

//MENU VISUALISER DESCRIPTEURS
void menu_descripteur(){
  //system("clear");
  printf("\nMenu d'affichage des descripteurs:\n1-Visualiser les descripteurs de texte\n2-Visualiser les descripteurs d'image noir et blanc\n3-Visualiser les descripteurs d'image couleur\n4-Retour au Mode administrateur\n5-Quitter le programme\n");
  int n;
  n = test_int();
  switch(n){
    case 1 :
      system("clear");
      affiche_descripteur_texte(); //Ce choix permet de visualiser les descripteurs texte
      menu_descripteur();
      break;
    case 2 :
      system("clear");
      affiche_descripteur_image_NB(); //Ce choix permet de visualiser les descripteurs d'image noir et blanc
      menu_descripteur();
      break;
    case 3 :
      system("clear");
      affiche_descripteur_image_coul(); //Ce choix permet de visualiser les descipteurs d'image couleur
      menu_descripteur();
      break;
    case 4 :
      system("clear"); //Ce choix permet de retourner au menu du mode administrateur
      menu_admin();
      break;
    case 5 :
      return;
      break;
    default :
      system("clear");
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
      menu_descripteur();
    }
}


//PARAMETRAGE RECHERCHE
void param_recherche_texte(){
  system("clear");
  printf("\n1-Changer les paramètres de recherche\n2-Retour au Mode administrateur\n");
  int n;
  n = test_int();
  if (n==1){
    char nbr_mots_txt_char[50];
    int nbr_mots_txt;
    do {
      printf("Combien de fois minimum faut-il qu'il y ait le mot dans le texte pour que le logiciel affiche le descripteur?\n");
      nbr_mots_txt = test_int();
      sprintf(nbr_mots_txt_char,"%d",nbr_mots_txt);
      if (nbr_mots_txt<1){
        system("clear");
        printf("Erreur: Le nombre entré n'est pas conforme.\n");
      }
    }while(nbr_mots_txt<1);
    //system("sed -i '2s/.*/%nbr_mots%/'  param_indexation.txt"); //Suppression de la deuxième ligne du fichier param_recherche.txt et remplacement par le nouveau nbr_mot_txt
    char commande[1024];
    strcpy(commande,"sed -i '2s/.*/"); //Suppression de la deuxième ligne du fichier param_recherche.txt
    strcat(commande, nbr_mots_txt_char);
    strcat(commande,"/'  Param/param_recherche"); //Remplacement de la deuxième ligne du fichier param_recherche.txt, avec le nouveau nombre
    system(commande);
    system("clear");
    printf("\nLes paramètres de recherche ont été modifiés avec succès.\n");
    param_recherche_texte();
  }
  else if(n==2){
    system("clear");
    menu_admin(); //Ce choix permet de revenir au mode administrateur
  }
  else{
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
      param_recherche_texte();
  }
}


//PARAMETRAGE COMPARAISON
//Textes
void param_compar_texte(){
  system("clear");
  char seuil_compar_char[50];
  float seuil_compar;
  do {
    printf("Quel seuil de similarité voulez-vous pour la comparaison de textes? (en pourcentage)\n");
    seuil_compar = test_pourcentage();
    sprintf(seuil_compar_char,"%f",seuil_compar);
    if (seuil_compar<0 || seuil_compar>100){
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
    }
  }while(seuil_compar<0 || seuil_compar>100);
  //system("sed -i '2s/.*/%nbr_mots%/'  param_indexation.txt"); //Suppression de la deuxième ligne du fichier param_comparaison.txt et remplacement par le nouveau seuil_compar
  char commande[1024];
  strcpy(commande,"sed -i '2s/.*/"); //Suppression de la deuxième ligne du fichier param_comparaison.txt
  strcat(commande, seuil_compar_char);
  strcat(commande,"/'  Param/param_comparaison"); //Remplacement de la deuxième ligne du fichier param_comparaison.txt, avec le nouveau seuil
  printf("%s",commande);
  system(commande);
}

//Images Noir et Blanc
void param_compar_img_nb(){
  //system("clear");
  char seuil_compar_img_nb_char[50];
  float seuil_compar_img_nb;
  do {
    printf("Quel seuil de similarité voulez-vous pour la comparaison d'images en noir et blanc? (en pourcentage)\n");
    seuil_compar_img_nb = test_pourcentage();
    sprintf(seuil_compar_img_nb_char,"%f",seuil_compar_img_nb);
    if (seuil_compar_img_nb<0 || seuil_compar_img_nb>100){
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
    }
  }while(seuil_compar_img_nb<0 || seuil_compar_img_nb>100);
  //system("sed -i '2s/.*/%nbr_mots%/'  param_indexation.txt"); //Suppression de la quatrième ligne du fichier param_comparaison.txt et remplacement par le nouveau seuil_compar
  char commande[1024];
  strcpy(commande,"sed -i '4s/.*/"); //Suppression de la quatrième ligne du fichier param_comparaison.txt
  strcat(commande, seuil_compar_img_nb_char);
  strcat(commande,"/'  Param/param_comparaison"); //Remplacement de la quatrième ligne du fichier param_comparaison.txt, avec le nouveau seuil
  system(commande);
}

//Images Couleur
void param_compar_img_coul(){
  system("clear");
  char seuil_compar_img_coul_char[50];
  float seuil_compar_img_coul;
  do {
    printf("Quel seuil de similarité voulez-vous pour la comparaison d'images en couleur? (en pourcentage)\n");
    seuil_compar_img_coul = test_pourcentage();
    sprintf(seuil_compar_img_coul_char,"%f",seuil_compar_img_coul);
    if (seuil_compar_img_coul<0 || seuil_compar_img_coul>100){
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
    }
  }while(seuil_compar_img_coul<0 || seuil_compar_img_coul>100);
  //system("sed -i '2s/.*/%nbr_mots%/'  param_indexation.txt"); //Suppression de la sixième ligne du fichier param_comparaison.txt et remplacement par le nouveau seuil_compar
  char commande[1024];
  strcpy(commande,"sed -i '6s/.*/"); //Suppression de la sixième ligne du fichier param_comparaison.txt
  strcat(commande, seuil_compar_img_coul_char);
  strcat(commande,"/'  Param/param_comparaison"); //Remplacement de la sixième ligne du fichier param_comparaison.txt, avec le nouveau seuil
  system(commande);
}

//Menu pour comparaison
void menu_comparaison(){
  printf("\nMenu modification des seuils de similarité pour la comparaison:\n1-Seuil pour les descripteurs texte\n2-Seuil pour les descripteurs image noir et blanc\n3-Seuil pour les descripteurs image couleur\n4-Retour au Mode administrateur\n5-Quitter le programme\n");
  int n;
  n = test_int();
  switch(n){
    case 1 :
      param_compar_texte(); //Ce choix permet de changer le chemin des fichiers texte
      system("clear");
      printf("\nLes paramètres de comparaison ont été modifiés avec succès.\n");
      menu_comparaison();
      break;
    case 2 :
      param_compar_img_nb(); //Ce choix permet de changer le chemin des fichiers image noir et blanc
      system("clear");
      printf("\nLes paramètres de comparaison ont été modifiés avec succès.\n");
      menu_comparaison();
      break;
    case 3 :
      param_compar_img_coul(); //Ce choix permet de changer le chemin des fichiers image couleur
      system("clear");
      printf("\nLes paramètres de comparaison ont été modifiés avec succès.\n");
      menu_comparaison();
      break;
    case 4 :
      menu_admin();  //Ce choix permet de retourner au menu du mode administration
      break;
    case 5 :
      return;
      break;
    default :
      system("clear");
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
      menu_comparaison();
    }
    system("clear");
    //  printf("Le fichier a été modifié avec succès.\n");
}


//PARAMETRAGE INDEXATION
// Texte
void param_index_texte(){
  system("clear");
  char nbr_mots_char[50];
  int nbr_mots;
  do {
    printf("Combien de mots voulez vous dans vos descripteurs de texte? (strictement supérieur à 0)\n");
    nbr_mots = test_int();
    sprintf(nbr_mots_char,"%d",nbr_mots);
    if (nbr_mots<1){
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
    }
  }while(nbr_mots<1);
  //system("sed -i '2s/.*/%nbr_mots%/'  param_indexation.txt"); //Suppression de la deuxième ligne du fichier param_indexation.txt et remplacement par le nouveau nbr_mot
  char commande[1024];
  strcpy(commande,"sed -i '2s/.*/"); //Suppression de la deuxième ligne du fichier param_indexation.txt
  strcat(commande, nbr_mots_char);
  strcat(commande,"/'  Param/param_indexation"); //Remplacement de la deuxième ligne du fichier param_indexation.txt, avec le nouveau nombre
  system(commande);
}

//Image
void param_index_image(){
  system("clear");
  char nbr_bits_char[50];
  int nbr_bits;
  do {
    printf("Combien de bits pour la quantification voulez-vous dans vos descipteurs d'image? (nombre entre 1 et 8)\n");
    nbr_bits = test_int();
    if(nbr_bits>8 || nbr_bits<=0){
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
    }
  }while(nbr_bits>8 || nbr_bits<=0);
  sprintf(nbr_bits_char,"%d",nbr_bits);
  char commande[1024];
  strcpy(commande, "sed -i '4s/.*/"); //Suppression de la quatrième ligne du fichier param_indexation.txt
  strcat(commande, nbr_bits_char);
  strcat(commande,"/' Param/param_indexation"); //Remplacement de la quatrième ligne du fichier param_indexation.txt, avec le nouveau nombre
  system(commande);
}

//Menu indexation (choix entre texte ou image)
void menu_index(){
  printf("Menu indexation:\n1-Paramétrer l'indexation des textes\n2-Paramétrer l'indexation des images\n3-Retour au Mode administrateur\n4-Quitter le programme\n");
  int n;
  n = test_int();
  switch(n){
    case 1 :
      param_index_texte(); //Ce choix permet de changer les paramètres d'indexation du texte
      system("clear");
      printf("\nLes paramètres d'indexation ont été modifiés avec succès.\n");
      menu_index();
      break;
    case 2 :
      param_index_image(); //Ce choix permet de changer les paramètres d'indexation d'image
      system("clear");
      printf("\nLes paramètres d'indexation ont été modifiés avec succès.\n");
      menu_index();
      break;
    case 3 :
      menu_admin();
    case 4 :
      return;
      break;
    default :
      system("clear");
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
      menu_index();
  }
  system("clear");
  printf("Le fichier a été modifié avec succès.\n");
}


//Chemin d'accès des textes
void chemin_texte(){
  system("clear");
  char* ch_txt;
  ch_txt =(char*) malloc(1000*sizeof(char));
  char commande[1024];
  printf("Où souhaitez vous placer vos fichiers? (chemin absolu ou à partir de ce fichier)\n");
  scanf("%s", ch_txt);
  strcpy(commande, "sed -i '6s#.*#");
  strcat(commande, ch_txt);
  strcat(commande,"#' Param/param_indexation");
  system(commande);
}

//Chemin d'accès des images noir et blanc
void chemin_image_nb(){
  system("clear");
  char* ch_img_nb;
  ch_img_nb =(char*) malloc(1000*sizeof(char));
  char commande[1024];
  printf("Où souhaitez vous placer vos fichiers? (chemin absolu ou à partir de ce fichier)\n");
  scanf("%s", ch_img_nb);
  strcpy(commande, "sed -i '8s#.*#");
  strcat(commande, ch_img_nb);
  strcat(commande,"#' Param/param_indexation");
  system(commande);
}


//Chemin d'accès des images couleur
void chemin_image_coul(){
  system("clear");
  char* ch_img_coul;
  ch_img_coul =(char*) malloc(1000*sizeof(char));
  char commande[1024];
  printf("Où souhaitez vous placer vos fichiers? (chemin absolu ou à partir de ce fichier)\n");
  scanf("%s", ch_img_coul);
  strcpy(commande, "sed -i '10s#.*#");
  strcat(commande, ch_img_coul);
  strcat(commande,"#' Param/param_indexation");
  system(commande);
}

//Menu modification chemins (choix entre texte, image noir et blanc, image couleur)
void menu_chemins(){
  printf("Menu modification des chemins:\n1-Chemin pour les fichiers texte\n2-Chemin pour les fichiers image noir et blanc\n3-Chemin pour les fichiers image couleur\n4-Retour au Mode administrateur\n5-Quitter le programme\n");
  int n;
  n = test_int();

  switch(n){
    case 1 :
      chemin_texte(); //Ce choix permet de changer le chemin des fichiers texte
      system("clear");
      printf("\nLe chemin a été modifié avec succès.\n");
      menu_chemins();
      break;
    case 2 :
      chemin_image_nb(); //Ce choix permet de changer le chemin des fichiers image noir et blanc
      system("clear");
      printf("\nLe chemin a été modifié avec succès.\n");
      menu_chemins();
      break;
    case 3 :
      chemin_image_coul(); //Ce choix permet de changer le chemin des fichiers image couleur
      system("clear");
      printf("\nLe chemin a été modifié avec succès.\n");
      menu_chemins();
      break;
    case 4 :
      menu_admin();  //Ce choix permet de retourner au mode administrateur
      break;
    case 5 :
      return;
      break;
    default :
      system("clear");
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
      menu_chemins();
    }
    system("clear");
    printf("Le fichier a été modifié avec succès.\n");
}

//MENU GÉNÉRAL DU MODE CONFIGURATION
void menu_admin(){
  system("clear");
  printf("Menu Mode Administrateur:\n1-Visualiser les descripteurs\n2-Accéder aux paramètres de recherche\n3-Accéder aux paramètres de comparaison\n");
  printf("4-Accéder aux paramètres d'indexation\n5-Changer les chemins\n6-Lancer l'indexation complète\n7-Accéder au Mode Utilisateur\n8-Quitter le programme\n");
  int n;
  n=test_int();
  switch(n){
    case 1 :
      menu_descripteur(); //Ce choix permet d'accéder au menu pour visauliser les descripteurs
      break;
    case 2 :
      param_recherche_texte(); //Ce choix permet de changer les paramètres de recherche
      break;
    case 3 :
      system("clear");
      menu_comparaison(); //Ce choix permet d'accéder au menu pour changer les paramètres de comparaison
      break;
    case 4 :
      system("clear");
      menu_index(); //Ce choix permet d'accéder au menu pour changer les paramètres d'indexation
      break;
    case 5 :
      system("clear");
      menu_chemins(); //Ce choix permet d'accéder au menu pour changer les chemins
      break;
    case 6 :
      IndexationComplet(); //Ce choix permet de lancer l'indéxation
      printf("L'indexation a bien été effectuée.\n");
      sleep(2);
      menu_admin();
      break;
    case 7 :
      menu_user();
      break;
    case 8 :
      return;
      break;
    default :
      printf("Erreur: Le nombre entré n'est pas conforme.\n");
      menu_admin();
  }
  //system("clear");
}
