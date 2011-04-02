/* Este programa solta um processo filho e finaliza o pai, o filho fica
 * inativo ateh receber um sinal, e quando o receber, chama uma funcao. Ele
 * vai ficar rodando infinitamente ateh que seja morto com um kill -9. Rode
 * um ps x para ver o processo e envie outros sinais (kill -14 <pid do
 * processo>) para ver como funciona. Um kill sem valor mata o processo de
 * forma "normal", ou seja, o programa sabe tratar sua saída quando recebe
 * um SIGTERM */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


void *saida (void) {
	printf("\nSaindo...\n");
	exit(107);
}

void trata_sinal (int sinal) {

	if (sinal != 15)
		printf ("\nRecebi sinal: %d\n",sinal);
	else
        // Quando receber um SIGTERM, o processo termina normalmente
		atexit(saida());
}

int main (int argc, char **argv) {

	int i;
	int pid;
	pid = fork();

    // Processo pai:
	if (pid != 0) exit(0);

    // Processo filho:
	if (pid == 0) {

        /* Este for aqui trata todos os sinais possiveis, existem dois
         * sinais que sao intrataveis pelo programa, 9(SIGKILL) e
         * 19(SIGSTOP). Para + informacoes, consulte o comando, trap -l ou
         * man 7 signal */
		for (i=0; i<=64; i++)
			signal(i,trata_sinal);

		while (1) sleep(3);

	}
	return 0;
}
