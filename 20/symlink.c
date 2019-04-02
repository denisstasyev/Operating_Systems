#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// В папке запустить: mkdir tmp

int main(){
    int fd = open("./tmp/a", O_CREAT, 0666);
    if (fd < 0) {
        printf("Cannon create file ./tmp/a. Please create folder ./tmp.\n");
        exit(1);
    }
    close(fd);


    int i = 0;
    char file_address[80];
    char prev_file_address[80];
    sprintf(file_address, "./tmp/file%d", i);

    int error = symlink("a", file_address);
    if (error < 0) {
        printf("Cannon create symlink %d.\n", i);
        exit(1);
    }

    fd = open(file_address, O_RDONLY);
    while (fd != -1) {
        close(fd);
        i++;

        sprintf(prev_file_address, "./file%d", i - 1);
        sprintf(file_address, "./tmp/file%d", i);

        int error = symlink(prev_file_address, file_address);
        if (error < 0){
            printf("Cannon create symlink %d.\n", i);
            exit(1);
        }

        fd = open(file_address, O_RDONLY);
    }

    printf("Result: %d.\n", i);

    return 0;
}