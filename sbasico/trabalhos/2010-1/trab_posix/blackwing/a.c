#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#define __NR_minhasys        337

int minhasys() {
   return (int) syscall(337);
};

main () {
   printf("The return code from the helloworld system call is %d\n", minhasys());
}
