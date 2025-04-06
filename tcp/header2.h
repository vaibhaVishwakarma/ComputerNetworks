#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 41000
#define BUFF 2048


int sockfd = 0;
void die(char* s){

printf("%s\n",s);
exit(EXIT_FAILURE);
}

#define TERMINATE "END"
#define printTable(s1,s2) printf("%-15s -|- %-15s\n",s1,s2)



