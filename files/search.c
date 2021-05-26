
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char *filename = argv[1];
	char *atributo = argv[2];
	char *palabra = argv[3];
	FILE *forigen;
	forigen = fopen(filename,"rb");
	STUDENT newstudent;
	while(fread(&newstudent, sizeof(newstudent), 1, forigen)){
		if(strcmp(atributo, "name") == 0){
			if(strcmp(newstudent.name, palabra) == 0){
				printf("%s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
		else if(strcmp(atributo, "lastname") == 0){
			if(strcmp(newstudent.lastname, palabra) == 0){
				printf("%s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
		else if(strcmp(atributo, "id") == 0){
			if(newstudent.id == atoi(palabra)){
				printf("%s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
		else if(strcmp(atributo, "semestre") == 0){
			if(newstudent.semestre == atoi(palabra)){
				printf("%s %s %d %d \n", newstudent.name, newstudent.lastname, newstudent.id, newstudent.semestre);
			}
		}
	}
	fclose(forigen);
}