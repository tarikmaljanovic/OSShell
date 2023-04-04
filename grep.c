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

//Find and print the pattern in a file
void grep() {
  char path[16];
  char pattern[16];
  char flag[16];
  char output[32] = "Line: ";
  char br[5] = "\n";

  int output_file = open("output.txt", O_RDWR | O_APPEND);

  int line_num = 1;
  char line[1024];

  printf(BLUE"Enter path: \033[0m");
  scanf("%s", path);
  printf(BLUE"Enter pattern: \033[0m");
  scanf("%s", pattern);
  printf(BLUE"Enter flag (ex. -v): \033[0m");
  scanf("%s", flag);

  FILE *file = fopen(path, "r");

  if(strcmp(flag, "-v")) {
    while(fgets(line, 1024, file)) {
      if (strstr(line, pattern)) {
        printf(BOLDGREEN"File:\033[0m %s: "BOLDGREEN"Line Number:\033[0m %d: "BOLDGREEN"Line:\033[0m %s\n", path, line_num, line);
        strcat(output, line);
        strcat(output, br);
        write(output_file, output, strlen(output));
      }

      line_num++;
    }
  } else {
    while(fgets(line, 1024, file)) {
      if (strstr(line, pattern) == 0) {
        printf(BOLDGREEN"File:\033[0m %s: "BOLDGREEN"Line Number:\033[0m %d: "BOLDGREEN"Line:\033[0m %s\n", path, line_num, line);
        strcat(output, line);
        strcat(output, br);
        write(output_file, output, strlen(output));
      }

      line_num++;
    }
  }

  close(output_file);
  fclose(file);
}

int main() {
  grep();
}