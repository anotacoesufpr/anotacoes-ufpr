/*
 * Pacote.h
 *
 */

#ifndef PACOTE_H_
#define PACOTE_H_


#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring>
#include <sstream>


// 0111 1110 em hexadecimal
#define MARCA 0x7e

#define ERR_SEQ   0x1
#define ERR_MARCA 0x2


#define TAM_SEQ 4
#define TAM_TIPO 4



/**
 * Macros para definir sequências próxima e anterior
 */
#define ProxSequencia(seq) (((seq) + 1) % 16 ) // Realiza a sequencicao de
#define AntSequencia(seq) (((seq) + 15) % 16 ) // 3 bits (8 possibilidades).


// Tipos de mensagens aceitas pelo protocolo
#define TIPO_ACK 1 // Ack.
#define TIPO_NACK 2 // Nack.
#define TIPO_DADOS 3 // Dados.
#define TIPO_INIT_TRANS 4 // início de transmissão
#define TIPO_EOF 5 // Fim de tranmissão de arquivo
#define TIPO_PRINT 6 // exibe na tela
#define TIPO_ERR 7 // Erro
#define TIPO_FOPEN 8 // Abrir arquivo
#define TIPO_CD 9 // CD
#define TIPO_LS 10 // LS
#define TIPO_APPEND 11 // append
#define TIPO_EDIT 12 // editar
#define TIPO_NUM_LINHA 13 // número da linha a ser editada
#define TIPO_SAIR 14 // sair do programa



#define TEMPO_TIMEOUT 1000 // (em ms)
#define NUM_TENTATIVAS 20 // Numero maximo de tentativas




#define TAM_DADOS 251 // (em bytes).
#define TAM_MSG   255


typedef unsigned char uchar;



using namespace std;


class Pacote
{
private:
	uchar Tamanho;
	uchar Sequencia;
	uchar Tipo;
	string dado;
	uchar CRC;


public:
	Pacote();
	Pacote( uchar tamanho, uchar sequencia, uchar tipo, string dado );
	virtual ~Pacote();
	static bool Exibir( Pacote *pack );
	static uchar Paridade( string str );
	static void LimpaPacote( Pacote *pack );
	static bool String2Pacote( uchar *, Pacote * );
	static bool Pacote2String( Pacote *, uchar * );
	uchar getCRC() const;
	string getDado() const;
	uchar getSequencia() const;
	uchar getTamanho() const;
	uchar getTipo() const;
	void setCRC( uchar CRC );
	void setDado( string dado );
	void setSequencia( uchar Sequencia );
	void setTamanho( uchar Tamanho );
	void setTipo( uchar Tipo );
};

#endif
