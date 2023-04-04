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
  char hostName[100]; //Host name is stored here
  char *login = getlogin(); //Login name is stored and called here

  gethostname(hostName, 100); //Function for getting the host name of the machine
  

  printf(RED"%s@%s\033[0m\033[1;32m:~$\033[0m ", hostName, login);  //The prompt which looks like this "machineName@userName:~$""
  scanf("%s", input); //Get input from user

  if(strcmp(input, "quit") == 0) { //If user enteres "quit", the shell prints a goodbye message and stops the prompt() funnction
    printf(BOLDBLUE"Goodbye ( ´ ▽ ` )ﾉ\033[0m\n");
    return;
  //The following code is for the cases when the use enteres "wc", "grep", "df", "cmatrix"
  //The way these commands are executes, is when the user enteres the command name, a child process is created and the execl() function
  //is used to transofrm the chils process into the implementations of these commands (which are the executables included wothin this .zip folder)
  //The parent process (the prompt) will wait for the child process and then resume once done
  } else if (strcmp(input, "wc") == 0) {
    int rc = fork();
    if(rc == 0) {
      execl("wc", NULL);
    } else if (rc > 0) {
      wait(NULL);
    }
  } else if(strcmp(input, "grep") == 0) {
    int rc = fork();
    if(rc == 0) {
      execl("grep", NULL);
    } else if (rc > 0) {
      wait(NULL);
    }
  } else if (strcmp(input, "name") == 0) { //Print the shell name
    printf("Shell Name: "BOLDBLUE"Shelly v1.0.0\033[0m\n");
  } else if (strcmp(input, "df") == 0) {
    int rc = fork();
    if(rc == 0) {
      execl("df", NULL);
    } else if (rc > 0) {
      wait(NULL);
    }
  } else if(strcmp(input, "cmatrix") == 0) {
    int rc = fork();
    if(rc == 0) {
      execl("cmatrix", NULL);
    } else if (rc > 0) {
      wait(NULL);
    }
  } else if(strcmp(input, "clear") == 0) { //Use the "clear" shell command for clearing the screen when it gets too messy
    system("clear"); //Not actually implemented, just used the system() function which executes shell commands (of the actual shell of the machine)
  } else if(strcmp(input, "man") == 0) {
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

  }

  prompt();
}

int main() {
  prompt();

  return 0;
}