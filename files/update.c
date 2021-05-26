#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char *filename = argv[1];
	char *atributo = argv[2];
	char *palabra = argv[3];
	char *nuevo = argv[4];
	FILE *forigen;
	forigen = fopen(filename,"r+");	// modo read write
	STUDENT newstudent;
	while(fread(&newstudent, sizeof(newstudent), 1, forigen)){
		if(strcmp(atributo, "name") == 0){
			if(strcmp(newstudent.name, palabra) == 0){
				printf("Original: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
				fseek(forigen, -sizeof(newstudent), SEEK_CUR);	// regresamos el puntero de lectura 
				strcpy(newstudent.name, nuevo);	// asignamos el nuevo valor
				fwrite(&newstudent, sizeof(newstudent), 1, forigen);	// actualizamos el archivo
				printf("Updated: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
		else if(strcmp(atributo, "lastname") == 0){
			if(strcmp(newstudent.lastname, palabra) == 0){
				printf("Original: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
				fseek(forigen, -sizeof(newstudent), SEEK_CUR);
				strcpy(newstudent.lastname, nuevo);
				fwrite(&newstudent, sizeof(newstudent), 1, forigen);
				printf("Updated: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
		else if(strcmp(atributo, "id") == 0){
			if(newstudent.id == atoi(palabra)){
				printf("Original: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
				fseek(forigen, -sizeof(newstudent), SEEK_CUR);
				newstudent.id = atoi(nuevo);
				fwrite(&newstudent, sizeof(newstudent), 1, forigen);
				printf("Updated: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
		else if(strcmp(atributo, "semestre") == 0){
			if(newstudent.semestre == atoi(palabra)){
				printf("Original: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
				fseek(forigen, -sizeof(newstudent), SEEK_CUR);
				newstudent.semestre = atoi(nuevo);
				fwrite(&newstudent, sizeof(newstudent), 1, forigen);
				printf("Updated: %s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
	}
	fclose(forigen);
}