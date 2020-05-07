#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>

int main()
{
  int pid = fork();
  if (pid) {
    printf("ID of first child: %d\n",pid);
    wait(NULL);

    printf("Wait!\n");
    pid = fork();
    if(pid) {
      printf("ID of second child: %d\n",pid);
      wait(NULL);

      printf("Wait!\n");
    }

    else if (pid == 0) {
      printf("The second child process is trying to run:\n");
      char *arg[]={"/bin/free","-h",NULL};
      execvp(arg[0],arg);
    }

    else printf("Cannot fork second child\n");
  }

  else if (pid == 0) {
    printf("The first child process is trying to run:\n");
    char *arg[]={"/bin/ps","-ef",NULL};
    execvp(arg[0],arg);
  }

  else printf("Cannot fork\n");
  return 0;
}