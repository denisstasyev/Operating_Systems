#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  uid_t uid = getuid();
  gid_t gid = getgid();
  printf("uid = %d; gid = %d\n", uid, gid);
  return 0;
}

