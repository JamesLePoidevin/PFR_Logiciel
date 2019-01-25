////////////////////////////////////////////////////////////////////////////
//Auteur : Amaia Camino                                                   //
//                                                                        //
//Indexation IMAGE                                                        //
//Description: Fichier Pour l'indexation pour tous type d'image           //
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

#include "IndexationImage.h"

//faire focntion

char * CHEMINIMAGE ="../IMAGE/";

int NomDesFichiersImage(char *CHEMIN){
	listeDeFichiers1(CHEMINIMAGE,"adresse");
	
  system("sed '/.jpg/d' adresse > adresse1");
	system("rm adresse");
	
	system("sed '/.bmp/d' adresse1 > adresse");
	system("rm adresse1");

	int IndiceDesNom = 0;
	char NomDuFichier[1024];

	FILE *ptr_fic;
  FILE *ptr_fichier;
	
  //ouverture du fichier adresse en lecture 
  ptr_fic = fopen("adresse", "r");
	
  //ouverture du fichier NomDesFichiersImage en ecriture
  ptr_fichier = fopen("../APPLICATION/FILES/NomDesFichiersImage", "w");
	
  //verification que les fichier se sont bien ouvert
  if(ptr_fichier != NULL){
		if( ptr_fic != NULL){
      

      fscanf( ptr_fic, "%*s %*s");      /* SAUTER LA PREMIERE LIGNE CONSTITUEE DE 2 CHAINES total xxxx */

      //lecture des NomDuFichier tant qu'il y en a, a lire
			while ( fscanf( ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier) == 1){
				
				fprintf(ptr_fichier, "%s %d\n", NomDuFichier,IndiceDesNom); //lecture du nom du fichier et l'indice
			  IndiceDesNom++; //increment le nombre de fichier
      }
			
      //fermeture des fichiers ouvert
      fclose(ptr_fic);
			fclose(ptr_fichier);
		
    }else fprintf(stderr, "ERREUR :  PB avec liste_rep\n");
	
  }else fprintf(stderr, "ERREUR :  PB avec liste_rep\n");
	
  //Enleve le fichier temporaire pour l'adresse
  system("rm adresse");

  //Renvoie le nombre de fichier
	return IndiceDesNom;
}

void Indexation(){

	FILE *ptr_chemin;
	int ligne,colonne,nbmatrice;
	int ref;

  //RGB
	type_descRGB RGB;
	PILERGB p = init_PILERGB();
	float tab[63];
  
  //NB
	type_descNB NB;
	PILENB pNB = init_PILENB();
	float tab2[2];

  //les chaine de caractere nessecaire pour l'indexation d'image
	char* nomfic= malloc(150 * sizeof(char));;
	char* adr = malloc(150 * sizeof(char));
	char *adresse=malloc(1024*sizeof(char));

  //Appelle de la fonction NomDesFichiersImage
  strcpy(adresse,CHEMINIMAGE);
  NomDesFichiersImage(adresse);

  //Ouverture du fichier NomDesFichiersImage
  ptr_chemin=fopen("../APPLICATION/FILES/NomDesFichiersImage","r");
  
  //Si le fichier c'est bien ouvert
  if(ptr_chemin!=NULL){

    //lecture du fichier tant qu'il y a un nomfic a lire
  	while( fscanf(ptr_chemin,"%s",nomfic)==1){
      //Lecture de la reference
  		fscanf(ptr_chemin,"%d",&ref);
  		
  		strcpy(adr, adresse);
  		strcat(adr, nomfic);
  		
      FILE* ptr_img;
  		
      //ouverture du fichier .txt de l'image 
      ptr_img = fopen(adr,"r");
  		
      //Lit le nombre de ligne,colonne et nombre de matrice
      fscanf(ptr_img,"%d %d %d",&ligne,&colonne,&nbmatrice);

  		//Si l'image est en couleur, nombre de matrice = 3
      if (nbmatrice == 3){
  			
        //lit tous l'image et le quantifie et le place dans un tableau/histogramme
  			lectureImage2(ptr_img,ligne,colonne,tab);
  			
        //on place la reference de l'image dans le descripteur RGB
        RGB.ref = ref;
  			
        //on place l'histogramme dans le descripteur RGB
        for (int i = 0; i < 64; i++){
  				RGB.tab[i]=tab[i];
  			}
  			
        //et on l'empile dans la pile de descripteur RGB
        p = emPILERGB(p, RGB);
  		
      }else{

        //indexation des image Noir et Blanc
        tab2[0]=0;
        tab2[1]=0;
  			
        //lecture de tous les pixels a 0 on les places dans la premier case du tableau
        //et le nombre de pixel pas a zero et le met en Pourcentage
        lecture_image(ptr_img,ligne,colonne,tab2);
  			
        //place le resultat dans le descripteur NB
        NB.ref = ref;
  			NB.tab[0]=(tab2[0]/(ligne*colonne))*100;
  			NB.tab[1]=(tab2[1]/(ligne*colonne))*100;
  
        //puis l'empile est dans la pile des descripteur NB
  			pNB = emPILENB(pNB,NB);
  		}
      //ferme le fichier ptr_img
  		fclose(ptr_img);
  	}
  }else fprintf(stderr, "ERREUR avec pointeur CHEMIN\n");


  /////////////////////////////////////////////////Ecriture des descripteur dans les fichier descripteur
  
  //Pointeur de fichier Descripteur RGB et NB
  FILE* ptr_ImageRGB;
  FILE* ptr_ImageNB;

  //Ouverture du fichier DescripteurImageRGB en ecriture
  ptr_ImageRGB = fopen("../APPLICATION/FILES/DescripteurImageRGB","w");

  //tant que le fichier s'ouvre correctement
  if(ptr_ImageRGB!=NULL){

    //tant que la pile n'est pas vide
  	while(PILE_estVideRGB(p)!=1){

      //On dépile le descripteur et on le place dans le descripteur temporaire
  		p = dePILERGB(p,&RGB);

      //On ecrit le descripteur dans le fichier
  		fprintf(ptr_ImageRGB, "%d\n",RGB.ref);
  		for (int i = 0; i < 64; i++){
  				fprintf(ptr_ImageRGB,"%f \n",RGB.tab[i]);
  		}
  	}
  }else fprintf(stderr, "ERREUR pointeur fichier DescripteurImageRGB\n");

  //Ouverture du fichier DescripteurImageNB en ecriture
  ptr_ImageNB = fopen("../APPLICATION/FILES/DescripteurImageNB","w");
  
  //tant que le fichier s'ouvre correctement
  if(ptr_ImageNB!=NULL){
  
    //tant que la pile n'est pas vide
  	while(PILE_estVideNB(pNB)!=1){

      //On dépile le descripteur et on le place dans le descripteur temporaire
  		pNB = dePILENB(pNB,&NB);

      //On ecrit le descripteur dans le fichier
  		fprintf(ptr_ImageNB, "%d\n",NB.ref);
  		for (int i = 0; i < 2; i++){
  				fprintf(ptr_ImageNB,"%f\n",NB.tab[i]);
  		}
  	}
  }else fprintf(stderr, "ERREUR pointeur fichier DescripteurImageNB\n");

  //Fermeture des fichier ouvert
  fclose(ptr_ImageRGB);
  fclose(ptr_ImageNB);
  fclose(ptr_chemin);
}