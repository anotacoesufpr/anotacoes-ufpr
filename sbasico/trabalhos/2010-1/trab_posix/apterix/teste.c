#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#define __NR_minhasys        339

int minhasys() {
   return (int) syscall(339);
};

main () {
   printf("O retorno da syscall foi... %d\n", minhasys());
}
