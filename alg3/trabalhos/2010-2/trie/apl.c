#include <stdio.h>
#include <stdlib.h>
#include "libArvBin.h"

int main(int argc, char *argv[]){
  No *Dicionario;
  Registro x;
  int status;
  FILE *fp; /*abertura de arquivo/stdin*/
	char opcao; /*leitura da opcao*/

	/* verifica se a leitura sera em arquivo ou stdin */
	if(argc>1){
		if((fp=fopen(argv[1], "r")) == NULL){
			fprintf(stderr,"Erro ao abrir o arquivo especificado!\n");
			exit(1);
		}			
	}
	else{
		fp=stdin;
	}

	/* inicializa arvore */
  Inicializa( &Dicionario );

	/*leitura dos dados*/
	while(!feof(fp) && !ferror(fp)){
		fscanf(fp,"%c %ld\n",&opcao,&x.Chave);
	
		switch(opcao) {
			case 'i': 
                printf("%c %ld\n", opcao, x.Chave);
								status = Insere (x,&Dicionario);
								if(status == ERRO){
									fprintf(stderr,"ERRO: %ld ja' existe\n",x.Chave);
								}
								imprimeArv(Dicionario);
								printf("\n");				    						
								break;
			case 'b':	
								printf("%c %ld\n", opcao, x.Chave);
								Busca(x.Chave,Dicionario);
								printf("\n");
								break;
			case 'r':
                printf("%c %ld\n", opcao, x.Chave);
                /*remover(x.Chave,Pesquisa(x.Chave,Dicionario));*/
								break;
		}
	}

	if(fp != stdin){
		fclose(fp);
	}

	free(Dicionario);
/*
  printf("Insire elemento: ");
  scanf("%ld", &(x.Chave));

  while (x.Chave > 0)
  {
    status = Insere ( x , &Dicionario ) ;
    if( status == ERRO)
      printf("ERRO: %ld ja' existe\n", x.Chave);
    printf("Arvore \n");
    imprimeArv( Dicionario );
    printf("\nInsere elemento: ");
    scanf("%ld", &(x.Chave));
  }
*/

return 0;  
}

