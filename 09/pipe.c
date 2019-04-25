#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
   int     fd[2];
//   ssize_t size, size_w, size_r;

//   if(pipe(fd) < 0){
//     printf("Can\'t open pipe\n");
//     exit(-1);
//   }

   fcntl(fd[1], F_SETFL, O_NONBLOCK);

   int sum = 0;
   while (1)
   {

     if (write(fd[1], "", 1) == -1)
     {
       printf(sum);
       return 0;
     }
     
     sum++;
   }

   /*
   size = write(fd[1], string, 14);

   if(size != 14){
     printf("Can\'t write all string to pipe\n");
     exit(-1);
   }

   size = read(fd[0], resstring, 14);

   if(size < 0){
      printf("Can\'t read string from pipe\n");
      exit(-1);
   }

   printf("%s\n", resstring);
   */

   if(close(fd[0]) < 0){
      printf("Can'\t close reading side of pipe\n"); exit(-1);
   }
   if(close(fd[1]) < 0){
      printf("Can'\t close writing side of  pipe\n"); exit(-1);
   }

   return 0;
}

