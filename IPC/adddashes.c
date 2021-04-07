
#include <unistd.h>
#include <stdio.h>

int main(){
    int fd[2];
    int pid;
    pipe(fd);
    pid = fork();
    if(pid == 0){ 
		// hijo
		close(fd[1]); 						// 1 input, 0 output
        dup2(fd[0], STDIN_FILENO); 			// pipe (entrada, salida)
        execl("/usr/bin/tr","tr","' '","-", NULL);
    }
    if(pid > 0){ 
		// padre
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execl("/bin/cat","cat", NULL);
    }
    return 0;
}