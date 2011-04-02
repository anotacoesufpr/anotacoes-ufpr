/*
 * Conexao.cpp
 *
 */

#include "Conexao.h"

Conexao::Conexao()
{
	this->setSocket( RawSocket::Rawsocket( "eth0" ) );
}


Conexao::Conexao( int socket )
{
	this->setSocket( socket );
}


void Conexao::FecharConexao( Conexao *c )
{
	shutdown( c->getSocket(), 2 );
}



int Conexao::getSocket() const
{
	return socket;
}


void Conexao::setSocket(int socket)
{
	this->socket = socket;
}
