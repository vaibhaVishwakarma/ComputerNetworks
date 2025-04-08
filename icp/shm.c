#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>


#define KEY 200
#define BUFF 2048


int main(){
    pid_t pid = fork();

    if(pid > 0 ){

        int shmid = shmget(KEY , BUFF , IPC_CREAT | 0666);
        char* addr = shmat(shmid , NULL , 0 );

        char message[BUFF] = "Hello from p1";

        memcpy(addr , message , BUFF);

        sleep(2);
        
        memcpy(message , addr , BUFF);
        
        printf("recieved from child:  %s\n",message);
        
        printf("exiting parent...\n");
        shmctl(shmid , IPC_RMID , NULL);
        wait(NULL);
    }
    else{
        int shmid = shmget(KEY , BUFF , IPC_CREAT | 0666);
        char* addr = shmat(shmid , NULL , 0 );

        char message[BUFF] = "";

        sleep(1);
        memcpy(message , addr , BUFF);

        printf("recieved from parent -> %s\n",message);

        strcpy(message , "hello from p2");

        memcpy(addr , message, BUFF);


    }

    
}
