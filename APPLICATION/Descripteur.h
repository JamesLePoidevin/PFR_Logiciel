#include "CommandeSysteme.h"
#include "Mot.h"


//structure descripteur pour les texte
typedef struct type_des
{
	int ref;
	type_mot *tab;
}type_des;


int recuperer_Valuer_Descripteur();
type_des init_des();
type_des CreerDescriteur(int ref,type_mot *tab);
void Trier_tab_mot(type_mot tab[],type_mot tab2[], int length);

//LILA
int test_int();