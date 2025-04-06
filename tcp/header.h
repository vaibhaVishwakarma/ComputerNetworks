#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<time.h>

#define PORT 4000
#define BUFF 2048
#define TERMINATE "end"

#define printTable(s1,s2) printf("%-15s --- | ---\t %-15s\n",s1,s2)
void die(char * s){
	printf("%s\n",s);
	exit(1);
	}
