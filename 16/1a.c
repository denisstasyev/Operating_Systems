#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    
    int msqid;
    char pathname[] = "09-1a.c";
    key_t  key;
    int i,len;

    struct mymsgbuf
    {
       long mtype;
       char mtext[81];
    } mybuf1, mybuf2;

    /* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }

    /* Send information */
    
//    for (i = 1; i <= 5; i++){
       
       mybuf1.mtype = 1;
       strcpy(mybuf1.mtext, "This is text message");
       len = strlen(mybuf1.mtext)+1;
       
       if (msgsnd(msqid, (struct msgbuf *) &mybuf1, len, 0) < 0){
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
       }



        int maxlen = 81;

        if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf2, maxlen, 2, 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

//        if (mybuf2.mtype == 255) {
//            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
//            exit(0);
//        }

        printf("message type = %ld, info = %s\n", mybuf2.mtype, mybuf2.mtext);
//    }

    return 0;    
}
