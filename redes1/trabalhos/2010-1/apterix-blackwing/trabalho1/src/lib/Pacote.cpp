/*
 * Pacote.cpp
 *
 */

#include "Pacote.h"

Pacote::Pacote()
{

}


Pacote::Pacote( uchar tamanho, uchar sequencia, uchar tipo, string dado )
{
	this->setTamanho( tamanho );
	this->setSequencia( sequencia );
	this->setTipo( tipo );
	this->setDado( dado );
	this->setCRC( this->Paridade( dado ) );
}


Pacote::~Pacote()
{

}




/**
 * Exibe na tela o conteúdo de um pacote
 */
bool Pacote::Exibir( Pacote *pack )
{
	cout << pack->getDado() ;

	return true;
}



uchar Pacote::Paridade( string str )
{
	int i, tam = str.size();
	uchar paridade = 0;

	for ( i = 0; i < tam; i++ )
	{
		paridade ^= str[i]; // XOR
	}

	return paridade;
}


void Pacote::LimpaPacote( Pacote * pack )
{
	pack->dado.clear();
	pack->setTamanho( 0 );
}


// Transforma um pacote em string.
bool Pacote::Pacote2String( Pacote *pack, uchar * mensagem )
{
	int i;
	uchar paridade, TipoSeq; // TipoSeq é o byte que une TIpo e Sequencia

	TipoSeq = ( ( pack->getSequencia() & 0xF ) << 4) | ( pack->getTipo() & 0xF );

	mensagem[0] = MARCA;
	mensagem[1] = pack->getTamanho();
	mensagem[2] = TipoSeq;

	string dados = pack->getDado();
	paridade = Pacote::Paridade( dados );

	for ( i = 0; i < pack->getTamanho(); i++ )
	{
		mensagem[i + 3] = ( dados.at( i ) );
	}

	mensagem[i + 3] = paridade;

	return true;
}


// Transforma uma string em um pacote.
bool Pacote::String2Pacote( uchar * mensagem, Pacote *pack )
{
	int i;
	uchar paridade;
	string dado;

	if ( mensagem[0] != MARCA )
	{
		// O pacote não é iniciado pela MARCA
		return false;
	}

	pack->setTamanho( mensagem[1] );
	pack->setSequencia( ( mensagem[2] >> 4 ) & 0xF );
	pack->setTipo( mensagem[2] & 0xF );

	if ( pack->getTamanho() > 0 )
	{
		for ( i = 0; i < pack->getTamanho(); i++ )
		{
			dado.operator += ( mensagem[ i + 3 ] );
		}

		paridade = Pacote::Paridade( dado );

		// Verifica paridade.
		if ( mensagem[ pack->getTamanho() + 3 ] != paridade )
		{
			cerr << "Erro de sequencia" << endl;
			return false;
		}

		pack->setCRC( paridade );
	}
	else
	{
		dado.operator += ( "" );
	}

	pack->setDado( dado );

	return true;
}


uchar Pacote::getCRC() const
{
	return CRC;
}

string Pacote::getDado() const
{
	return dado;
}


uchar Pacote::getSequencia() const
{
	return Sequencia;
}

uchar Pacote::getTamanho() const
{
	return Tamanho;
}

uchar Pacote::getTipo() const
{
	return Tipo;
}

void Pacote::setCRC( uchar CRC )
{
	this->CRC = CRC;
}

void Pacote::setDado( string dado )
{
	this->dado = dado;
}

void Pacote::setSequencia( uchar Sequencia )
{
	this->Sequencia = Sequencia;
}

void Pacote::setTamanho( uchar Tamanho )
{
	this->Tamanho = Tamanho;
}

void Pacote::setTipo( uchar Tipo )
{
	this->Tipo = Tipo;
}
