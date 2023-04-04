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

//Information about the diskspace of a filesystem
void df() {
  //Structures where the disk info is located
  struct statvfs vfs;

  //Variables which store information such as "total size", "used size" and "free size"s
  unsigned long long total_size = vfs.f_blocks * vfs.f_frsize;
  unsigned long long used_size = (vfs.f_blocks - vfs.f_bfree) * vfs.f_frsize;
  unsigned long long free_size = vfs.f_bfree * vfs.f_frsize;

  printf(BOLDBLUE"Total size: \033[0m%llu "BOLDBLUE"Used Size: \033[0m%llu "BOLDBLUE"Free Size: \033[0m%llu "BOLDBLUE"Used Size: \033[0m%llu%% \n", total_size, used_size, free_size, used_size*100/total_size);
  printf(BOLDBLUE"Unit: 512-Byte Blocks\033[0m\n");

}

int main() {
  df();
}