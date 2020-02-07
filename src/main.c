#include <stdio.h>

#define MAXLINE 255

int readline(char buffer[MAXLINE]);

int main(){
	char buffer[MAXLINE];
	readline(buffer);
	printf("Hello world : %s", buffer);
}

int readline(char buffer[MAXLINE]){
	int c, i = 0;
	while((c = getchar()) != EOF && c != '\n'){
		buffer[i] = c;
		++i;
	}
	buffer[i] = '\0';
	if(c == EOF){
		return -1;
	}
	else{
		return 0;
	}
}