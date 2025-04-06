#include "header2.h"

int main(int argc , char* argv[]){
	
	int sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if(0>sockfd) die("socket()");

	char buffer[BUFF] = "";
	
	struct sockaddr_in serv_addr;
	socklen_t size_serv = sizeof(serv_addr);
	memset(&serv_addr, 0 , size_serv );

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_aton(argv[1] , &serv_addr.sin_addr);

	connect(sockfd , (struct sockaddr *) &serv_addr , size_serv);
	

	sprintf(buffer , "%s" , argv[2] );
	int n = write(sockfd , buffer , BUFF);
	
	printTable("sent" , buffer);

	n = read(sockfd , buffer , BUFF);

	printTable("read", buffer);
	
	








	close(sockfd);
	return 0;
}
