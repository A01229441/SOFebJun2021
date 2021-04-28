/******** mish.c **********/
// gcc -o mish mish.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>	// for wait(NULL)
 
#define MAX_LINE 80
#define MAX_NUM_ARGS 10

size_t string_parser(char *input, char *word_array[]) {
	size_t n = 0;
	while (*input) {
		while (isspace((unsigned char)*input))
		++input;
		if (*input) {
			word_array[n++] = (char *)input;
			while (*input && !isspace((unsigned char)*input))
			++input;
			*(input) = '\0';
			++input;
		}
	}
	word_array[n] = NULL;
	return n;
}
 
int main(void) {
  char *args[MAX_NUM_ARGS + 1]; /* command line (of 80) has max of 5 arguments */
  char line[MAX_LINE + 1];
  int should_run = 1;
 
  int i;
 
  while (should_run) {
    printf("mish> ");
    fgets(line,MAX_LINE,stdin);
    line[strcspn(line, "\n")] = '\0';
    // Separamos la línea en palabras separadas por espacio
    // y las guardamos en args
    i = string_parser(line,args); // i contiene el número de argumentos
    //printf("%d, %s %s\n", i, args[1],line); // Es solo para pruebas borrar cuando esté listo
    
    /**
    (1) Crear un proceso hijo
    (2) El hijo debe ejecutar execvp para ejecutar al comando tecleado
    (3) Si el programa no existe debe imprimir programa no encontrado
    (4) El proceso padre debe esperar a que el hijo termine, checar función wait
    (5) Debe ejecutar comandos como ls , ps
    (6) Cuando se teclee exit deberá terminar
    **/
    
	if(!strcmp(line,"exit")){		// exit para terminar
		exit(0);					// salir
	}
	  
	switch (fork()){
		// fork failed
		case -1:
			break;
		
		// child
		case 0:
			//int execvp(const char *file, char *const argv[]);		// template de execvp()
			//if(execvp(line, args) == -1){							// if is redundant, not needed
				//printf("Program not found\n");
				//exit(0);
			//}
			execvp(line, args);					// execute program
			printf("Program not found\n");		// we will only get here if execvp returns -1 (does not exist)
			exit(0);							// exit unexistent executed program 
			break;
			
		// parent
		default:
			wait(NULL);				// esperar al hijo
			break;
	}

    fflush(stdout);
    fflush(stdin);
    line[0] = '\0';
  }
 
  return 0;
}
