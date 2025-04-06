#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>

#define SERVER "0.0.0.0"
#define BUFF 2048
#define PORT 41001
#define TERMINATE "END"
#define printTable(s1,s2) printf("%-15s -|- %-15s\n",s1,s2)

int sockfd = 0 , n = 0;
char buffer[BUFF] = "";
char manipulate[2*BUFF] = "";
void die(char*s){
	printf("%s\n",s);
	exit(EXIT_FAILURE);
}




