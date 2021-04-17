
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 
#include <string.h>
#include <signal.h>

void signalHandler(int sig){
	printf("Recibi segnal %d\n", sig);
}

int main(){
	
	signal(3, signalHandler);

	// from parent to child, parent write, child read
    int pp2c[2];
    // from child to parent, child write, parent read
    int pc2p[2];

	// create pipes
	pipe(pp2c);
    pipe(pc2p);
	
	int sum;

    switch (fork()) {
        // fork failed
        case -1:
            break;
        
		// child
        case 0: 
            // connect pp2c to stdin
            close(pp2c[1]);
            dup2(pp2c[0], STDIN_FILENO);
            close(pp2c[0]);
            // connect pc2p to stdout
            close(pc2p[0]);
            dup2(pc2p[1], STDOUT_FILENO);
            close(pc2p[1]);

            // exec "rev" to reverse lines
            //execlp("rev", "rev", (char*) NULL);
			
			execl("/usr/bin/bc","bc","-l", NULL);
          break;
        
		// parent
        default:
            // close unnecessary pipes
            close(pp2c[0]);
            close(pc2p[1]);
            
			// open pipes as stream
           	// this is need to use fprintf/scanf to write/read from the pipes
            FILE *out = fdopen(pp2c[1], "w");
            FILE *in = fdopen(pc2p[0], "r");

			char word[1024];			// stores string from scanf()
			char function[1024];		// stores function inputted by user
			
			float min;					// lower limit of eval range
			float max; 					// upper limit of eval range
			float eval_point;			// value at which function will be evaluated, sent to bc 			
			float sum;					// stores results sum
			float average;				// results average
				
			int points;					// amount of points to evaluate
			int count;					// keep count of inputs
			
			while(1){
				// reset every loop
				count = 0;
				sum = 0;

				do{
					scanf("%s", word);							// scan user input
					if(count == 0){
						memcpy(function, word, sizeof(word));	// first input is the function
					}
					else if (count == 1){						// inputs 2-4 are the range
						min = atof(word);						// scanf splits the values for us
					}
					else if (count == 2){						 
						max = atof(word);
					}
					else if (count == 3){						
						points = atof(word);
					}
					else{
						break;
					}
					count++;
				} while(count < 4);								// stop reading inputs

				// loop to evaluate on all points
				for(int i = 0; i < points; i++){
					eval_point = min + (i + 1) * (max - min) / points;		// calculate next point to evaluate
					fprintf(out, "x=%f\n", eval_point);						// send eval_point to child in format "x="					
					fprintf(out, "%s\n", function);							// send function to child
					fflush(out);											// clear to use "in" later

					// read child process output
					fscanf(in, "%s", word);
					fflush(in);												// clear to use "out" later
					
					sum += atof(word);										// update sum
				}

				average = sum / points;			// when done calculate average
				
				printf("%f\n", average);		// print program output
			}
			
			// close
			fclose(out);
			fclose(in);			

            // call wait on finished child
        	wait(NULL);
           	break;
    }

    return 0;
}




