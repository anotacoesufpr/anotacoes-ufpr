/*
 * Comandos.h
 *
 */

#ifndef COMANDOS_H_
#define COMANDOS_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <string>
#include <cctype>
#include <vector>
#include <unistd.h>

#include "Pacote.h"
#include "Conexao.h"
#include "Protocolo.h"
#include "Util.h"


/**
 * String que será exeibida ao solicitar um comando
 */
#define PROMPT "CMD>"


using namespace std;

class Comandos
{
private:
	/**
	 * Vetor com as strings dos comandos aceitos pelo programa
	 *
	 * Esse vetor é preenchido no construtor. Por isso é necessário instanciar esta classe com new
	 */
	vector<char> comandosAceitos;

	/**
	 * Vetor com os ID's dos comandos aceitos
	 */
	vector<int> idComandos;

public:
	Comandos();
	int IDComando( char );
	void Sair();
	bool VerificarComando( string );
	void ImprimirComandos();
	string Ls( Conexao * );
	bool Cd( string );
	string Fopen( string );
	bool Append( string filename, string dado );
	bool Edit( string filename, int linhaEditada, string dado );
};

#endif
