#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

    int msqid;
    char pathname[] = "server.c";
    key_t key;
    int i, maxlen, mypid;
    float mynum;

    struct mymsgbuf {
        long mtype;
        struct ab {
            int pid;
            float num;
        } a;
    } mybuf, mybufsend;

    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0)) < 0) { //!!!!!!
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    mypid = getpid();

    printf("Enter number: ");
    scanf("%f", &mynum);

    mybufsend.mtype = 1;
    mybufsend.a.pid = mypid;
    mybufsend.a.num = mynum;

    maxlen = sizeof(mybufsend.a);

    if (msgsnd(msqid, (struct msgbuf *) &mybufsend, maxlen, 0) < 0) {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    if ((maxlen = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, mypid, 0)) < 0) {///////////
        printf("Can\'t receive message from queue\n");
        exit(-1);
    }

    printf("Result: %f\n", mybuf.a.num);
//    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

    return 0;
}