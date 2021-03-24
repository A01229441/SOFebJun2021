#include <stdio.h>
#include <ctype.h>
// 0 = stdin
// 1 = stdout
int main(){
	char minC;
	char mayC;
	while(read(0,&minC,1)){
		mayC = toupper(minC);
		write(1,&mayC,1);
	}
	return 0;
}