#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <sys/wait.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGUMENTS 10

int main() {
  char input[MAX_COMMAND_LENGTH]; //User input is stored here
  char *arguments[MAX_NUM_ARGUMENTS];
  char hostName[100]; //Host name is stored here
  char *login = getlogin(); //Login name is stored and called here
  gethostname(hostName, 100); //Function for getting the host name of the machine
  int fd[2];
  pipe(fd);

  
  while (1) {
    printf(RED"%s@%s\033[0m"BOLDGREEN":~$ \033[0m", hostName, login);
    fgets(input, MAX_COMMAND_LENGTH, stdin);
    input[strlen(input) - 1] = '\0';  // Remove newline character

    if(strcmp(input, "") == 0) {
      continue;
    }
    // Tokenize the command string by spaces
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < MAX_NUM_ARGUMENTS) {
      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    arguments[i] = NULL;  // Set the last argument to NULL for execvp

    if(strcmp(arguments[0], "quit") == 0) {
      printf(BOLDBLUE"Goodbye ( ´ ▽ ` )ﾉ\033[0m\n");
      break;
    } else if(strcmp(arguments[0], "name") == 0) {
      printf("Shell Name: "BOLDBLUE"Shelly v1.0.0\033[0m\n");
      continue;
    } else if(strcmp(arguments[0], "manuel") == 0) {
      printf(BOLDBLUE"Shell Man Page\033[0m\n");
      printf("\n");
      printf("Shell Name: "BOLDBLUE"Shelly v1.0.0\033[0m\n");
      printf("\n");
      printf(BOLDGREEN"**************************\033[0m\n");
      printf(RED"machineName@hostName\033[0m"BOLDGREEN":~$ \033[0m"BOLDWHITE"<Command Name> \033[0m"BOLDWHITE"<Flag>\033[0m\n");
      printf("\n");

      printf(BOLDBLUE"grep ~File pattern searcher \033[0m\n");
      printf(BOLDBLUE"-v ~Selected lines are those not matching any of the specified patterns.\033[0m\n");
      printf("\n");

      printf(BOLDBLUE"wc ~Word count \033[0m\n");
      printf(BOLDBLUE"-l ~Include number of lines\033[0m\n");
      printf("\n");

      printf(BOLDBLUE"df ~Display free disk space \033[0m\n");
      printf("\n");

      printf(BOLDBLUE"cmatrix ~Shows a scrolling 'Matrix' like screen in Linux\033[0m\n");
      printf("\n");

      printf(BOLDBLUE"name ~Get shell name and version\033[0m\n");
      printf("\n");

      printf(BOLDBLUE"quit ~Exit the shell\033[0m\n");
      printf("\n");

      printf(BOLDBLUE"clear ~Clear the screen\033[0m\n");
      printf("\n");

      printf(BOLDBLUE"man ~Get manual page of the shell\033[0m\n");
      printf(BOLDGREEN"**************************\033[0m\n");
    } else {
      pid_t pid = fork();
      if (pid == 0) {  // Child process
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); // close unused read end of pipe
        close(fd[1]); // close original write end of pipe
        execvp(arguments[0], arguments); // execute ls command
        perror(BOLDRED"Shelly fail: \033[0m execlp"); // this line only runs if execvp fails
        exit(1);
      } else if (pid > 0) {
        // parent process - read output of child process from pipe
        char buf[1024];
        ssize_t n;
        close(fd[1]); // close write end of pipe
        while ((n = read(fd[0], buf, sizeof(buf))) > 0) {
          write(STDOUT_FILENO, buf, n); // write output to stdout
        }
        close(fd[0]); // close read end of pipe
        waitpid(pid, NULL, 0); // wait for child process to finish
        printf("\n");
      } else {  // Error forking
        perror(BOLDRED"Shelly fail: \033[0m fork");
        exit(1);
      }

    }
    
  }
}