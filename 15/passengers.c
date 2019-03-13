#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Max number of passengers in a boat */
#define N 10

/* k - number of trips */
#define k 3

int main() {

    int m = N*k;

    /* Semaphores init */

    int semid;
    char pathname[] = "boat.c";
    key_t key;
    struct sembuf mybuf;

    key = ftok(pathname, 0);
    if ((semid = semget(key, 4, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }

    mybuf.sem_num = 3;
    mybuf.sem_op = N;
    mybuf.sem_flg = 0;
    if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
    }

    /* Part with forks */
    int result;
    int i = 0;
    for(i = 0; i < m; i++) {
        result = fork();
        if (result < 0) {
            printf("Can\'t fork child\n");
            exit(-1);
        } else if (result > 0) {

            /* Parent process */

        } else {

            /* Child process */

            mybuf.sem_num = 3;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            printf("One passenger is loaded!\n");
            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            printf("Waiting for finish of tour trip...\n");
            mybuf.sem_num = 1;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            printf("One passenger is unloaded!\n");
            mybuf.sem_num = 2;
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            break;
            //printf("This cycle successfully finished!\n");
        }

        //printf("This finished!\n");
    }

    return 0;
}
