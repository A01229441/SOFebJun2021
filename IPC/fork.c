#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int ready = 0;

void signalHandler(int sig){
	int pidHijoTermino = wait(NULL);
	printf("Mi hijo termino %d\n", pidHijoTermino);
	ready = 1;
}

int main(){
	signal(17, signalHandler);
	int pid = fork();
	int pidHijoTermino;
	if (pid == 0){
		// proceso hijo
		printf("Soy el proceso hijo\n");
	}
	else{
		printf("Soy el proceso padre y mi hijo es %d\n", pid);
		// pidHijoTermino = wait(NULL);
		while(1){
			printf("Trabajando\n");
			sleep(1);
			if (ready == 1) break;
		}
		
	}
	
	printf("Terminando\n");
	return 0;
}
