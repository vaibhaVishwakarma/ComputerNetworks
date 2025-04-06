#include "header2.h"

int main(int argc , char* argv[]){
	
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	char buffer[BUFF] = "";
	struct sockaddr_in serv_addr, client_addr;
	socklen_t size_serv = sizeof(serv_addr) , size_client = sizeof(size_client);
	memset(&serv_addr , 0 , size_serv);
	memset(&client_addr , 0 , size_client);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd , (struct sockaddr *)&serv_addr , size_serv);
	listen(sockfd , 10);

	while(1){
	
		int connfd = accept(sockfd , (struct sockaddr *)&client_addr , &size_client);
	
		
		int n = read(connfd , buffer , BUFF);
		


		sprintf(buffer , "Hello --|-- %s", inet_ntoa(client_addr.sin_addr));	
		
		n = write(connfd , buffer , BUFF);





		close(connfd);
		
	}

	






	close(sockfd);
	return 0;
}
