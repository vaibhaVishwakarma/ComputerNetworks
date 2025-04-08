#include <stdio.h>
#include <sys/msg.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAXSIZE 1024

struct msgbuf{
    long mtype;
    char mtext[MAXSIZE];
};

int main(){
    struct msgbuf sendbuf;

    char buffer[MAXSIZE]="Hellowoeld";
    int msgid;
    int msgflag = IPC_CREAT | 0666;
    key_t key1=399;

    msgid=msgget(key1, IPC_CREAT | 0666);

    if (msgid <0) {
        perror("msgget failed");
        return 1;
    }

    strcpy(sendbuf.mtext,buffer);
    sendbuf.mtype = 1; // Set a message type for the queue

    int n = msgsnd(msgid,&sendbuf,MAXSIZE,IPC_NOWAIT);
    printf("%d\n",n);

    sleep(10);
    return 0;

}