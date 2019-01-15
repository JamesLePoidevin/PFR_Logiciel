#include "TriFichier.h"

void enleverPointEtVirgule(char* mot);
void enleverAppostrophe(char* mot);
void enleverParenthese(char * mot);
int misDeMotDansTableau(char* mot, int indiceTabMot, type_mot tab[]);
int enleverBalise2(FILE * ptr_fic,type_mot tab[]);
void IndexationComplet();
void ecritureDescripteur(type_des descripteur);
void ecritureMotCles(type_des descripteur);
char* lirechemin();
type_des FaireDescripteur(FILE * ptr_fic,int reference);
int Blacklist(char **tab);
