#include <stdio.h>
#include <stdlib.h>

int main(int numarg, char **argv) {

	int sum = 0;
	
	if(numarg == 1){
		printf("Error. No se recibieron argumentos.\n");
	}
	else{
		for(int i = 1; i < numarg; i++){
		sum += atoi(argv[i]);
   		}
		printf("%d\n", sum);
	}
    
    return 0;
}