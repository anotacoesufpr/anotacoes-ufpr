/*
 * Conexao.h
 *
 */

#ifndef CONEXAO_H_
#define CONEXAO_H_


#include "RawSocket.h"


using namespace std;



class Conexao
{
	private:
		int socket;

	public:
		Conexao();
		Conexao( int socket );
		void FecharConexao( Conexao * );
		int getSocket() const;
		void setSocket( int );

};

#endif
