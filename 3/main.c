#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    printf("Something go wrong!\n");
  }
  else if(pid == 0) {
    printf("child\n");
  }
  else {
    printf("parent\n");
  }
  return 0;
}

