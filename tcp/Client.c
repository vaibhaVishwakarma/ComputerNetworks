#include "header.h"

int main(int argc , char* argv[]){
	
	if(argc == 1) die("usage argv [IP] [MSG]");

	int sockfd = 0 , n = 0;
	
	if(0>(sockfd = socket(AF_INET , SOCK_STREAM , 0)))
		die("socket()");
	
	
	
	struct sockaddr_in serv_addr;
	memset(&serv_addr , 0 , sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_aton(argv[1] , &serv_addr.sin_addr);
	//serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	if( 0 > connect(sockfd ,(struct sockaddr *) &serv_addr , sizeof(serv_addr)))
		die("connect()");

	char buffer[BUFF];
	strcpy(buffer , argv[2]);

	n = write(sockfd , buffer , BUFF);
	if(0>n) die("write()");

	printTable("[sent]",buffer);

	n = read(sockfd , buffer , BUFF);
	if(0>n) die("read()");

	printTable("[rcv]",buffer);



	


			

	


	
	

}
