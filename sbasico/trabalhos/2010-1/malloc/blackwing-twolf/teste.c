#include <stdio.h>


#define malloc aloca
#define free   libera_memoria

int main () {

	int i, j, tam;
	//tam = 40;
	void *primeiro = malloc( 200 );
	imprMapa();
	int *segundo = malloc( 100 );
	imprMapa();
	free(primeiro);
	imprMapa();
	int *terceiro = malloc( 200 );
	imprMapa();

	
	return 0;
}
