#include <stdio.h>
#include <sys/types.h>
#include <regex.h>

/**
 * @brief Função que verifica se um padrão (pattern - Expressão Regular) casa com uma string. Segue o padrão da função homônima do PHP.
 * @param er Padrão (pattern) a ser buscado.
 * @param str String de entrada, onde o padrão será buscado.
 * @return Retorna 1 se o padrão casar, 0 se não. Em caso de erro, retorna -1.
*/
int preg_match(const char *er, const char *str)
{
	regex_t reg;
	
	if (regcomp(&reg , er, REG_EXTENDED|REG_NOSUB) != 0)
	{
		fprintf(stderr, "Erro ao compilar a ER\n");
		return -1;
	}
	
	if ((regexec(&reg, str, 0, (regmatch_t *)NULL, 0)) == 0)
		return 1;
	else
		return 0;
}
/*********************************************/
