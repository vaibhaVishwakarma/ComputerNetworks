#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>



int main(int argc , char* argv[]){

    struct addrinfo hints;
    struct addrinfo *result , *rp;
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    int success = getaddrinfo(argv[1] , NULL , &hints , &result);

    for(rp = result ; rp != NULL ; rp = rp->ai_next){
        struct sockaddr_in *current = (struct sockaddr_in *) rp->ai_addr;
        printf("ip-> %s:%d\n",inet_ntoa((current->sin_addr)) , ntohs(current->sin_port)); 
    }
    
    return 0;
}


// #include <fcntl.h>
//#include <string.h>
  // char buffer[1024] = "ping -c 4 www.youtube.com";
    // printf("\n");
    //     FILE *fp = popen(buffer,"r");
    //     if(!fp){
    //         perror("popen");
    //         return 1;
    //     }
    //     char output[1024-10]={0};
    //     fread(output,1,sizeof(output)-1,fp);
    //     pclose(fp);



    //     strcpy(buffer,output);
    //     printf("%s\n",buffer);