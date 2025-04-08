#include <stdio.h>
#include <sys/msg.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define MAXSIZE 1024

struct msgbuf {
    long mtype;
    char mtext[MAXSIZE];
};

int main() {
    struct msgbuf recvBuff;
    size_t buflen;

    char buffer[MAXSIZE];
    int msgid;

    key_t key1 = 399; 

    msgid = msgget(key1, IPC_CREAT | 0666);
    recvBuff.mtype =1 ;

    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    if (msgrcv(msgid, &recvBuff, MAXSIZE, 1, 0) == -1) {
        perror("msgrcv failed");
        return 1;
    }

    printf("Received message: %s", recvBuff.mtext);

    return 0;
}