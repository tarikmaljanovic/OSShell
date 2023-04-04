#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

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

//Recursice promp function
void prompt() {
  char input[100]; //User input is stored here
  char *arguments[100];
  char hostName[100]; //Host name is stored here
  char *login = getlogin(); //Login name is stored and called here
  gethostname(hostName, 100); //Function for getting the host name of the machine
  

  printf(RED"%s@%s\033[0m"BOLDGREEN":~$\033[0m ", hostName, login);  //The prompt which looks like this "machineName@userName:~$""
  fgets(input, 100, stdin);

  input[strlen(input) - 1] = '\0';
  char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < 100) {
      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    arguments[i] = NULL;

    if(strcmp(arguments[0], "quit") == 0) {
      printf(BOLDBLUE"Goodbye ( ´ ▽ ` )ﾉ\033[0m\n");
      return;
    } else if(strcmp(arguments[0], "name") == 0) {
      printf("Shell Name: "BOLDBLUE"Shelly v1.0.0\033[0m\n");
    } else if(strcmp(arguments[0], "manual") == 0) {
      //A simple man page of this shell, which explaines each available command
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
      int rc = fork();

      if(rc == 0) {
        execvp(arguments[0], arguments);
      } else if(rc > 0) {
        wait(NULL);
      } else if (rc < 0) {
        perror("Failed to fork\n");
        exit(1);
      }
    }
  prompt();
}

int main() {
  prompt();

  return 0;
}