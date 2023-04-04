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

//Word Count
void wc() {
  char path[16];
  char flag[16];
  FILE *file;
  int output_file;
  char ch;
  char br[5] = "\n";
  int lines = 1, words = 1;

  char output[32] = "Words: ";
  char words_[5];

  printf(BLUE"Enter a path: \033[0m");
  scanf("%s", path);
  printf(BLUE"Enter a flag (ex. -l): \033[0m");
  scanf("%s", flag);


  file = fopen(path, "r");
  output_file = open("output.txt", O_RDWR | O_APPEND);

  if (file == NULL) {
    printf("Error: could not open file.\n");
    exit(1);
  }

    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
          lines++;
      }

      if (ch == ' ' || ch == '\n' || ch == '\t') {
          words++;
      }
    }


    sprintf(words_, "%d", words);
    strcat(output, words_);
    strcat(output, br);
    write(output_file, output, strlen(output));
    if(strcmp(flag, "-l") == 0) {
      printf("Words: %d, Lines: %d\n", words, lines);
    } else {
      printf("Words: %d\n", words);
    }
    
    close(output_file);
    fclose(file);
}

int main() {
  wc();
}