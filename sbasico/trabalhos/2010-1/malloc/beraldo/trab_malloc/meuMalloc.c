#include <stdio.h>

#define MAX_ELEM 16
#define TAM_MAX  64
#define NUM_OPER 32

#define malloc aloca
#define free   libera_memoria

int main () {

	int i, j, tam;
	tam = 40;
	void *primeiro = malloc( 132 );
	int *segundo = malloc( 67 );
	int *terceiro = malloc( tam );
	void *vetor[10];

	vetor[0] = malloc (132);
	printf( "Endereço: %p %p %p eee!! %p\n" , primeiro, segundo, terceiro, vetor[1] );
	free( primeiro );
	imprMapa();
	free( segundo );
	imprMapa();
	
	return 0;
}
