
// Practica 11
// Luis Alfredo Aceves Astengo A01229441

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argnum, char **argv){
    char *original = argv[1];	// nombre de archivo original
    char *destino = argv[2];	// nombre de archivo destino
    
	FILE *foriginal, *fdestino;
    foriginal = fopen(original,"rb");	// abrir original en modo read
    fdestino = fopen(destino,"wb");		// abrir destino en modo write
	
	char buffer;	// buffer de 1 char para ir leyendo el original
	int size = 0;	// tamaño en bytes de la linea siendo leida
	char *linea;	// puntero al arreglo de chars de la linea leida
    
	while(fread(&buffer, sizeof(char), 1, foriginal) ){	// leemos el original, guardando en buffer un char a la vez 
		size += 1;	// cada char leido aumenta en 1 el tamaño de la linea
		if(buffer == '\n'){	// llegamos al final de linea
            fseek(foriginal, -size, SEEK_CUR);	// regresamos el puntero de lectura size chars atras
												// es decir, al inicio del renglon
            linea = (char *) calloc(size, sizeof(char));	// linea[size];
			fread(linea, sizeof(char), size, foriginal);	// leemos el renglon y guardanamos en linea
			
			if(strstr(linea, "hola") == NULL){	// si "hola" esta en linea
				fwrite(linea, sizeof(char), size, fdestino);	// escribimos la linea en destino
            }
			else {
            	// no escribe la linea en destino
        	}
			size = 0;	// reseteamos size a 0 para leer el siguiente renglon
   		}
	}
	
	// cerramos los archivos
	fclose(foriginal);
    fclose(fdestino);

    return 0;
}