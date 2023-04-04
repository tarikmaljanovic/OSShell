#define _GNU_SOURCE
#define __USE_GNU
#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>


int child_func(void *arg)
{
    char *envp[] = {"PATH=/bin", NULL};

    printf("Child Process: Hello, World!\n");
    execle("/bin/ls", "ls", "-l", NULL, envp); // execute ls command with modified environment
    return 0;
}

int main()
{
    void *child_stack = malloc(4096);

    if (child_stack == NULL) // check if allocation was successful
    {
        fprintf(stderr, "Failed to allocate stack\n");
        exit(-1);
    }

    int pid = clone(child_func, child_stack + 4096, SIGCHLD, NULL); // create a child process using clone()
//A trap signal that indicates a process started by the current process has terminated.
//This allows the process to “reap” the zombie process and evaluate the exit status and make
// decisions on why the process terminated. This is how the shell knows to wait for a command to 
//terminate before prompting for another command.

    if (pid < 0) // clone() failed
    {
        fprintf(stderr, "Clone Failed\n");
        exit(-1);
    }

    free(child_stack);

    return 0;
}