
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int done = 0;

void signalHandler(int sig){
	printf("Recibi segnal %d\n", sig);
	done = 1;
}

int main(){
	signal(2, signalHandler);
	while(1){
		printf("Trabajando\n");
		sleep(1);
		if(done){
			break;
		}
	}
	printf("Ya voy a terminar \n");
	return 0;
}