#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#define KEY 200
#define BUFF 2040


struct msgbuf{

    long mtype;
    char mtext[BUFF];

};



int main(){


    pid_t pid = fork();

    if(pid > 0){

        int msgqid = msgget(KEY,IPC_CREAT | 0666);
        
        struct msgbuf message;
        strcpy(message.mtext,"Hello from process 1"); 
        int n_char = msgsnd(msgqid , &message , BUFF , IPC_NOWAIT );
        
        sleep(1);
        
        n_char = msgrcv(msgqid , &message , BUFF , message.mtype , 0);
        
        printf("PARENT | recived : %s\n",message.mtext);
    }
    else{
        int msgqid = msgget(KEY,IPC_CREAT | 0666);
        
        struct msgbuf message;
        
        int n_char = msgrcv(msgqid , &message , BUFF , message.mtype , 0);

        printf("CHILD | revieced %s\n",message.mtext);

        strcpy(message.mtext , "Hello from process 2");
        n_char = msgsnd(msgqid , &message , BUFF , IPC_NOWAIT );

    } 
    
    
    
    
    
    
    
    
    
    
    return 0;
        
        
        
        
        
        
}

