#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Função responsável pela manipulação de mensagens de erro.
 * @param msg Mensagem de erro a ser exibida.
 * @param is_fatal Se is_fatal receber o valor 1, o programa será encerrado após a exibição da mensagem de erro.
 * @param file Arquivo em que o erro ocorreu. Use a constante __FILE__.
 * @param line Linha em que o erro ocorreu. Use a constante __LINE__.
*/
void log_error(char *msg, int is_fatal, char *file, int line)
{
	fprintf(stderr, "Error: %s. File: %s. Line: %d.\n", msg, file, line);
	
	if (is_fatal)
	{
		exit(1);
	}
}
/*******************************************/
