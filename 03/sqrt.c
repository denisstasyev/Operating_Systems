#include <stdio.h>
#include <math.h>

//int isInteger(double number)
//{
//  int truncated = (int) number;
//  return (truncated == number);
//}

int main(int argc, char* argv[], char* env[])
{
//---------  
  if (argc < 2) 
  {
    printf("One argument is required\n");
    exit(1);
  }
  if (argc > 2)
  {
    printf("Too much arguments\n");
    exit(1);
  } 
//----------
  double a = atoi(argv[1]);

  if (a < 0)
  {
    printf("Input below zero\n");
    exit(2);
  }

//  if (!isInteger(a)) //  if (a % 10 != 0)
//  {
//    printf("Input is not integer\n");
//    exit(2);
//  }
  
  
  int j;
  for (j = 0; j < strlen(argv[1]); j++)
  {
    if (!isdigit(argv[1][j]))
    {
      printf("Wrong input\n");
      exit(2);
    }
  }

//-----------
  double x0 = 0.1;
  double x1 = 0.5 * (x0 + a/x0);
  while (fabs(x1 - x0) >= 1e-6)
  {
    x0 = x1;
    x1 = 0.5 * (x0 + a/x0);
  }
  printf("Result is %f\n", x0);
  return 0;
}

