#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    /* Getting N - number of cycles */

    int n = 1;
    int N;

    printf("Enter number of cycles (>= 2): ");
    scanf("%d", &N);
    while (N < 2){
        printf("Please enter number only >= 2: ");
        scanf("%d", &N);
    }

    /* Semaphore init */

    int semid;
    char pathname[] = "pipe-sem.c";
    key_t key;
    struct sembuf mybuf;

    key = ftok(pathname, 0);
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }

    /* Pipe init */

    int fd[2], result;
    size_t size;
    char resstring[15];

    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }
    result = fork();

    /* Main part */

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {

        /* Parent process */

        printf("\nParent started!\n");

        size = write(fd[1], "Hello, child!_", 15);
        if (size != 15) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }
        printf("Parent wrote!\n");

        mybuf.sem_num = 0;
        mybuf.sem_op = 1;
        mybuf.sem_flg = 0;
        if (semop(semid, &mybuf, 1) < 0) {
            printf("Can\'t wait for condition\n");
            exit(-1);
        }

        for (n = 1; n <= N; n++) {

            /* After child */

            mybuf.sem_num = 0;
            mybuf.sem_op = -2;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            size = read(fd[0], resstring, 15);
            if (size < 0) {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }
            printf("Parent read: %s\n", resstring);

            printf("Parent finished %d cycles!\n", n);

            if (n == N) {
                if (close(fd[0]) < 0) {
                    printf("parent: Can\'t close reading side of pipe\n");
                    exit(-1);
                }
                if (close(fd[1]) < 0) {
                    printf("parent: Can\'t close writing side of pipe\n");
                    exit(-1);
                }
                printf("Successfully finished!\n");
                return 0;
            }

            printf("\nParent starts!\n");

            size = write(fd[1], "Hello, child!_", 15);
            if (size != 15) {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }
            printf("Parent wrote!\n");

            mybuf.sem_num = 0;
            mybuf.sem_op = 3;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            mybuf.sem_num = 0;
            mybuf.sem_op = 0;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            mybuf.sem_num = 0;
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
        }
    } else {

        /* Child process */

        int m = 1;

        for (m = 1; m <= N; m++) {
            printf("\nChild started!\n");

            mybuf.sem_num = 0;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            size = read(fd[0], resstring, 15);
            if (size < 0) {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }
            printf("Child read: %s\n", resstring);

            size = write(fd[1], "Hello, parent!", 15);
            if (size != 15) {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }
            printf("Child wrote!\n");

            printf("Child finished!\n\n");

            mybuf.sem_num = 0;
            mybuf.sem_op = 2;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }

            /* Back to parent and come back */

            if (n == N) {
                if (close(fd[0]) < 0) {
                    printf("parent: Can\'t close reading side of pipe\n");
                    exit(-1);
                }
                if (close(fd[1]) < 0) {
                    printf("parent: Can\'t close writing side of pipe\n");
                    exit(-1);
                }
                printf("Successfully finished!\n");
                return 0;
            }

            mybuf.sem_num = 0;
            mybuf.sem_op = -3;
            mybuf.sem_flg = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
        }
    }

    return 0;
}