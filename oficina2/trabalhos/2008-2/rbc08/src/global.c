#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>

#include "global.h"
#include "files.h"
#include "error.h"
#include "memory.h"


/* Protótipos de funções não inclusas no respectivo arquivo .h */
void inicia_cores();
void pausar(tLABIRINTO *labirinto, tJOGADOR *jogador);
void desenha_mapa(tLABIRINTO *labirinto, tJOGADOR *jogador);
void mostra_mapa_final(tLABIRINTO *labirinto, tJOGADOR *jogador);
void mensagem_vencedor(tLABIRINTO *labirinto, tJOGADOR *jogador);
void entrar(int destino[2], int direcao, tLABIRINTO *labirinto, tJOGADOR *jogador);
int verifica_chave(int destino[2], int direcao, tLABIRINTO *labirinto, tJOGADOR *jogador);
void pega_chave(int destino[2], tLABIRINTO *labirinto, tJOGADOR *jogador);
int verifica_permissao_movimento(int destino[2], int direcao, tLABIRINTO *labirinto, tJOGADOR *jogador);
void mover(tLABIRINTO *labirinto, tJOGADOR *jogador, int mov);
void mostra_passos(tLABIRINTO *labirinto, tJOGADOR *jogador);




/**
 * @brief Função chamada ao iniciar o programa. Inicia NCurses, as cores utilizadas no jogo. Mostra a tela inicial do jogo.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void init_game(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	int c;
	
	/* Inicia NCurses */
	inicia_curses();
	
	/* Cria os pares de cores utilizados */
	inicia_cores();
	
	
	/* Oculta o cursor do teclado */
	curs_set(0);
	
	/* Cor de fundo */
	bkgd(COLOR_PAIR(branco_no_preto));

	mvprintw(2, 20, "JOGO DO LABIRINTO");

	mvprintw(5, 5, "Use as seguintes teclas durante o jogo:");
	mvprintw(8, 5, "[q] Sair do jogo");
	mvprintw(9, 5, "[p] Pausar o jogo");
	mvprintw(10, 5, "[SETAS] Movimentar o jogador");
	mvprintw(11, 5, "[0-9] Alterar raio de visão.");
	
	mvprintw(16, 18, "Pressione 's' para iniciar o jogo ou 'q' para sair");
	
	
	do
	{
		c = getch();
	
		switch (c)
		{
			case TECLA_S_UPPER:
			case TECLA_S_LOWER:
				jogar(labirinto, jogador);
				break;
			case TECLA_Q_UPPER:
			case TECLA_Q_LOWER:
				finish_game(labirinto, jogador);
				break;
		}
	}
	while (c != TECLA_S_UPPER && c != TECLA_S_LOWER && c != TECLA_Q_UPPER && c != TECLA_Q_LOWER);
}
/***********************************************/



/**
 * @brief Função chamada na finalização do jogo.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void finish_game(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	/* Libera a memória usada pelos arquivos de entrada e saída */
	free_io_files(labirinto);
	
	/* Libera a memória usada pela matriz "mapa" */
	destroi_mapa(labirinto);
	
	/* Finaliza NCurses */
	finaliza_curses();
	
	exit(0);
}
/*********************************************/




/**
 * @brief Inicia NCurses.
*/
void inicia_curses()
{
	/* É necessário criar a variável tela, pois ela será usada na função keypad() */
	WINDOW *tela;
	
	tela = initscr();
	
	/* Desabilita a exibição dos caracteres digitados pelo usuário. */
	noecho();
	
	/* Desabilita o buffer de linha, disponbilizando imediatamente o processamento pelo programa do caractere digitado */
	cbreak();
	
	/* Ativa as teclas de funções, como as setas. */
	keypad(tela, TRUE);
}
/**********************************************/



/**
 * @brief Finaliza NCurses.
*/
void finaliza_curses()
{
	endwin();
}
/***************************************************/



/**
 * @brief Inicia as cores NCurses, criando os respectivos pares de cores.
*/
void inicia_cores()
{
	start_color();
	
	init_pair(preto_no_branco, COLOR_BLACK, COLOR_WHITE);
	init_pair(preto_no_azul, COLOR_BLACK, COLOR_BLUE);
	init_pair(preto_no_verde, COLOR_BLACK, COLOR_GREEN);
	init_pair(preto_no_vermelho, COLOR_BLACK, COLOR_RED);
	init_pair(preto_no_amarelo, COLOR_BLACK, COLOR_YELLOW);
	init_pair(branco_no_preto, COLOR_WHITE, COLOR_BLACK);
	init_pair(branco_no_azul, COLOR_WHITE, COLOR_BLUE);
	init_pair(branco_no_vermelho, COLOR_WHITE, COLOR_RED);
	init_pair(branco_no_verde, COLOR_WHITE, COLOR_GREEN);
	init_pair(branco_no_amarelo, COLOR_WHITE, COLOR_YELLOW);
	init_pair(azul_no_branco, COLOR_BLUE, COLOR_WHITE);
	init_pair(azul_no_preto, COLOR_BLUE, COLOR_BLACK);
	init_pair(azul_no_vermelho, COLOR_BLUE, COLOR_RED);
	init_pair(azul_no_verde, COLOR_BLUE, COLOR_GREEN);
	init_pair(azul_no_amarelo, COLOR_BLUE, COLOR_YELLOW);
	init_pair(verde_no_vermelho, COLOR_GREEN, COLOR_RED);
	init_pair(verde_no_azul, COLOR_GREEN, COLOR_BLUE);
	init_pair(verde_no_branco, COLOR_GREEN, COLOR_WHITE);
	init_pair(verde_no_preto, COLOR_GREEN, COLOR_BLACK);
	init_pair(verde_no_amarelo, COLOR_GREEN, COLOR_YELLOW);
	init_pair(vermelho_no_branco, COLOR_RED, COLOR_WHITE);
	init_pair(vermelho_no_preto, COLOR_RED, COLOR_BLACK);
	init_pair(vermelho_no_azul, COLOR_RED, COLOR_BLUE);
	init_pair(vermelho_no_verde, COLOR_RED, COLOR_GREEN);
	init_pair(vermelho_no_amarelo, COLOR_RED, COLOR_YELLOW);
	init_pair(amarelo_no_azul , COLOR_YELLOW, COLOR_BLUE);
	init_pair(amarelo_no_vermelho , COLOR_YELLOW, COLOR_RED);
	init_pair(amarelo_no_verde , COLOR_YELLOW, COLOR_GREEN);
	init_pair(amarelo_no_preto , COLOR_YELLOW, COLOR_BLACK);
	init_pair(amarelo_no_branco , COLOR_YELLOW, COLOR_WHITE);
}
/**************************************************/




/**
 * @brief Inicia as estruturas tJOGADOR e tLABIRINTO, atribuindo-lhes os valores padrões de cada elemento, se houver.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void init_structs(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	labirinto->mapa = NULL;
	labirinto->linhas = 0;
	labirinto->colunas = 0;
	
		
	jogador->chave_azul = 0;
	jogador->chave_vermelha = 0;
	jogador->chave_amarela = 0;
	jogador->chave_verde = 0;
	jogador->raio_visao = 1;
	jogador->caminho.capacidade = 0;
	jogador->caminho.tamanho = 0;
	jogador->caminho.passos = NULL;
	
	/* Inicia o vetor de passos do jogador */
	aloca_memoria_passos(jogador, 0);
	
	
	/* Inicia os arquivos de entrada e saída */
	init_io_files(labirinto);
}
/***********************************************/





/**
 * @brief Função responsável pelo processamento das opções da linha de comando.
 * @param argc Parâmetro argc da função main.
 * @param argv Parâmetro argv da função main.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
 * @return Retorna 1 se o processamento for bem-sucedido. Caso contrário, retorna 0.
*/
int parse_opt(int argc, char **argv, tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	/* Variáveis definidas em unistd.h */
	extern char *optarg;
    extern int optind, opterr, optopt;
    
    
    /* opções aceitas pelo programa */
    static char opcoes[] = "il:o:";
    
    /* variável que armazena a opção (usada no while) */
    int opcao;
    
    
    
    while((opcao = getopt(argc, argv, opcoes)) != -1)
    {
    	switch (opcao)
    	{
    		case 'i':
    			jogador->game_mode = MODO_INTERATIVO;
    			break;
    			
    		case 'l':
    			/* Aloca memória suficiente para armazenar o nome do arquivo. */
    			labirinto->in_file = (char *) realloc(labirinto->in_file, (strlen(optarg) + 1) * sizeof(char));
    			
    			if (labirinto->in_file == NULL)
    			{
    				log_error("Erro de alocação de memória", 1, __FILE__, __LINE__);
    				return 0;
    			}
    			
    			strcpy(labirinto->in_file, optarg);
    			break;
    			
    		case 'o':
    			/* Aloca memória suficiente para armazenar o nome do arquivo. */
    			labirinto->out_file = (char *) realloc(labirinto->out_file, (strlen(optarg) + 1) * sizeof(char));
    			
    			if (labirinto->out_file == NULL)
    			{
    				log_error("Erro de alocação de memória", 1, __FILE__, __LINE__);
    				return 0;
    			}
    			
    			strcpy(labirinto->out_file, optarg);
    			break;
    	}
    }
    
    
	/* Se o modo de jogo for o interativo, o arquivo do labirinto deve ser especificado (opção -l) */
	if (jogador->game_mode == MODO_INTERATIVO && (labirinto->in_file == NULL || !strcmp(labirinto->in_file, "stdin")))
	{
    	log_error("Usando a opção -i, é necessário usar a opção -l", 1, __FILE__, __LINE__);
    	return 0;
    }
    
    
    return 1;
}
/*************************************************/





/**
 * @brief Função responsável pelo início do jogo propriamente dito. Carrega o mapa, verifica a tecla pressionada e exibe o mapa, num loop que só encerra quando o usuário digita 'q', para sair do jogo, 'p', para pausá-lo, ou encontra a saída.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void jogar(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	int key;
	
	/* Carrega o mapa do arquivo na matriz "mapa" */
	carregar_mapa(labirinto, jogador);
	
	
	/* Mostra o mapa na tela */
	desenha_mapa(labirinto, jogador);
	
	while((key = getch()))
	{
		switch (key)
		{
			/* Q = Sair do jogo */
			case TECLA_Q_UPPER:
			case TECLA_Q_LOWER:
				finish_game(labirinto, jogador);
				break;
			
			/* P = pausar jogo */
			case TECLA_P_UPPER:
			case TECLA_P_LOWER:
				pausar(labirinto, jogador);
				break;
			
			/* SETAS = Movimentação do jogador no labirinto */
			case TECLA_SETA_DIREITA:
				mover(labirinto, jogador, MOVER_DIREITA);
				break;
			
			case TECLA_SETA_ESQUERDA:
				mover(labirinto, jogador, MOVER_ESQUERDA);
				break;
			
			case TECLA_SETA_CIMA:
				mover(labirinto, jogador, MOVER_CIMA);
				break;
			
			case TECLA_SETA_BAIXO:
				mover(labirinto, jogador, MOVER_BAIXO);
				break;
			
			
			/* [0-9] = Altera o raio de visão do jogador */
			case TECLA_0:
				jogador->raio_visao = 0;
				break;
			
			case TECLA_1:
				jogador->raio_visao = 1;
				break;
			
			case TECLA_2:
				jogador->raio_visao = 2;
				break;
			
			case TECLA_3:
				jogador->raio_visao = 3;
				break;
			
			case TECLA_4:
				jogador->raio_visao = 4;
				break;
			
			case TECLA_5:
				jogador->raio_visao = 5;
				break;
			
			case TECLA_6:
				jogador->raio_visao = 6;
				break;
			
			case TECLA_7:
				jogador->raio_visao = 7;
				break;
			
			case TECLA_8:
				jogador->raio_visao = 8;
				break;
			
			case TECLA_9:
				jogador->raio_visao = 9;
				break;
				
		}
		
		desenha_mapa(labirinto, jogador);
	}
}
/****************************************************/


/**
 * @brief Função que realiza a pausa do jogo. Os dados correntes são salvos num arquivo binário que poderá ser carregado posteriormente.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void pausar(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	FILE *fp;
	register unsigned int i = 0;
	
	clear();
	
	
	/* Verifica se foi especificado um arquivo de saída */
	if (labirinto->out_file == NULL || (strcmp(labirinto->out_file, "stdout") == 0))
	{
		char filename[30];
		
		printw("Informe o nome do arquivo de saída: ");
		refresh();
		
		/* Ativa a exibição do cursor do teclado */
		curs_set(1);
		echo();
		
		/* lê o nome do arquivo */
		getstr(filename);
		
		curs_set(0);
		noecho();
		
		refresh();
		
		/* aloca o tamanho adequado para o novo valor do nome do arquivo de saída */
		if ((labirinto->out_file = (char *) realloc(labirinto->out_file, (strlen(filename) + 1) * sizeof(char))) == NULL)
		{
			log_error("Erro ao realocar memória", 1, __FILE__, __LINE__);
		}
		
		strcpy(labirinto->out_file, filename);
		
	}
	
	/* Abre o arquivo no modo binário para escrita a fim de salvar os dados atuais */
	fp = abrir_arquivo(labirinto->out_file, "wb");
	fwrite(labirinto, sizeof(tLABIRINTO), 1, fp);
	fwrite(jogador, sizeof(tJOGADOR), 1, fp);	
		
	/* Salva a matriz do mapa */
	for (i = 0; i < labirinto->linhas; i++)
	{
		fwrite(labirinto->mapa[i], sizeof(char), labirinto->colunas, fp);
	}
		
	/* Salva a matriz do caminho do jogador */
	for (i = 0; i < jogador->caminho.tamanho; i++)
	{
		fwrite(jogador->caminho.passos[i], sizeof(unsigned int), 2, fp);
	}
		
	fechar_arquivo(fp);
		
	clear();
	printw("Dados salvos com sucesso no arquivo '%s'.\nVocê pode usá-lo no parâmetro -l para carregá-lo a fim de recomeçar o jogo", labirinto->out_file);
	printw("\n\nPressione qualquer tecla para finalizar");
	refresh();
	getch();
	finish_game(labirinto, jogador);
}
/**********************************************/




/**
 * @brief Função que imprime o mapa na tela.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void desenha_mapa(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	register int i, j;
	
	/* As variáveis terminadas em _centro são usadas na centralização do mapa na tela. As terminadas em _raio são uasadas para viabilizar a implementação do raio de visão, informando onde a exibição do labirinto deve iniciar e terminar. */
	int cor, coluna_inicio_centro, linha_inicio_centro, linha_inicio_raio, linha_fim_raio, coluna_inicio_raio, coluna_fim_raio;
	
	/* Esta variável será usada para armazenar a soma ou a diferença entre a posição do jogador e o raio de visão. Por um motivo não identificado, a não utilização dessa variável impede a implementação do raio de visão, de forma que as verificações nunca sejam satisfeitas. */
	int tmp;
	
	
	/* Define a linha e a coluna de início, a fim de centralizar o mapa na tela */
	coluna_inicio_centro = ((COLUNAS_TERMINAL / 2) - (labirinto->colunas / 2));
	linha_inicio_centro = ((LINHAS_TERMINAL / 2) - (labirinto->linhas / 2));
	
		
	/* Define o local onde começará e terminará a exibição do mapa, conforme o raio de visão */
	linha_inicio_raio = (jogador->raio_visao) ? ((tmp = (jogador->pos_y - jogador->raio_visao)) > 0 ? tmp : 0) : 0;
	linha_fim_raio = (jogador->raio_visao) ? ((tmp = (jogador->pos_y + jogador->raio_visao)) < labirinto->linhas ? tmp : labirinto->linhas - 1) : labirinto->linhas - 1;
	coluna_inicio_raio = (jogador->raio_visao) ? ((tmp = (jogador->pos_x - jogador->raio_visao)) >= 0 ? tmp : 0) : 0;
	coluna_fim_raio = (jogador->raio_visao) ? ((tmp = (jogador->pos_x + jogador->raio_visao)) < labirinto->colunas ? tmp : labirinto->colunas - 1) : labirinto->colunas - 1;
	
	/* limpa a tela */
	clear();
	
	/* A variável "tamanho" da estrutura "caminho" armazena o total de índices de "passos". Como um dos índices é a posição inicial, ela não deve ser considerada como um passo. Logo, deve-se subtrair uma unidade. */
	printw("Passos: %d\n", jogador->caminho.tamanho - 1);
	printw("Chaves: vermelha: %s | azul: %s | amarela: %s | verde: %s", (jogador->chave_vermelha ? "sim" : "não"), (jogador->chave_azul ? "sim" : "não"), (jogador->chave_amarela ? "sim" : "não"), (jogador->chave_verde ? "sim" : "não"));
	
	
	for (i = linha_inicio_raio; i <= linha_fim_raio; i++)
	{
		/* Move para o centro da linha */
		move(linha_inicio_centro, coluna_inicio_centro);
		
		for (j = coluna_inicio_raio; j <= coluna_fim_raio; j++)
		{
			/* Verifica qual é o caractere corrente, a fim de utilizar a cor correspondente */
			switch (labirinto->mapa[i][j])
			{
				case CHAR_JOGADOR:
				case CHAR_LIVRE:
				case CHAR_PAREDE:
				case CHAR_SAIDA:
					cor = branco_no_preto;
					break;
				
				case CHAR_CHAVE_VERMELHA:
				case CHAR_PORTA_VERMELHA:
					cor = vermelho_no_preto;
					break;
				
				case CHAR_CHAVE_AZUL:
				case CHAR_PORTA_AZUL:
					cor = azul_no_preto;
					break;
				
				case CHAR_CHAVE_AMARELA:
				case CHAR_PORTA_AMARELA:
					cor = amarelo_no_preto;
					break;
				
				case CHAR_CHAVE_VERDE:
				case CHAR_PORTA_VERDE:
					cor = verde_no_preto;
					break;
				
			}
			/* Ativa a cor selecionada */
			attron(COLOR_PAIR(cor));
			
			printw("%c", labirinto->mapa[i][j]);
			
			/* Desativa a cor selecionada */
			attroff(COLOR_PAIR(cor));
		}
		linha_inicio_centro++;
		printw("\n");
	}
	
	refresh();
}
/*************************************************/



/*
 * @brief Função que mostra o estado final do mapa, quando o jogador encontra a saída.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void mostra_mapa_final(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	register unsigned int i, j;
	FILE *fp;
	
	/* Abre o arquivo da saída padrão */
	fp = abrir_arquivo(labirinto->out_file, "a");
	
	
	/* Mostra as dimensões do labirinto */
	printw("\n\n%d x %d\n\n", labirinto->linhas, labirinto->colunas);
	
	if (strcmp(labirinto->out_file, "stdout") != 0)
	{
		fprintf(fp, "\n\n%d x %d\n\n", labirinto->linhas, labirinto->colunas);
	}
	
	
	/* Desenha o mapa */
	for (i = 0; i < labirinto->linhas; i++)
	{
		for (j = 0; j < labirinto->colunas; j++)
		{
			printw("%c", labirinto->mapa[i][j]);
			
			if (strcmp(labirinto->out_file, "stdout") != 0)
			{
				fprintf(fp, "%c", labirinto->mapa[i][j]);
			}
		}
		printw("\n");
		
		fprintf(fp, "\n");
		
	}
	
	if (strcmp(labirinto->out_file, "stdout") != 0)
	{
		fechar_arquivo(fp);
	}
}
/*****************************************/



/**
 * @brief Função chamada quando o jogador encontra a saída do labirinto. Apresenta a mensagem de sucesso.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void mensagem_vencedor(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	FILE *fp;
	
	clear();
	
	printw("O aluno encontrou a saída em %d passos\n", jogador->caminho.tamanho - 1);
	
	fp = abrir_arquivo(labirinto->out_file, "a");
	if (strcmp(labirinto->out_file, "stdout") != 0)
	{
		fprintf(fp, "O aluno encontrou a saída em %d passos\n", jogador->caminho.tamanho - 1);
	}
	fechar_arquivo(fp);
	
	mostra_passos(labirinto, jogador);
	mostra_mapa_final(labirinto, jogador);
	refresh();
	getch();
	finish_game(labirinto, jogador);
}
/*********************************************/




/**
 * @brief Função chamada ao encontrar uma porta aberta ou cuja chave correspondente o jogador possui. A função verifica se o caractere após a porta é um espaço livre. Se for, tranfere o jogador para lá, caso contrário, apenas abre a porta e mantém o jogador na posição corrente.
 * @param destino Vetor que representa a posição para onde o jogador deseja ir.
 * @param direcao Direção do movimento. Devem ser usadas as constantes MOVER_CIMA, MOVER_BAIXO, MOVER_ESQUERDA, MOVER_BAIXO.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void entrar(int destino[2], int direcao, tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	/* Este vetor é necessário pois será usado para verificar se o destino (caractere após a porta) é um espaço livre */
	int possivel_destino[2];
	possivel_destino[0] = destino[0];
	possivel_destino[1] = destino[1];
	
	/* Abre a porta */
	labirinto->mapa[destino[1]][destino[0]] = CHAR_PORTA_ABERTA;
	
	/* Verifica a direção do movimento, a fim de definir a posição final do jogador após passar pela porta. */
	switch (direcao)
	{
		case MOVER_CIMA:
			possivel_destino[1]--;
			break;
			
		case MOVER_BAIXO:
			possivel_destino[1]++;
			break;
			
		case MOVER_DIREITA:
			possivel_destino[0]++;
			break;
			
		case MOVER_ESQUERDA:
			possivel_destino[0]--;
			break;
	}
	
	/* Verifica se a posição final não está além dos limites do labirinto */
	if (possivel_destino[0] < labirinto->colunas && possivel_destino[1] < labirinto->linhas)
	{
		/* Verifica o que há na posição para onde o jogador se destinará */
		switch (labirinto->mapa[possivel_destino[1]][possivel_destino[0]])
		{
			/* Se for um local livre, realiza o movimento */
			case CHAR_LIVRE:
				labirinto->mapa[possivel_destino[1]][possivel_destino[0]] = CHAR_JOGADOR;
				labirinto->mapa[jogador->pos_y][jogador->pos_x] = CHAR_LIVRE;
				jogador->pos_x = possivel_destino[0];
				jogador->pos_y = possivel_destino[1];
				salva_posicao(jogador);
				break;
			
			/* Se for a saída, mostra a mensagem de sucesso */
			case CHAR_SAIDA:
				jogador->pos_x = possivel_destino[0];
				jogador->pos_y = possivel_destino[1];
				salva_posicao(jogador);
				mensagem_vencedor(labirinto, jogador);
				break;
			
			case CHAR_PORTA_AZUL:
			case CHAR_PORTA_VERMELHA:
			case CHAR_PORTA_AMARELA:
			case CHAR_PORTA_VERDE:
				entrar(possivel_destino, direcao, labirinto, jogador);
			
			case CHAR_CHAVE_AZUL:
			case CHAR_CHAVE_VERMELHA:
			case CHAR_CHAVE_AMARELA:
			case CHAR_CHAVE_VERDE:
				pega_chave(possivel_destino, labirinto, jogador);
		}
		
	}
}
/**********************************************/



/**
 * @brief Função que verifica se o jogador possui a chave correspondente à porta que deseja abrir.
 * @param destino Vetor que representa a posição para onde o jogador deseja ir.
 * @param direcao Direção do movimento. Devem ser usadas as constantes MOVER_CIMA, MOVER_BAIXO, MOVER_ESQUERDA, MOVER_BAIXO.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
 * @return Retorna 1 se o jogador possui a chave correspondente. Caso contrário, retorna 0.
*/
int verifica_chave(int destino[2], int direcao, tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	int possui_chave = 0;
	char char_dest = labirinto->mapa[destino[1]][destino[0]];
	
	/* Verifica qual é o caractere presente na posição de destino do jogador */
	switch (char_dest)
	{
		case CHAR_PORTA_AZUL:
			possui_chave = (jogador->chave_azul) ? 1 : 0;
			break;
			
		case CHAR_PORTA_VERMELHA:
			possui_chave = (jogador->chave_vermelha) ? 1 : 0;
			break;
			
		case CHAR_PORTA_AMARELA:
			possui_chave = (jogador->chave_amarela) ? 1 : 0;
			break;
			
		case CHAR_PORTA_VERDE:
			possui_chave = (jogador->chave_verde) ? 1 : 0;
			break;
	}
	
	if (possui_chave)
	{
		entrar(destino, direcao, labirinto, jogador);
		return 1;
	}
	
	return 0;
}
/*********************************************/




/**
 * @brief Adiciona à estrutura tJOGADOR a chave adquirida pelo jogador.
 * @param destino Vetor que representa a posição para onde o jogador deseja ir.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void pega_chave(int destino[2], tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	
	char char_dest = labirinto->mapa[destino[1]][destino[0]];
	
	switch (char_dest)
	{
		case CHAR_CHAVE_AZUL:
			jogador->chave_azul = 1;
			break;
		
		case CHAR_CHAVE_VERMELHA:
			jogador->chave_vermelha = 1;
			break;
			
		case CHAR_CHAVE_AMARELA:
			jogador->chave_amarela = 1;
			break;
		
		case CHAR_CHAVE_VERDE:
			jogador->chave_verde = 1;
			break;
	}
	
	/* Move o jogador */
	labirinto->mapa[destino[1]][destino[0]] = CHAR_JOGADOR;
	labirinto->mapa[jogador->pos_y][jogador->pos_x] = CHAR_LIVRE;
	jogador->pos_x = destino[0];
	jogador->pos_y = destino[1];
	salva_posicao(jogador);
}
/********************************************/






/**
 * @brief Verifica se o jogador pode realizar o movimento, se o destino não é uma parede ou uma porta cuja chave o jogador não possui.
 * @param destino Vetor que representa a posição para onde o jogador deseja ir.
 * @param direcao Direção do movimento. Devem ser usadas as constantes MOVER_CIMA, MOVER_BAIXO, MOVER_ESQUERDA, MOVER_BAIXO.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
 * @return Retorna 1 se o movimento for permitido. caso contrário, retorna 0.
*/
int verifica_permissao_movimento(int destino[2], int direcao, tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	char char_dest;
	
	/* Não é posível iniciar a variável char_dest antes da verificação do destino, pois, se o destino ultrapassar o tamanho do mapa, haverá erro de segmentação */
	
	if ((destino[0] > (labirinto->colunas - 1)) || (destino[1] > (labirinto->linhas - 1)))
	{
		return 0;
	}
	
	char_dest = labirinto->mapa[destino[1]][destino[0]];
	
	
	switch (char_dest)
	{
		case CHAR_PAREDE:
			return 0;
			break;
		
		case CHAR_SAIDA:
			jogador->pos_x = destino[0];
			jogador->pos_y = destino[1];
			salva_posicao(jogador);
			mensagem_vencedor(labirinto, jogador);
			break;
		
		case CHAR_PORTA_AZUL:
		case CHAR_PORTA_VERMELHA:
		case CHAR_PORTA_AMARELA:
		case CHAR_PORTA_VERDE:
			return (verifica_chave(destino, direcao, labirinto, jogador));
			break;
		
		case CHAR_CHAVE_AZUL:
		case CHAR_CHAVE_VERMELHA:
		case CHAR_CHAVE_AMARELA:
		case CHAR_CHAVE_VERDE:
			pega_chave(destino, labirinto, jogador);
			break;
		
		case CHAR_LIVRE:
			/* Move o jogador */
			labirinto->mapa[destino[1]][destino[0]] = CHAR_JOGADOR;
			labirinto->mapa[jogador->pos_y][jogador->pos_x] = CHAR_LIVRE;
			jogador->pos_x = destino[0];
			jogador->pos_y = destino[1];
			salva_posicao(jogador);
			return 1;
			break;
		
		case CHAR_PORTA_ABERTA:
			entrar(destino, direcao, labirinto, jogador);
			return 1;
			break;
	}
	
	return 1;
}
/*************************************************/




/**
 * @brief Movimenta o jogador no labirinto.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
 * @param mov Direção do movimento. Devem ser usadas as constantes MOVER_CIMA, MOVER_BAIXO, MOVER_ESQUERDA, MOVER_BAIXO.
*/
void mover(tLABIRINTO *labirinto, tJOGADOR *jogador, int mov)
{
	/* O vetor destino armazena as posições X e Y para onde o jogador deseja se mover. O índice 0 corresponde a X, o 1, a Y. */
	int destino[2];
	
	/* Verifica qual é a direção do movimento e atribui os devidos valores ao vetor "direcao" */
	switch (mov)
	{
		case MOVER_DIREITA:
			destino[0] = jogador->pos_x + 1;
			destino[1] = jogador->pos_y;
			break;
		
		case MOVER_ESQUERDA:
			destino[0] = jogador->pos_x - 1;
			destino[1] = jogador->pos_y;
			break;
		
		case MOVER_CIMA:
			destino[0] = jogador->pos_x;
			destino[1] = jogador->pos_y - 1;
			break;
		
		case MOVER_BAIXO:
			destino[0] = jogador->pos_x;
			destino[1] = jogador->pos_y + 1;
			break;
	}
	
	
	/* verifica se as coordenadas de destino estão livres */
	verifica_permissao_movimento(destino, mov, labirinto, jogador);
}
/****************************************************/


/**
 * @brief Salva no vetor "passos", da estrutura tJOGADOR, a posição corrente do jogador.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void salva_posicao(tJOGADOR *jogador)
{
	
	/* Se não houver mais espaço no vetor "passos", aloca mais memória */
	if ((jogador->caminho.tamanho) == (jogador->caminho.capacidade))
	{
		aloca_memoria_passos(jogador, jogador->caminho.tamanho * 2);
	}
	
	
	jogador->caminho.passos[jogador->caminho.tamanho][0] = jogador->pos_x;
	jogador->caminho.passos[jogador->caminho.tamanho][1] = jogador->pos_y;
	jogador->caminho.tamanho++;
}
/****************************************************/





/**
 * @brief Mostra os passos realizados pelo jogador.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
 *
*/
void mostra_passos(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	register unsigned int i = 0;
	FILE *fp;
	
	fp = abrir_arquivo(labirinto->out_file, "a");
		
	for (i = 0; i < jogador->caminho.tamanho; i++)
	{
		printw("(%d:%d)%s", jogador->caminho.passos[i][0], jogador->caminho.passos[i][1], ((i < (jogador->caminho.tamanho - 1)) ? " : " : ""));
		
		if (strcmp(labirinto->out_file, "stdout") != 0)
		{
			fprintf(fp, "(%d:%d)%s", jogador->caminho.passos[i][0], jogador->caminho.passos[i][1], ((i < (jogador->caminho.tamanho - 1)) ? " : " : ""));
		}
	}
	
	fechar_arquivo(fp);
}
/**********************************************/
