#include "Mot.h"


type_mot setMot(type_mot A,char *mot){
	strcpy(A.mot,mot);
	return A;	
}

type_mot setOccurence(type_mot A,int occurence){
	A.occurence = occurence;
	return A;	
}

type_mot setMotetOccurence(type_mot A,int occurence,char *mot){
	A=setMot(A,mot);
	A=setOccurence(A,occurence);
	return A;
}

int getOccurence(type_mot A){
	return A.occurence;
}


/*
int main(int argc, char *argv[]){
	type_mot a;
	char *testmot = "hello0000000000";
	a=setMot(a,testmot);
	char *test =toString(a);
	printf("%s\n", test);
	return 0;
}*/
