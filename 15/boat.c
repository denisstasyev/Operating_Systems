#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Max number of passengers in a boat */
#define N 10



int main() {

    /* Getting k - number of trips */
    int k = 3;

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

    while (k) {

        printf("Waiting for loading passengers...\n");
        mybuf.sem_num = 0;
        mybuf.sem_op = -N;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
            printf("Can\'t wait for condition\n");
            exit(-1);
        }

        printf("Tour trip!\n");
        mybuf.sem_num = 1;
        mybuf.sem_op = N;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
            printf("Can\'t wait for condition\n");
            exit(-1);
        }

        printf("Waiting for unloading passengers...\n");
        mybuf.sem_num = 2;
        mybuf.sem_op = -N;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
            printf("Can\'t wait for condition\n");
            exit(-1);
        }

        mybuf.sem_num = 3;
        mybuf.sem_op = N;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
            printf("Can\'t wait for condition\n");
            exit(-1);
        }

        printf("This cycle successfully finished!\n");
        k--;
    }

    return 0;
}