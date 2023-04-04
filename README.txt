Group Members: Tarik Maljanović, Melisa Geca

List of files within this submission:
  1. file.txt
  2. shell (executable)
  3. Shell.c
  4. task3_basic.c
  5. task3_intermediate.c
  6. task3_additionally.c

Q1: If we have a single-core, uniprocessor system that supports multiprogramming, how many
processes can be in a running state in such a system, at any given time?

A1: In this scenario, we can only have one process in the running state. That is because we only have one core,
(a core has registers, ALU, control unit) and thus just enough CPU components for operating a single proccess.
But multiprogramming is supported with the help of scheduling (scheduling algorithms) and context switching.
We would simply implement a scheduling algorithms which would switch between different processes. For example,
we can use round-robin to switch between process A and process B quickly enough to have good response time and
see progress with both processes.


Q2: Explain why system calls are needed for a shared memory method of inter-process
communication (IPC). If there are multiple threads in one process, are the system calls needed
for sharing memory between those threads?

A2: System calls are needed for a shared memory method of inter-process communication (IPC) because shared memory 
involves the coordination of access to a shared resource between multiple processes, which requires the involvement 
of the operating system. System calls are the mechanism through which a user-level process can interact with the 
operating system and request services like allocating shared memory, mapping it into its address space, and synchronizing 
access to it.

When two or more processes want to communicate using shared memory, they need to agree on the location and size of the 
shared memory segment, which requires the use of system calls like shmget() to allocate the shared memory and shmat() 
to map it into the address space of each participating process. Once the shared memory is set up, the processes need 
to coordinate access to it to avoid conflicts and race conditions, which requires the use of synchronization primitives 
like semaphores, which can be obtained through system calls like sem_init() and sem_wait().

In the case of multiple threads within a single process, system calls are not strictly necessary for sharing memory between 
those threads, as they all share the same address space and can access the same memory directly. However, synchronization 
primitives like mutexes and condition variables may still be needed to coordinate access to shared memory between multiple 
threads to avoid race conditions and ensure consistency. These synchronization primitives can also be obtained through system 
calls like pthread_mutex_init() and pthread_cond_wait().

An outline of what we did for the assignment:
For this assignment we implemented a simple shell program using tokens (so the user can enter the command, additional flags, paths etc. in a single line),
and it also supports piping, so when you run a command (wc for exmaple), a child process is created and it will be transformed into the called program (execvp)
and its output will be written in the standard output of the parent process. The parent process will wait for the child process, output the result, and the user is
prompted again. Beside the shell implementation, we worked with system calls (fork(), wait(), exec(), execle(), clone()) and created some simple C programs which
feature these system calls. And additionally, we researched "forkbomb", what it means, why it exists, and why its used. The code is very simple but dangerous.

Instructions for compiling:
Once the user unzips the project folder, they only need to enter in their terminal the command './shell' to run the shell program (no additional compiling needed,
unless they whish to make some changes to the shell within the Shell.c file). If the user wishes to run the task 3 programs, they will nee to compile them
(gcc -o <SOME NAME> <FILE NAME>.c -Wall) and then run it as usual (./<ENTERED NAME>).

Any sources/tutorials you have used to complete the assignment:
The sources we used for this assigned are: man pages, google (googling commands not featured in Mac OS man pages and implementations of the assigned commands),
ChatGPT

Any challenges you encountered along the way:
This assigned was challaning in a way that made us go into details for each implementation. The basics such as: prompt and shell colours didn't impose a challange
such as the implementation of piping, tokens, and system calls, since it required us to actually reasearch and understand the commands, system calls, and C functions.

