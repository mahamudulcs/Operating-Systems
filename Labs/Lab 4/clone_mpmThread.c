/*Lab 4-Mahamudul Islam(500963051)
  Q4:
*/
#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int x = 0, y = 0;

int do_something()
{
        sleep(1);
        printf ("\nThis is process (thread) %d.\n", getpid());
        x=7;
        printf("x + y = %d\n", x + y);
        exit(0);
}

int main(int argc, char *argv[])
{
        const int STACK_SIZE = 65536;  // note stack grows down
        char *stack, *stackTop, tempch;
        int cret;

        stack = malloc(STACK_SIZE);
        if (stack == NULL) {
                perror("malloc");
                exit(1);
        }
        stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

        cret = clone(do_something, stackTop, CLONE_VM|CLONE_FILES, NULL);
        if (cret == -1) {
                perror("clone");
                exit(0);
        }
        printf ("\nThis is process (thread) %d.\n", getpid());
        y=1;
        printf("x + y = %d\n", x + y);
}
