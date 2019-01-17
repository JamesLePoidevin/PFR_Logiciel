#include "Recherche.h"

void Recherche_par_mot_cle()
{

  init_chemain3();
  
  Recherche();
  Recup_textes();

  system("rm *.temp");
}
