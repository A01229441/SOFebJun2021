
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 

int main(){
	
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

			
			
			int suma = 0;
			
			char function[1024];
			char range[1024];
			char result[1024];
			
			float min, max, eval_point; 
			int points;
			
			fgets(function, 1024, stdin);
			fgets(range, 1024, stdin);
			
			min = (float) atoi(&range[0]);
			max = (float) atoi(&range[2]);
			points = atoi(&range[4]);
			
			eval_point = 1;
			
			fprintf(out, "x=%f\n", eval_point);
			fprintf(out, "%s", function);
            fclose(out);
            // read child process output
            while (fscanf(in, "%s", result) != EOF) {
                printf("resultad : %s\n", result);
            }
            fclose(in);

			out = fdopen(pp2c[1], "w");
            in = fdopen(pc2p[0], "r");
			
			printf("part2");
			eval_point = 2;
			fprintf(out, "x=%f\n", eval_point);
			fprintf(out, "%s", function);
            fclose(out);
            // read child process output
            while (fscanf(in, "%s", result) != EOF) {
                printf("resultad : %s\n", result);
            }
            fclose(in);
			
			
			//printf("%f\n", min);
			//printf("%f\n", max);
			//printf("%d\n", points);
			
			/*for(int i = 0 ; i < points; i++){
				
				eval_point = min + (points + 1) * (max-min) / points;
				
				out = fdopen(pp2c[1], "w");
				fprintf(out, "x=%f\n", eval_point);
				fprintf(out, "%s", function);
				fclose(out);
				
				in = fdopen(pc2p[0], "r");
				fscanf(in, "%s", result);
				fclose(in);
				printf("%s", result);
			}*/
			
			//for(int i = 0 ; i < points; i++){
				//printf("hola");
			//}
			
			//eval_point = min + (points + 1) * (max-min) / points;
			
			/*eval_point = 8;
				
				fprintf(out, "x=%f\n", eval_point);
				fprintf(out, "%s", function);
				fclose(out);
				
				fscanf(in, "%s", result);
				fclose(in);
				printf("result = %s", result);
			
			wait(NULL);*/
			/*
			//eval_point = 2;
				out = fdopen(pp2c[1], "w");
				//fopen(out,"w");
				fprintf(out, "x=%f\n", eval_point);
				fprintf(out, "%s+1", function);
				fclose(out);
				
				in = fdopen(pc2p[0], "r");
				fscanf(in, "%s", result);
				//fopen(in,"w");
				fscanf(in, "%s", result);
				//printf("closing\n");
				//fclose(in);
				printf("%s", result);
			
			*/
			
			//char word[1024];
            // redirect input to child process
            /*while (scanf("%s", word) != EOF) {
                fprintf(out, "%s\n", word);
            }*/
            //fclose(out);
            // read child process output
            //while (fscanf(in, "%s", word) != EOF) {
                //printf("%s\n", word);
            //}
            

            // call wait on finished child
            wait(NULL);
            break;
    }

    return 0;
}




