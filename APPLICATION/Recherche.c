#include "Recherche.h"

void Recherche_par_mot_cle()
{
  init_chemin4();
  Recherche();
  Recup_textes();

  printf("\n\n\t Au revoir.\n\n");
  system("rm *.temp");
}
