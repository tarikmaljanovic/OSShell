#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;

    // create pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // fork child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // child process - redirect standard output to pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); // close unused read end of pipe
        close(fd[1]); // close original write end of pipe
        execlp("ls", "ls", NULL); // execute ls command
        perror("execlp"); // this line only runs if execlp fails
        exit(1);
    } else {
        // parent process - read output of child process from pipe
        char buf[1024];
        ssize_t n;
        close(fd[1]); // close write end of pipe
        while ((n = read(fd[0], buf, sizeof(buf))) > 0) {
            write(STDOUT_FILENO, buf, n); // write output to stdout
        }
        close(fd[0]); // close read end of pipe
        waitpid(pid, NULL, 0); // wait for child process to finish
    }

    return 0;
}