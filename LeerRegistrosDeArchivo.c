/*
 * LeerRegistrosDeArchivo.c
 *
 *  Created on: 19 ago. 2018
 *      Author: utnso
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char id[5];
	char nom[31];
	char dar[6];
	char grua[4];
	char cantCont[4];
	char fec[9];
	char cte[4];
	char lugar[27];
} RReadBuque;

typedef struct {
	int id;
	char nom[31];
	char dar[6];
	unsigned short grua;
	unsigned short cantCont;
	unsigned long fec;
	unsigned short cte;
	char lugar[27];
} RBuque;

int leerArchivo(FILE *a,RReadBuque *buff);

void printRecord(const RBuque* reg);

void castRecord(RReadBuque* reg2Read, RBuque* reg);

int main(){
	RReadBuque regToRead;
	RBuque reg;
	FILE* fp;
	int fin;
	if ((fp=fopen("/home/utnso/ejemplosBasicosC/BasicoArchivos/buques.txt","r")) == NULL){
		printf("Error opening file!");
		exit(1);
	}
	fin=leerArchivo(fp, &regToRead);
	while(!fin){
		castRecord(&regToRead, &reg);
		printRecord(&reg);
		fin=leerArchivo(fp, &regToRead);
	}
	fclose(fp);
	return 0;
}

int leerArchivo(FILE *a,RReadBuque *buff){
	if(feof(a)){
		return 1;
	} else {
		fgets(buff->id, sizeof(buff->id), a);
		fgets(buff->nom, sizeof(buff->nom), a);
		fgets(buff->dar, sizeof(buff->dar), a);
		fgets(buff->grua, sizeof(buff->grua), a);
		fgets(buff->cantCont, sizeof(buff->cantCont), a);
		fgets(buff->fec, sizeof(buff->fec), a);
		fgets(buff->cte, sizeof(buff->cte), a);
		fgets(buff->lugar, sizeof(buff->lugar), a);
		return 0;
	}
}

void printRecord(const RBuque* reg) {
	printf("Id de buque %d\n", reg->id);
	printf("Nombre %s\n", reg->nom);
	printf("Darsena %s\n", reg->dar);
	printf("Nro grua %d\n", reg->grua);
	printf("Cant. de containters %d\n", reg->cantCont);
	printf("Fecha %li\n", reg->fec);
	printf("Constante de flotacion %d\n", reg->cte);
	printf("Lugar %s\n", reg->lugar);
}

void castRecord(RReadBuque* reg2Read, RBuque* reg) {
	reg->id=atoi(reg2Read->id);
	reg->grua=(unsigned short)atoi(reg2Read->grua);
	reg->cantCont=(unsigned short)atoi(reg2Read->cantCont);
	reg->fec=(unsigned long)atol(reg2Read->fec);
	reg->cte=(unsigned short)atoi(reg2Read->cte);
	for(int i=0;i<=30;i++){
		reg->nom[i]=reg2Read->nom[i];
	}
	for(int i=0;i<=24;i++){
		reg->lugar[i]=reg2Read->lugar[i];
	}
	for(int i=0;i<=5;i++){
		reg->dar[i]=reg2Read->dar[i];
	}
}
