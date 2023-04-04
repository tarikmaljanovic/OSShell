#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid;

    pid = fork(); // create a child process

    if (pid < 0) // fork() failed
    {
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0) // child process
    {
      // execlp() function replaces the current process image with a
      //new process image specified by the provided command and arguments. Therefore, any code
      //written after execlp() call in the child process will not be executed.
      
        printf("Child Process: Hello, World!\n");
        execlp("/bin/ls", "ls", NULL); // execute ls command
        printf("This should NOT be printed\n");
    }
    else // parent process
    {
      // the wait() function blocks the parent process until the child process terminates,
      //and returns the exit status of the child process

        printf("Parent Process: Child's PID is %d\n", pid);
        wait(&status); // wait for child process to terminate
        printf("Parent Process: Child Terminated with status %d\n", WEXITSTATUS(status));

        //the WEXITSTATUS() macro is used to extract the exit status from the status variable
       //returned by wait().
    }

    return 0;
}