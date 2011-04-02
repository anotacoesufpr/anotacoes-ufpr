/*
 * Protocolo.cpp
 *
 */

#include "Protocolo.h"

Protocolo::Protocolo()
{

}


/**
 * Este método envia um único pacote
 */
bool Protocolo::MandaPacote( Conexao *conexao, Pacote *pack )
{
	uchar mensagem[TAM_MSG];
	int enviados;
	struct pollfd pfd;
	int pollRet;
	int numTentativas = 0; // número  de tentativas de recebimento/envio

	pfd.fd = conexao->getSocket();
	pfd.events = POLLOUT;

	Pacote::Pacote2String( pack , mensagem );

	do
	{
		pollRet = poll( &pfd, 1, TEMPO_TIMEOUT );
		if ( pollRet > 0 )
		{
			if ( (pfd.revents & POLLOUT) || (pfd.revents & POLLIN)  )
			{
				try
				{
					enviados = MySocket::_send( conexao->getSocket(), mensagem, TAM_MSG, 0 );
				}
				catch ( SocketException &e )
				{
					cerr << e.what() << endl ;
					return false;
				}
			}
		}
		else if ( pollRet == -1 )
		{
			cerr << "Erro em " << __FILE__ << ":" << __LINE__ << ": pollRet < 0" << endl;
			return false;
		}


		numTentativas++;
	}
	while ( ( pollRet == 0 ) && (numTentativas < NUM_TENTATIVAS) );

	// se atingir o número de tentativas e pollRet ainda for zero, a conexão foi perdida
	/*if ( pollRet == 0 )
	{
		cerr << "Erro em " << __FILE__ << ":" << __LINE__ << ": Conexão perdida" << endl;
		return false;
		//exit( 1 );
	}*/

	return true;
}


/**
 * Este método recebe um único pacote
 */
bool Protocolo::RecebePacote( Conexao *conexao,  Pacote *pack )
{
	uchar buffer[TAM_MSG];
	int recebidos;

	struct pollfd pfd;
	int pollRet;
	int numTentativas = 0; // número  de tentativas recebimento/envio

	pfd.fd = conexao->getSocket();
	pfd.events = POLLIN ;

	do
	{
		pollRet = poll( &pfd, 1, TEMPO_TIMEOUT );

		if ( pollRet > 0 )
		{
			if ( pfd.revents & POLLIN )
			{
				try
				{
					recebidos = MySocket::_recv( conexao->getSocket(), buffer, TAM_MSG, 0 );
				}
				catch ( SocketException &e )
				{
					cerr << e.what() << endl ;
					return false;
				}
			}
		}
		else if ( pollRet == -1 )
		{
			cerr << "Erro em " << __FILE__ << ":" << __LINE__ << ": pollRet < 0" << endl;
			return false;
		}

		numTentativas++;
	}
	while ( pollRet == 0 && numTentativas < NUM_TENTATIVAS );

	// se atingir o número de tentativas e pollRet ainda for zero, a conexão foi perdida
	/*if ( pollRet == 0 )
	{
		cerr << "Erro em " << __FILE__ << ":" << __LINE__ << ": Conexão perdida" << endl;
		return false;
		//exit( 1 );
	}*/

	// Como o pacote recebido pode não ser para o programa,
	// retorna-se o retorno de String2Pacote, que verifica a MARCA
	return pack->String2Pacote( buffer , pack );
}


/**
 * Este método envia uma string. Ele a divide em pacotes e chama o método MandaPacote
 */
bool Protocolo::MandaString( Conexao *Con, uchar Tipo, string mensagem )
{
	Pacote *pack, *rec;
	string strEnvio; // string que será enviada a cada iteração do loop
	bool continuaEnvio = true;
	bool recebido; // verifica se recebeu um pacote válido
	bool enviado;
	uchar seqAtual = 0; // sequência atual do envio


	while ( continuaEnvio )
	{
		int tamanhoCopia = mensagem.size() > TAM_DADOS ? TAM_DADOS : mensagem.size();
		strEnvio = mensagem.substr( 0, tamanhoCopia);

		pack = new Pacote( strEnvio.size(), seqAtual, Tipo, strEnvio );

		do
		{
			enviado = Protocolo::MandaPacote( Con, pack );
		}
		while ( !enviado );

		do
		{
			rec = new Pacote();
			recebido = Protocolo::RecebePacote( Con, rec );
		}
		while( !recebido );

		if ( rec->getTipo() != TIPO_ACK )
		{
			continue;
		}

		// ACK recebido. Prepara o envio da próxima sequencia

		mensagem.erase( 0, tamanhoCopia );

		if ( mensagem.size() > 0 )
		{

			seqAtual = ProxSequencia( seqAtual );
			pack = NULL;
		}
		else
		{
			continuaEnvio = false;
		}
	}

	// após toda a trsnmissão, envia-se um fim de transmissãp
	Protocolo::MandaEOF( Con );

	return true;
}


bool Protocolo::MandaACK( Conexao *Con )
{
	Pacote *pack = new Pacote( 1, 0, TIPO_ACK, "Y" );
	Protocolo::MandaPacote( Con, pack );

	delete pack;

	return true;
}


bool Protocolo::MandaNACK( Conexao *Con )
{
	Pacote *pack = new Pacote( 1, 0, TIPO_NACK, "N" );
	Protocolo::MandaPacote( Con, pack );

	delete pack;

	return true;
}

/**
 * Manda um pacote que sinaliza fim de transmissao
 */
bool Protocolo::MandaEOF( Conexao *Con )
{
	Pacote *pack = new Pacote( 1, 0, TIPO_EOF, "Z" );
	Protocolo::MandaPacote( Con, pack );

	delete pack;

	return true;
}




/**
 * Manda um pacote com mensagem de erro
 */
bool Protocolo::MandaErro( Conexao *Con, string errStr )
{
	Pacote *pack = new Pacote( errStr.size(), 0, TIPO_ERR, errStr );
	Protocolo::MandaPacote( Con, pack );
	Protocolo::MandaEOF( Con );

	delete pack;

	return true;
}




