#include "LectureFichiers.h"


/**
 * Crée le descripteur du chemin adresse et avec la ref reference
 * @param  adresse   chemin de l'adresse à indexer
 * @param  reference reference
 * @return           descripteur
 */
/*type_des FaireDescripteur(char adresse[],int reference){
	int IndiceDuTableauTab;
	enleverBalise(adresse,"fichieraux1")
	CompterMot("fichieraux1", "NombreDeMotFichier");
	type_des A = init_des();

	FILE *ptr_fichier;
	ptr_fichier = fopen("NombreDeMotFichier", "r");

	if( ptr_fichier != NULL)
	{
		int nbDeMot = NombreDeMot(ptr_fichier);
		fclose(ptr_fichier);

		type_mot tab[nbDeMot];
		type_mot tab2[nbDeMot];

		FILE *ptr_fic;
	    ptr_fic = fopen("FichierAux1", "r");	//fichierAux1 crée dans remove balise
	    if(ptr_fic!=NULL){
		IndiceDuTableauTab =read_word(ptr_fic,tab);
		fclose(ptr_fic);
	}

	Trier_tab_mot(tab,tab2,IndiceDuTableauTab);
	A=CreerDescriteur(reference,tab2);
	return A;
	//remove("FichierAux1");
}
return A;
}*/

/**
 * lit le nombre de mots dans un fichier
 * @param  fichierMot pointeur de fichier
 * @return            nb mot ou 0
 */
int NombreDeMot(FILE *fichierMot){
	int mot=0;
	if( fichierMot != NULL)
	{
		fscanf(fichierMot, "%d %*s",&mot);
		return mot;
	}
	return 0;
}

/**
 * lit un fichier mot par mot et met dans un tableau 
 * @param  f   pointeur de fichier
 * @param  tab tableau qui va eêre rempli des mots
 * @return     renvoie l'indice du tableau
 */
int read_word(FILE *f,type_mot tab[]) {
	char x[1024];
	char BM[1024];
	int indice =0;
	int etat =0;
	int etat1=0;
	FILE *ptr_BLACKLIST;
	if (f != NULL) {
		while ( fscanf(f," %s",x)==1 ){
			//printf("%s\n", x);
			etat1 = 0;
			etat = 0;
			if(indice == 0){
				if(strlen(x)>3){	//vérifie que la longueur de x est sup a
					ptr_BLACKLIST=fopen("../APPLICATION/BLACKLIST","r");
					if(ptr_BLACKLIST!=NULL){
						while(fscanf(ptr_BLACKLIST, "%s",BM)==1){						
							if(strcmp(BM, x)==0){
								etat1 = 1;
							}
						}
					}else {printf("ERREUR pointeur BLACKLIST\n");}
					if(etat1==0){
						strcpy(tab[0].mot,x);
						tab[0].occurence= 1;
						indice =1;
					}
					fclose(ptr_BLACKLIST);
				}
			}else{
				for (int i = 0; i < indice; i++)
				{
					if(strcmp(tab[i].mot,x)==0)
					{
						tab[i].occurence +=1;
						etat = 1;
					}
				}
				if(etat == 0){
					if((int)strlen(x)>3){
						ptr_BLACKLIST=fopen("../APPLICATION/BLACKLIST","r");
						if(ptr_BLACKLIST!=NULL){
							while(fscanf(ptr_BLACKLIST, "%s",BM)==1){
								if(strcmp(BM, x)==0){
									etat1 = 1;
								}
							}
						}else {printf("ERREUR pointeur BLACKLIST\n");}
						if(etat1==0){
							strcpy(tab[indice].mot,x);
							tab[indice].occurence= 1;
							indice=indice+1;
						}
						fclose(ptr_BLACKLIST);
					}
				}
			}
		}
	}else fprintf(stderr, "erreur pointeur read_word\n");

	return indice;

}

/**
 * créé un fichier avec les nom des fichier
 * @param  CHEMIN        dossier où se trouve les fichiers
 * @param  adresseArrive l'adresse d'arrivée du fichier
 * @return               nombre de fichiers
 */
int NomDesFichiers(char *CHEMIN,char *adresseArrive){
	listeDeFichiers(CHEMIN,"adresse");
	FILE *ptr_fic;
	FILE *ptr_fichier;
	ptr_fic = fopen("adresse", "r");
	char commande[1024];
	strcpy(commande,"../APPLICATION/FILES/");	//créé le fichier a l'adresse : ../Source/FILES/adresseArrive
	strcat(commande,adresseArrive);
	ptr_fichier = fopen(commande, "w");
	int IndiceDesNom = 0;
	char NomDuFichier[1024];
	if( ptr_fic != NULL)
	{
    fscanf( ptr_fic, "%*s %*s");      /* SAUTER LA PREMIERE LIGNE CONSTITUEE DE 2 CHAINES total xxxx */

    //fscanf(ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier);  /* %*s INGNORE LA CHAINE LUE */
		while (fscanf( ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier)==1)
		{
			IndiceDesNom++;
			//fscanf( ptr_fic, "%*s %*s %*s %*s %*s %*s %*s %*s %s", NomDuFichier);
			fprintf(ptr_fichier, "%s %d\n", NomDuFichier,IndiceDesNom);
		}
		fclose(ptr_fic);
		fclose(ptr_fichier);
	}
	else
	{
		fprintf(stderr, "ERREUR :  PB avec liste_rep\n");
	}
	return IndiceDesNom;
}
