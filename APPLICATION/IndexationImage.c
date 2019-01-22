#include "IndexationImage.h"

char * CHEMINIMAGE ="../IMAGE/";

int NomDesFichiersImage(char *CHEMIN){
	listeDeFichiers1(CHEMINIMAGE,"adresse");
	system("sed '/.jpg/d' adresse > adresse1");
	system("rm adresse");
	//listeDeFichiers2(CHEMINIMAGE,"adresse1");
	system("sed '/.bmp/d' adresse1 > adresse");
	system("rm adresse1");

	int IndiceDesNom = 0;
	char NomDuFichier[1024];

	FILE *ptr_fic;
	FILE *ptr_fichier;
	ptr_fic = fopen("adresse", "r");
	ptr_fichier = fopen("../APPLICATION/FILES/NomDesFichiersImage", "w");
	if(ptr_fichier != NULL){
		if( ptr_fic != NULL){
        fscanf( ptr_fic, "%*s %*s");      /* SAUTER LA PREMIERE LIGNE CONSTITUEE DE 2 CHAINES total xxxx */

        fscanf(ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier);  /* %*s INGNORE LA CHAINE LUE */
			while ( !feof(ptr_fic) )
			{
				IndiceDesNom++;
				fscanf( ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier);
				fprintf(ptr_fichier, "%s %d\n", NomDuFichier,IndiceDesNom);
			}
			fclose(ptr_fic);
			fclose(ptr_fichier);
		}else fprintf(stderr, "ERREUR :  PB avec liste_rep\n");
	}else fprintf(stderr, "ERREUR :  PB avec liste_rep\n");
	system("rm adresse");
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

	char* nomfic= malloc(150 * sizeof(char));;
	char* adr = malloc(150 * sizeof(char));
	char *adresse=malloc(1024*sizeof(char));

  strcpy(adresse,CHEMINIMAGE); // à lire dans un fichier créé par Jean-Sébastien
  NomDesFichiersImage(adresse);

  ptr_chemin=fopen("../APPLICATION/FILES/NomDesFichiersImage","r");
  if(ptr_chemin!=NULL){
  	while( fscanf(ptr_chemin,"%s",nomfic)==1){
  		fscanf(ptr_chemin,"%d",&ref);
  		//printf("%d\n",ref);
  		strcpy(adr, adresse);
  		strcat(adr, nomfic);
  		FILE* ptr_img;
  		ptr_img = fopen(adr,"r");
  		fscanf(ptr_img,"%d %d %d",&ligne,&colonne,&nbmatrice);
  		if (nbmatrice == 3)
  		{
  			//printf("%d\n",ref);
  			lectureImage2(ptr_img,ligne,colonne,tab);
  			RGB.ref = ref;
  			for (int i = 0; i < 64; i++)
  			{
  				RGB.tab[i]=tab[i];
  			}
  			p = emPILERGB(p, RGB);
  		}else{
  			lecture_image(ptr_img,ligne,colonne,tab2);
  			NB.ref = ref;
  			NB.tab[0]=tab2[0];
  			NB.tab[1]=tab2[1];
  			pNB = emPILENB(pNB,NB);
  		}
  		fclose(ptr_img);
  	}
  }else fprintf(stderr, "ERREUR avec pointeur CHEMIN\n");
  FILE* ptr_ImageRGB;
  FILE* ptr_ImageNB;

  ptr_ImageRGB = fopen("../APPLICATION/FILES/DescripteurImageRGB","w");
  if(ptr_ImageRGB!=NULL){
  	while(PILE_estVideRGB(p)!=1){
  		p = dePILERGB(p,&RGB);
  		fprintf(ptr_ImageRGB, "%d\n",RGB.ref);
  		for (int i = 0; i < 64; i++){
  				fprintf(ptr_ImageRGB,"%f \n",RGB.tab[i]);
  		}
  	}
  }else fprintf(stderr, "ERREUR pointeur fichier DescripteurImageRGB\n");

  ptr_ImageNB = fopen("../APPLICATION/FILES/DescripteurImageNB","w");
  if(ptr_ImageNB!=NULL){
  	while(PILE_estVideNB(pNB)!=1){
  		pNB = dePILENB(pNB,&NB);
  		fprintf(ptr_ImageNB, "%d\n",NB.ref);
  		for (int i = 0; i < 2; i++){
  				fprintf(ptr_ImageNB,"%f\n",NB.tab[i]);
  		}
  	}
  }else fprintf(stderr, "ERREUR pointeur fichier DescripteurImageRGB\n");

  fclose(ptr_ImageRGB);
  fclose(ptr_ImageNB);
  fclose(ptr_chemin);
}
