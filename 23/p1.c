// Program 1
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int a = 0;

void (*p)(int);

void my_handler(int nsig){
   a = 1;
}

int main(void){
    p = signal(SIGUSR1, my_handler);

    pid_t pid_p1 = getpid();
    printf("My pid: %d\nEnter pid where to send:\n", pid_p1);

    pid_t pid_p2;
    scanf("%d", &pid_p2);

    int number;
    printf("Enter number to send:\n");
    scanf("%i", &number);

    int i;
    for (i = 0; i < (sizeof(int) * 8); i++) {
        if ((number & (1 << i)) > 0) {
            kill(pid_p2, SIGUSR1);
            //printf("1");
            while (a == 0);
            a = 0;
        }
        if ((number & (1 << i)) == 0) {
            kill(pid_p2, SIGUSR2);
            //printf("0");
            while (a == 0);
            a = 0;
        }
    }
    printf("Sent!\n");
    return 0;
}

