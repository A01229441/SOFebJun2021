
// Equipo:
// Luis Alfredo Aceves Astengo A01229441
// Eduardo Garcia Olmos A01351095
// José Luis Jiménez Arévalo A01633245

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argvnum, char **argv){
	char *path = argv[1];
	char *path2 = argv[2];
	struct stat sb;
	if(stat(path, &sb) == -1){
		printf("Error: el primer argumento no existe.\n");
		return -1;
	}
	if(S_ISDIR(sb.st_mode)){
		printf("El primer argumento es un directorio. Se espera un archivo.\n");
		return -1;
	}
	
	// argumento 1 si es un archivo
	if(S_ISREG(sb.st_mode)){
		// segundo argumento no existe, vamos a crearlo
		if(stat(path2, &sb) == -1){
			link(path, path2);		// creamos el nuevo
			unlink(path);			// borramos el viejo
		}
		// segundo argumento es un directorio, vamos a mover arch1 ahi
		else if(S_ISDIR(sb.st_mode)){
			// se asume que path2 termina en "/"
			link(path, strcat(path2,path));		// movemos el archivo al nuevo path
			unlink(path);			// borramos el viejo
		}
		// segundo argumento es un archivo, vamos a mandar un mensaje de error
		else if(S_ISREG(sb.st_mode)){
			printf("Error: %s ya existe.\n", path2);
		}
	}
		
	return 1;
}








