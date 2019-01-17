Qwante : menu.o menuUser.o configuration.o Recherche.o Recup_textes.o traiter_mot_cle.o global.o Comparaison.o indexationAuto.o indexationComplet.o TriFichier.o LectureFichiers.o pile_statique.o element.o Descripteur.o CommandeSysteme.o Mot.o comparaisonImage.o IndexationImage.o IndexationImageRGB.o elementRGB.o pile_statiqueRGB.o IndexationImageNB.o pile_statiqueNB.o elementNB.o
	gcc -o Qwante menu.o menuUser.o configuration.o Recherche.o Recup_textes.o traiter_mot_cle.o global.o Comparaison.o indexationAuto.o indexationComplet.o TriFichier.o LectureFichiers.o pile_statique.o element.o Descripteur.o CommandeSysteme.o Mot.o comparaisonImage.o IndexationImage.o IndexationImageRGB.o elementRGB.o pile_statiqueRGB.o IndexationImageNB.o pile_statiqueNB.o elementNB.o

menu.o : menu.c
	gcc -c menu.c

menuUser.o : menuUser.c menuUser.h
	gcc -c -g menuUser.c

Comparaison.o : Comparaison.c Comparaison.h
	gcc -c -g Comparaison.c

indexationAuto.o: indexationAuto.c indexationAuto.h
	gcc -c -g indexationAuto.c

indexationComplet.o: indexationComplet.h indexationComplet.c
	gcc -c -g indexationComplet.c

TriFichier.o: TriFichier.c TriFichier.h
	gcc -c -g TriFichier.c

LectureFichiers.o: LectureFichiers.c LectureFichiers.h
	gcc -c -g LectureFichiers.c

pile_statique.o: pile_statique.c pile_statique.h
	gcc -c -g pile_statique.c

element.o: element.c element.h
	gcc -c -g element.c

Descripteur.o: Descripteur.c Descripteur.h
	gcc -c -g Descripteur.c

CommandeSysteme.o: CommandeSysteme.c CommandeSysteme.h
	gcc -c -g CommandeSysteme.c

Mot.o: Mot.c Mot.h
	gcc -c -g Mot.c

configuration.o : configuration.c configuration.h
	gcc -c configuration.c

Recherche.o : Recherche.c Recherche.h
	gcc -c Recherche.c

Recup_textes.o : Recup_textes.c Recup_textes.h
	gcc -c Recup_textes.c

traiter_mot_cle.o : traiter_mot_cle.c traiter_mot_cle.h
	gcc -c traiter_mot_cle.c

global.o : global.c global.h
	gcc -c global.c

IndexationImage:comparaisonImage.o IndexationImage.o IndexationImageRGB.o elementRGB.o pile_statiqueRGB.o IndexationImageNB.o pile_statiqueNB.o elementNB.o
	gcc -o IndexationImage.out comparaisonImage.o IndexationImage.o IndexationImageRGB.o elementRGB.o pile_statiqueRGB.o IndexationImageNB.o pile_statiqueNB.o elementNB.o

comparaisonImage.o:comparaisonImage.c
	gcc -c comparaisonImage.c

IndexationImage.o:IndexationImage.c IndexationImage.h
	gcc -c IndexationImage.c
	
IndexationNB: IndexationImageNB.o pile_statiqueNB.o elementNB.o elementNB.h
	gcc -o indexationNB.out IndexationImageNB.o pile_statiqueNB.o elementNB.o

IndexationImageNB.o: IndexationImageNB.c IndexationImageNB.h
	gcc -c IndexationImageNB.c

pile_statiqueNB.o: pile_statiqueNB.c pile_statiqueNB.h 
	gcc -c pile_statiqueNB.c

elementNB.o: elementNB.c elementNB.h descripteurNB.h
	gcc -c elementNB.c

IndexationRGB : IndexationImageRGB.o elementRGB.o pile_statiqueRGB.o
	gcc -o indexationRGB.out IndexationImageRGB.o elementRGB.o pile_statiqueRGB.o

IndexationRGB.o : IndexationImageRGB.c IndexationImageRGB.h
	gcc -c IndexationRGB.c

pile_statiqueRGB.o :pile_statiqueRGB.c pile_statiqueRGB.h
	gcc -c pile_statiqueRGB.c

elementRGB.o: elementRGB.c elementRGB.h descripteurRGB.h
	gcc -c elementRGB.c

clean :
	rm -rf *.o
