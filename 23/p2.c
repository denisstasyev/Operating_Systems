// Program 2
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

pid_t pid_p1;

int i = 0;
int number = 0;

void (*p)(int);

void my_handler(int nsig){
    if (nsig == SIGUSR1) {
        number |= (1 << i); 
        kill(pid_p1, SIGUSR1);
        i += 1;
        //printf("1");
    }
    if (nsig == SIGUSR2) {
        number |= (0 << i); 
        kill(pid_p1, SIGUSR1);
        i += 1;
        //printf("0");
    }

}

int main(void){
    pid_t pid_p2 = getpid();
    printf("My pid: %d\nEnter pid from where to recieve:\n", pid_p2);

    scanf("%d", &pid_p1);

    p = signal(SIGUSR1, my_handler);
    p = signal(SIGUSR2, my_handler);
    while(i < (sizeof(int) * 8));
    printf("Recieved number: %i\n", number);
    return 0;
}

