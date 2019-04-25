#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd[2];
   ssize_t size, size_w, size_r;
   //char     string[] = "H";
   //char  resstring[14];

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
       string[i] = "h";
     }

     char resstring[current];

     size_w = write(fd[1], string, current);
     size_r = read(fd[0], resstring, size_w);
     //char resstr[current];
     printf("%i %i\n", size_w, current);


     //if (read(fd[0], resstring, 10) != 0) printf("final");
     //if (current != size_w){
     //  printf("%i", current - 1);
     //  break;
     //}

     //if ((size_w == size_r)) 
     //{
       //printf("%i", current - 1);
       //return;
     //}
     
     current++;

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

