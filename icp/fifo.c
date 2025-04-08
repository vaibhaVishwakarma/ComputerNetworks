#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>

#define FIFO "fifo1"
#define BUFF 2048

int main(){
    pid_t pid = fork();
    
    if(pid > 0){

        open(FIFO , O_CREAT | 0666 , 0666  );
        
        int wfd = open(FIFO,O_WRONLY);
        int rfd = open(FIFO,O_RDONLY);
        
        char message[BUFF] = "Hello from p1";
        write(wfd , message , BUFF  );
        printf("PARENT | snd | %s\n",message);
        
        sleep(3);
        
        read(rfd , message , BUFF);
        
        printf("PARENT | rcv | %s\n",message);
        
        close(wfd);
        close(rfd);
        
        wait(NULL);

    }
    else{
        open(FIFO , O_CREAT | 0666 , 0666  );
        
        
        int wfd = open(FIFO,O_WRONLY);
        int rfd = open(FIFO,O_RDONLY);

        char message[BUFF] = "";
        sleep(2);
        read(rfd , message , BUFF);
        
        printf("CHILD | rcv | %s\n",message); 
        
        strcpy(message , "Hello from p2");
        printf("CHILD | snd | %s\n",message); 
        
        write(wfd , message , BUFF  );

        sleep(3);
        close(wfd);
        close(rfd);


    }

}