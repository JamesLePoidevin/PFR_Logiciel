#include "IndexationImageNB.h"

char CHEMIN_NB [100] =  "../TEST_NB/";

//fonction lecture fichier
void lecture_image(FILE* ptr_fil,int ligne,int colonne,float tab[2]){
	int x;
	if(ptr_fil!=NULL){
		while(fscanf(ptr_fil,"%d ",&x)==1){
			if (x==0)
			{
				tab[0]+=1;
			}else
			tab[1]+=1;
		}
		//tab[0]=tab[0];
		//tab[1]=tab[1]/(ligne*colonne))*100;
	}
}



void listeDeFichiers1(char *adresseDeBase,char *fichierDArriver){
	char commande[1024];
	strcpy(commande, "ls -l ");
	strcat(commande, adresseDeBase);
	strcat(commande, " >");
	strcat(commande, fichierDArriver);
	system(commande);
	printf("%s\n", 	commande);
}

char* cheminImage(){
	//Prend la ligne 8 du fichier
	system("sed -n \"8 p\" ./Param/param_indexation > adress.temp");

	char* adresse = malloc(128 * sizeof(char));

	//pointeur fichier
	FILE * ptr_adresse;

	ptr_adresse = fopen("adress.temp","r");

	//si ca c'est bien ouvert
	if(ptr_adresse != NULL){

		fscanf(ptr_adresse,"%s",adresse);
	
	}

	fclose(ptr_adresse);

	return adresse;
}

//création liste fichiers
int NomDesFichiers1(char *CHEMIN){
	listeDeFichiers1(CHEMIN,"adresse");
	system("sed '/.bmp/d' adresse > adresse1");
	system("rm adresse");
	int IndiceDesNom = 0;
	char NomDuFichier[1024];

	FILE *ptr_fic;
	FILE *ptr_fichier;
	ptr_fic = fopen("adresse1", "r");
	ptr_fichier = fopen("../Source/FILES/NomDesFichiersImageNB", "w");
	if(ptr_fichier != NULL){
		if( ptr_fic != NULL){
    		fscanf( ptr_fic, "%*s %*s");      /* SAUTER LA PREMIERE LIGNE CONSTITUEE DE 2 CHAINES total xxxx */

    		fscanf(ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier);  /* %*s IGNORE LA CHAINE LUE */
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
	system("rm adresse1");
	return IndiceDesNom;

}

/*void indexationCompleteNB(){
	char*camino;
	FILE *ptr_chemin;
	int ref;
	type_descNB NB;
	PILE p = init_PILE();
	char* nomfic= malloc(150 * sizeof(char));;
	char* adr = malloc(150 * sizeof(char));
	nomfic=(char*)malloc(1024*sizeof(char));
	camino=(char*)malloc(1024*sizeof(char));
	strcpy(camino,CHEMIN_NB); // à lire dans un fichier créé par Jean-Sébastien
	NomDesFichiers(CHEMIN_NB);

	ptr_chemin=fopen("../Source/FILES/NomDesFichiersImageNB","r");
	if(ptr_chemin!=NULL){
		while(!feof(ptr_chemin)){
			float tab[2]={0,0};
			fscanf(ptr_chemin,"%s %d",nomfic,&ref);
			strcpy(adr, camino);
			strcat(adr, nomfic);
			lecture_image(adr, tab);
			NB.ref = ref;
			for (int i = 0; i < 2; i++)
			{
				NB.tab[i]=tab[i];
			}
			p = emPILE(p, NB);

		}
	}else fprintf(stderr,"ERREUR de pointeur NDFI");
	fclose(ptr_chemin);
	ptr_chemin=fopen("../Source/FILES/DescripteurImageNB","w");
	while(PILE_estVide(p)!=1){
		type_descNB A;
		p = dePILE(p,&A);
		fprintf(ptr_chemin,"%d\n",A.ref );
		fprintf(ptr_chemin, "%f \n%f\n",A.tab[0],A.tab[1]);
	}
	fclose(ptr_chemin);
	free(camino);
	free(nomfic);
}*/
/*
int main(int argc, char const *argv[])
{
	indexationCompleteNB();
	system("gedit ../Source/FILES/DescripteurImageNB &");
	return 0;
}*/
