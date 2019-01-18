#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct type_mot
{
	char *mot;
	int occurence;
}type_mot;


type_mot init_mot();
//setter
type_mot setMot(type_mot A,char *mot);
type_mot setOccurence(type_mot A,int occurence);
type_mot setMotetOccurence(type_mot A,int occurence,char *mot);

//getter
int getOccurence(type_mot A);
char* getMot(type_mot A);


//fonction
int read_word(FILE *f,type_mot tab[]);