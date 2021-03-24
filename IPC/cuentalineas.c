#include <stdio.h>
#include <ctype.h>

int main(){
    char c;
	int count = 0;
	
    while(read(0, &c, 1)) {
    	if (c == '\n'){
        	count = count + 1;
    	}
    }
    if (c != '\n'){
        count = count + 1;
    }
    printf("La entrada tiene %d lineas\n", count);
    return 0;
}