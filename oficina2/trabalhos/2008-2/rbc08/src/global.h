#ifndef _GLOBAL_H_
#define _GLOBAL_H_




/*****************
*   Enumerações  *
*****************/

/**
 * @enum cores_curses
 * @brief Enumaração para ser usada na manipulação de cores da NCurses. 
 * O primeiro elemento deve ter o valor 1, pois init_pair() não aceita o número zero.
 * Exemplos:
 *   preto_no_branco -> fonte preta, fundo branco
 *   branco_no_preto -> fonte branca, fundo preto */
enum cores_curses
{
	preto_no_branco = 1,
	preto_no_azul,
	preto_no_verde,
	preto_no_vermelho,
	preto_no_amarelo,
	branco_no_preto,
	branco_no_azul,
	branco_no_vermelho,
	branco_no_verde,
	branco_no_amarelo,
	azul_no_branco,
	azul_no_preto,
	azul_no_vermelho,
	azul_no_verde,
	azul_no_amarelo,
	verde_no_vermelho,
	verde_no_azul,
	verde_no_branco,
	verde_no_preto,
	verde_no_amarelo,
	vermelho_no_branco,
	vermelho_no_preto,
	vermelho_no_azul,
	vermelho_no_verde,
	vermelho_no_amarelo,
	amarelo_no_azul,
	amarelo_no_vermelho,
	amarelo_no_verde,
	amarelo_no_preto,
	amarelo_no_branco
};



/**
 * @enum modo_de_jogo
 * @brief Modos de jogo. 0 = Modo Batch. 1 = Modo Interativo
*/
enum modo_de_jogo
{
	MODO_BATCH,
	MODO_INTERATIVO
};



/**
 * @enum movimentacoes
 * @brief Valores usados na movimentação do jogador no labirinto.
*/
enum movimentacoes
{
	MOVER_DIREITA,
	MOVER_ESQUERDA,
	MOVER_CIMA,
	MOVER_BAIXO
};





/************************
*  Estruturas (structs) *
*************************/


/**
 * @struct struc_caminho
 * @brief Estrutura que salva o caminho realizado pelo jogador.
*/
struct struct_caminho
{
	unsigned int capacidade; /**< Capacidade corrente do vetor "passos" */
	int tamanho; /**< Tamanho corrente do vetor "passos" */
	unsigned int **passos; /**< Vetor que armazena as posições X e Y dos passos do jogador. */
};



/**
 * @struct struct_labirinto
 * @brief Estrutura que armazena a matriz que representa o mapa, o tamanho do labirinto, as posições das portas, chaves e saída(s). Todos os elementos podem ocorrer mais de uma vez no labirinto, por isso suas posições são armazenadas em vetores.
*/
struct struct_labirinto
{
	char **mapa; /**< Matriz que representa o mapa do labirinto */
	unsigned int linhas; /**< Número de linhas do labirinto */
	unsigned int colunas; /**< Número de colunas do labirinto */
	char *in_file; /**< Arquivo de entrada, de onde será carregado o mapa do labirinto */
	char *out_file; /**< Arquivo onde será salva a saída do programa */
	unsigned int **saidas; /**< Vetor que armazena as posições X e Y das saídas do labirinto */
	unsigned int total_saidas; /**< Total de saídas do labirinto */
	unsigned int **portas_azuis; /**< Coordenadas X e Y das portas azuis */
	unsigned int total_portas_azuis; /**< Total de portas azuis */
	unsigned int **portas_vermelhas; /**< Coordenadas X e Y das portas vermelhas */
	unsigned int total_portas_vermelhas; /**< Total de portas vermelhas */
	unsigned int **portas_amarelas; /**< Coordenadas X e Y das portas amarelas */
	unsigned int total_portas_amarelas; /**< Total de portas amarelas */
	unsigned int **portas_verdes; /**< Coordenadas X e Y das portas verdes */
	unsigned int total_portas_verdes; /**< Total de portas verdes */
	unsigned int **chaves_azuis; /**< Coordenadas X e Y das chaves azuis */
	unsigned int total_chaves_azuis; /**< Total de chaves azuis */
	unsigned int **chaves_vermelhas; /**< Coordenadas X e Y das chaves vermelhas */
	unsigned int total_chaves_vermelhas; /**< Total de chaves vermelhas */
	unsigned int **chaves_amarelas; /**< Coordenadas X e Y das chaves amarelas */
	unsigned int total_chaves_amarelas; /**< Total de chaves amarelas */
	unsigned int **chaves_verdes;; /**< Coordenadas X e Y das chaves verdes */
	unsigned int total_chaves_verdes; /**< Total de chaves verdes */
};




/**
 * @struct struct_jogador
 * @brief Estrutura que armazena a posição do jogador, suas chaves, o raio de visão e o modo de jogo.
*/
struct struct_jogador
{
	unsigned int pos_x; /**< Posição X corrente do jogador */
	unsigned int pos_y; /**< Posição Y corrente do jogador */
	unsigned int raio_visao; /**< Raio de visão do jogador */
	struct struct_caminho caminho; /**< Estrutura que armazena os passos do jogador */
	unsigned short int game_mode; /**< Modo de jogo (interativo ou batch) */
	unsigned short int chave_azul; /**< Esta variável recebe 1 se o jogador possui chave azul */
	unsigned short int chave_vermelha; /**< Esta variável recebe 1 se o jogador possui chave vermelha */
	unsigned short int chave_amarela; /**< Esta variável recebe 1 se o jogador possui chave amarela */
	unsigned short int chave_verde; /**< Esta variável recebe 1 se o jogador possui chave verde */
};









/********************************
* Definições de tipo (typedef's *
********************************/


/**
 * @typedef struct struct_labirinto tLABIRINTO
*/
typedef struct struct_labirinto tLABIRINTO;



/**
 * @typedef struct struct_jogador tJOGADOR
*/
typedef struct struct_jogador tJOGADOR;






/*************************
* Protótipos de funçõess *
**************************/
void init_game(tLABIRINTO *labirinto, tJOGADOR *jogador);
void finish_game(tLABIRINTO *labirinto, tJOGADOR *jogador);
void inicia_curses();
void finaliza_curses();
void init_structs(tLABIRINTO *labirinto, tJOGADOR *jogador);
int parse_opt(int argc, char **argv, tLABIRINTO *labirinto, tJOGADOR *jogador);
void jogar(tLABIRINTO *labirinto, tJOGADOR *jogador);
void salva_posicao(tJOGADOR *jogador);




/****************************
* Constantes usadas no jogo *
****************************/


/*
 * Definição dos caracteres usados no jogo, como paredes, portas e chaves.
*/
#define CHAR_PAREDE '#'
#define CHAR_PORTA_ABERTA '_'
#define CHAR_LIVRE '.'
#define CHAR_JOGADOR '*'
#define CHAR_SAIDA 'X'
#define CHAR_PORTA_VERMELHA 'R'
#define CHAR_PORTA_AZUL 'B'
#define CHAR_PORTA_VERDE 'G'
#define CHAR_PORTA_AMARELA 'Y'
#define CHAR_CHAVE_VERMELHA 'r'
#define CHAR_CHAVE_AZUL 'b'
#define CHAR_CHAVE_VERDE 'g'
#define CHAR_CHAVE_AMARELA 'y'


/*
 * Número inicial de posições dos vetores que armazenam as posições das portas, chaves, passos e saída(s).
*/
#define NUM_POSICOES_VETORES 15



/*
 * Códigos ASC das teclas usadas no controle do jogo
*/
#define TECLA_P_UPPER 80
#define TECLA_P_LOWER 112
#define TECLA_Q_UPPER 81
#define TECLA_Q_LOWER 113
#define TECLA_S_UPPER 83
#define TECLA_S_LOWER 115
#define TECLA_0 48
#define TECLA_1 49
#define TECLA_2 50
#define TECLA_3 51
#define TECLA_4 52
#define TECLA_5 53
#define TECLA_6 54
#define TECLA_7 55
#define TECLA_8 56
#define TECLA_9 57
#define TECLA_SETA_CIMA KEY_UP
#define TECLA_SETA_BAIXO KEY_DOWN
#define TECLA_SETA_DIREITA KEY_RIGHT
#define TECLA_SETA_ESQUERDA KEY_LEFT




/*
 * Os valores abaixo definem o tamanho do terminal. Eles são usados para centralizar o mapa na tela
*/
#define LINHAS_TERMINAL 22
#define COLUNAS_TERMINAL 73



#endif


