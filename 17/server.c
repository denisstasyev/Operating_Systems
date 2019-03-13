#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 2


int main(void)
{

    int msqid;
    char pathname[]="server.c";
    key_t  key;
    int i,len;

    struct mymsgbuf
    {
        long mtype;
        struct ab {
            int pid;
            float num;
        } a;
    } mybuf, mybufsend;

    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    while (1) {

        int maxlen = sizeof(mybuf.a);

        if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, -2, 0)) < 0){////////
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mtype == 1) { //HERE IS ERROR
            mybufsend.mtype = mybuf.a.pid;
            mybufsend.a.pid = mybuf.a.pid;
            mybufsend.a.num = (mybuf.a.num) * (mybuf.a.num);

            len = sizeof(mybufsend.a);

            if (msgsnd(msqid, (struct msgbuf *) &mybufsend, len, 0) < 0){
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }

//            printf("message type = %ld, info: char = %c, float = %.02f\n", mybuf.mtype, mybuf.a.c, mybuf.a.f);
        }

        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(0);
        }

    }
}
