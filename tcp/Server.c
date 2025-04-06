#include "header.h"


int main(int argc , char* argv[]){

	char buffer[BUFF] ;
	int sockfd = 0, connfd = 0 , n = 0 ;

	struct sockaddr_in serv_addr;
	memset(&serv_addr , 0 , sizeof(serv_addr));
	
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if(0>sockfd) die("socket()");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);

	bind(sockfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr));

	listen(sockfd , 10);

	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
	memset(&client_addr , 0 , sizeof(client_addr));
	
	while(1){
		
		connfd = accept(sockfd , (struct sockaddr *) &client_addr , \
			      			&length	 );
		n = read(connfd , buffer , BUFF);
		if(0>n) die("read()");
		if(strcmp(buffer,TERMINATE) == 0) die("terminating... \n");

		printTable("[rcv]",buffer);

		n = write(connfd , buffer , BUFF);
		if(0>n) die("write()");
		

		printf("IP - > %s\n\n", inet_ntoa(client_addr.sin_addr));

		printTable("[snd]",buffer);

		close(connfd);
		sleep(1);

	
	}
	

	close(sockfd);
}

