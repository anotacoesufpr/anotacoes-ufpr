#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#define __NR_mySyscall   337

main () {
	printf("teste");
	syscall(1080);
}
