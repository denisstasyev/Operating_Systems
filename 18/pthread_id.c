#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main () {
    pthread_t pthread_id = pthread_self();
    printf("pthread_id: %u\n", pthread_id);
    return 0;
}