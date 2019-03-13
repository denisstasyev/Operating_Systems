//#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int     fd[2];
    ssize_t size, size_w, size_r;

    if(pipe(fd) < 0){
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    int current = 1;
    while(1)
    {
        char string[current];
        int i;
        for (i = 0; i < current; i++)
        {
            string[i] = "";
        }

        char resstring[current];

        size_w = write(fd[1], string, current);
        size_r = read(fd[0], resstring, size_w);
        //char resstr[current];
        printf("%i %i\n", size_w, current);

        current++;

    }

    if(close(fd[0]) < 0){
        printf("Can'\t close reading side of pipe\n"); exit(-1);
    }
    if(close(fd[1]) < 0){
        printf("Can'\t close writing side of  pipe\n"); exit(-1);
    }

    return 0;
}
