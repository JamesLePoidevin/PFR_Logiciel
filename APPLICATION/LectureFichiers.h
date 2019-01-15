#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pile_statique.h"

//type_des FaireDescripteur(char adresse[],int reference);
int NombreDeMot(FILE *f);
int read_word(FILE *f,type_mot tab[]);
int NomDesFichiers(char *CHEMIN,char *adresseArrive);
