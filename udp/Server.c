#include "header.h"

int main(int argc , char * argv[]){

	sockfd = socket(AF_INET , SOCK_DGRAM , 0);
	
	struct sockaddr_in serv_addr , client_addr;
	socklen_t size_serv = sizeof(serv_addr) , size_client = sizeof(client_addr);
	memset(&serv_addr , 0 , size_serv);
	memset(&client_addr , 0 ,size_client);


	serv_addr.sin_family  = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd , (struct sockaddr *) &serv_addr , size_serv );

	while(1){
	
	recvfrom(sockfd , buffer , BUFF ,0 , (struct sockaddr *)&client_addr , &size_client);
	
	sprintf(manipulate, "%-500s -|- %s",buffer , inet_ntoa(client_addr.sin_addr));
	
	sendto(sockfd , manipulate, BUFF , 0 , (struct sockaddr *)&client_addr , size_client);

	
	}


close(sockfd);
return 0;
}
