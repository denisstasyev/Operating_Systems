#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int msqid;
    char pathname[] = "server.c";
    key_t key;
    int i, len, mypid;
    float mynum;

    struct mymsgbuf {
        long mtype;
        struct ab {
            int pid;
            float num;
        } a;
    } mybufsend;

    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0)) < 0) { //!!!!!!
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    mybufsend.mtype = 2;
    mybufsend.a.pid = 2;
    mybufsend.a.num = 0;

    len = sizeof(mybufsend.a);

    if (msgsnd(msqid, (struct msgbuf *) &mybufsend, len, 0) < 0) {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    return 0;
}