#include "header.h"

int main(int arc , char* argv[]){
	
	sockfd = socket(AF_INET , SOCK_DGRAM , 0);

	
	struct sockaddr_in serv_addr;
	socklen_t size_serv = sizeof(serv_addr);
	memset(&serv_addr , 0, size_serv );


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_aton(SERVER , &serv_addr.sin_addr);
	

	sprintf(buffer , "%s" , argv[1]);


	n = sendto(sockfd , buffer , BUFF , 0 , (struct sockaddr *)&serv_addr , size_serv);
	printTable("sent",buffer);


	n = recvfrom(sockfd , buffer , BUFF, 0 , (struct sockaddr *)&serv_addr,&size_serv);
	printTable("recv", buffer);
	
	
	close(sockfd);
	return 0;
}
