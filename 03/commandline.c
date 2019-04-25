#include <stdlib.h>

int main(int argc, char* argv[], char* env[])
{
  int i;
  printf("argv[]\n");
  for (i = 0; i < argc; i++)
  {
    printf("%s ", argv[i]);
  }
  
  printf("\nenv[]\n");
  i = 0;
  while (env[i] != NULL)
  {
    printf("%s ", env[i]);
    i++; 
  }
  printf("\n");

  return 0;
}

