/**
 * @file src/lib/Servidor.cpp
 */

#include "Servidor.h"

Servidor::Servidor()
{
	if ( !isRoot() )
	{
		cerr << "Você precisa ser root para rodar a aplicação" << endl;
		exit( 1 );
	}

	Conexao *Con = new Conexao();
	Pacote *pack = new Pacote();
	Pacote *packAnterior = new Pacote(); // impede que o comando atual seja igual ao enterior, devido a um bug com o buffer da placa de rede
	Comandos *Cmd = new Comandos();
	string retornoComando;
	bool encerrarTransmissao = false;
	bool recebido;
	uchar paridade;
	int tipoResposta = 0; // usado para identificar se o servidor está aguardando resposta para APPEND ou EDIT ou nenhum deles
	string nomeArquivo; // nome do arquivo para APPEND ou EDIT
	int linhaEdicao = 0; // número da linha que será editada



	while ( !encerrarTransmissao )
	{
		do
		{
			recebido = Protocolo::RecebePacote( Con, pack );;
		}
		while ( !recebido );

		if ( pack->getTipo() == TIPO_EOF )
		{
			// se o servidor receber um EOF depois de terminar o APPEND, manda um EOF ao cliente
			if ( tipoResposta == TIPO_APPEND )
			{
				tipoResposta = 0;
				Protocolo::MandaEOF( Con );
			}
			else if ( tipoResposta == TIPO_EDIT )
			{
				tipoResposta = 0;
				Protocolo::MandaEOF( Con );
			}
			else
			{
				continue;
			}
		}

		paridade = Pacote::Paridade( pack->getDado() );

		if ( pack->getTipo() != TIPO_ACK && pack->getTipo() != TIPO_APPEND && pack->getTipo() != TIPO_EDIT && pack->getTipo() != TIPO_NUM_LINHA )
		{
			if ( paridade == pack->getCRC() )
			{
				// manda ACK somente se a paridade estiver certa e o pacote recebido não for um ACK do servidor
				Protocolo::MandaACK( Con );
			}
			else
			{
				// manda NACK
				Protocolo::MandaNACK( Con );
				continue;
			}
		}


		switch ( pack->getTipo() )
		{
			case TIPO_LS:
				retornoComando = Cmd->Ls( Con );
				Protocolo::MandaString( Con, TIPO_PRINT, retornoComando );
				break;

			case TIPO_CD:
				Cmd->Cd( pack->getDado() );
				Protocolo::MandaEOF( Con );
				break;

			case TIPO_FOPEN:
				try
				{
					retornoComando = Cmd->Fopen( pack->getDado() );
				}
				catch ( string e )
				{
					Protocolo::MandaErro( Con, e );
					break;
				}
				Protocolo::MandaString( Con, TIPO_PRINT, retornoComando );
				break;

			case TIPO_APPEND:
				nomeArquivo = pack->getDado();
				tipoResposta = TIPO_APPEND;
				try
				{
					VerificaExistenciaEscrita( nomeArquivo );
				}
				catch ( string e )
				{
					Protocolo::MandaErro( Con, e );
					break;
				}

				Protocolo::MandaACK( Con );

				// após a verificação inicial, volta a escutar, para receber o dado a ser inserido
				break;

			case TIPO_EDIT:
				nomeArquivo = pack->getDado();
				tipoResposta = TIPO_EDIT;

				try
				{
					VerificaExistenciaEscrita( nomeArquivo );
				}
				catch ( string e )
				{
					Protocolo::MandaErro( Con, e );
					break;
				}

				Protocolo::MandaACK( Con );

				break;

			case TIPO_NUM_LINHA:
				if ( ExisteLinha( atoi( pack->getDado().c_str() ), nomeArquivo ))
				{
					linhaEdicao = atoi( pack->getDado().c_str() );
				}
				else
				{
					Protocolo::MandaErro( Con, "Linha não existe" );
					break;
				}

				Protocolo::MandaACK( Con );
				break;


			case TIPO_DADOS:
				// Se receber TIPO_DADOS, é resposta a um APPEND ou EDIT
				if ( tipoResposta == TIPO_APPEND )
				{
					Cmd->Append( nomeArquivo, pack->getDado() );
				}
				else if ( tipoResposta == TIPO_EDIT )
				{
					Cmd->Edit( nomeArquivo, linhaEdicao, pack->getDado() );
				}

				break;
		}
	}
}
