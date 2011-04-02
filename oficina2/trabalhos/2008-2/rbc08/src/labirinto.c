#include "global.h"

int main(int argc, char **argv)
{
	tLABIRINTO labirinto;
	tJOGADOR jogador;
	
	/* Inicia as estruturas com os valores padrão */
	init_structs(&labirinto, &jogador);
	
	if (parse_opt(argc, argv, &labirinto, &jogador))
	{
		init_game(&labirinto, &jogador);
	}
	
	
	return 0;
}
