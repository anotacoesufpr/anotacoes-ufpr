#include "libPatriz.h"

/** 
* @brief Main()
* 
* @param argc
* @param argv
* 
* @return 0 se deu tudo certo, 1 se deu algo errado
*/ 

int* transicaoBuff;
int  countAux1, countAux2;

int main (int argc, char *argv[])
{

	nodo patricia = NULL;
	nodo patriz = NULL;
	char opcao;
   int k, tipoArvore;
   
   /**
   * @var tipoArvore segundo espeficicacao, assume que arvore inicial eh Patricia
	* 1 para Patricia e 2 para Patriz
   *
   **/
   tipoArvore = '1';

	/**
	* @note Faz a leitura da stdin seguindo especificacao
	***/
	unsigned int *aux; int i;
	while (scanf("%c ", &opcao) != EOF)
	{
        printf ("%c ", opcao);
        if (opcao == 'i' || opcao == 'b')
			{
            scanf ("%d\n", &k);

				/**
				* @note conversao necessaria para atender especificacao
				**/
            aux = apl_dec2bin(k);

				/**
				 * @note Solicitado pela especificacao do trab
				**/
            for (i = 0; i < 5; i++)
                printf ("%u", aux[i]);
            printf("\n");
        }

        if (tipoArvore == '1')
		 	{
				switch(opcao)
				{
					case 'i': 
						patricia = PatriciaInsere (patricia, k);
      	         patriciaImpressao (patricia, -1);
						break;

					case 'b':	
						/**
						* @note Importante: limpar o buffer antes da busca
						**/
      	         apl_free_transicaoBuff ();
      	         patriciaBusca (patricia, k, -1);
						break;

					case 't':
      	         patriz = NULL;
      	         patriz = transformaPatriciaEmPatriz (patricia);
						/**
						* @note Importante: Troca o tipo da arvore
						**/
      	         tipoArvore = '2';
						break;

      	   	case 'c':
						/**
						* @note Importante: limpar o buffer antes da busca
						**/
      	         apl_free_transicaoBuff ();
      	         patriciaAnalisaCusto(patricia, -1);
      	         printf("\n\n%d bytes alocados, \n\n%d visitas realizadas\n", countAux1, countAux2);
      	   		break;
				}

        }
		else
		{
			switch(opcao)
				{
					case 'i': 
						patriz = patrizInsere (patriz, k);
      	         patrizImpressao (patriz);
						break;
				
					case 'b':	
						/**
						* @note Importante: limpar o buffer antes da busca
						**/
      	         apl_free_transicaoBuff ();
      	         buscaPatriz (patriz, k, -1);
						break;
	
					case 't':
      	         patricia = NULL;
      	         patricia = transformaPatrizEmPatricia (patriz);
						/**
						* @note Importante: Troca o tipo da arvore
						**/
      	         tipoArvore = '1';
						break;

 		        	case 'c':
						/**
						* @note Importante: limpar o buffer antes da busca
						**/
 	              apl_free_transicaoBuff ();
 	              patrizAnalisaCusto (patriz);
 	              printf("\n\n%d bytes alocados, \n\n%d visitas realizadas\n", countAux1, countAux2);
					  break;
			}

       }
		printf ("\n");
	}
	return 0;
}
