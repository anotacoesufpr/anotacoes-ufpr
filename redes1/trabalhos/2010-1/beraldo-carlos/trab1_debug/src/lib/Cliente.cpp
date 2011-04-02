/**
 * @file src/lib/Cliente.cpp
 */


#include "Cliente.h"
#include <cstdio>

Cliente::Cliente()
{
	if ( !isRoot() )
	{
		cerr << "Você precisa ser root para rodar a aplicação" << endl;
		exit( 1 );
	}

	uchar paridade;
	Pacote *rec; /* pacote recebido */
	string comando, cmd;
	Conexao *Con = new Conexao(); /* */
	Comandos *Cmd = new Comandos(); /* */
	bool recebido, enviado;
	int tentativasRecebimento = 0;
	int linhaEdit = 0; // linha que será editada (inicia em zero devido do IF da linha 134)

	while ( !cin.eof() )
	{
		cout << endl;
		cout << PROMPT;
		getline( cin, comando );

		if ( ! Cmd->VerificarComando( comando ) )
		{
			/* Se o comando for inválido, volta a solicitar comando ao cliente */
			continue;
		}

		/* coloca em cmd o char do comando */
		istringstream s_comando( comando ); /* coloca o comando digitado numa stream de entrada */
		char cmd;
		string param;

		s_comando >> cmd;
		cmd = toupper( cmd );

		if ( cmd == 'Q' )
		{
			Cmd->Sair();
		}

		/* coloca em "param" o parâmetro do comando, se houver */
		if ( ! s_comando.eof() )
		{
			s_comando >> param;
		}

		/* o tamanho do pacote não pode ser 0, para o C++ não interpretar como \0 (byte nulo) */
		int tamanhoPacote = param.size() == 0 ? 1 : param.size();
		param = param.size() == 0 ? "B" : param; /* se nao houver dado, coloca um B só por farra e para ter tamDado == 1 */

		//cout << "Criando pacote: " << tamanhoPacote << " | 0 | "  << Cmd->IDComando( cmd ) << " | " << param << endl;

		/* O comando vai no Tipo. O parâmetro (se houver) vai no Dado */
		Pacote *pack = new Pacote( tamanhoPacote, 0, Cmd->IDComando( cmd ), param );

		ENVIO:
		if ( pack != NULL )
		{
//			do
//			{
				enviado = Protocolo::MandaPacote( Con, pack );
//			}
//			while ( !enviado );
		}


		do
		{
			do
			{
				cout << "Cliente.cpp: tentando receber pacote... No.= " << tentativasRecebimento << endl;
				rec = new Pacote();
				recebido = Protocolo::RecebePacote( Con, rec );
				tentativasRecebimento++;
			}
			while ( !recebido && tentativasRecebimento < 10  );

			if ( !recebido )
			{
				cout << "fazendo goto" << endl;
				tentativasRecebimento = 0;
				goto ENVIO;
			}

			cout << "Recebido: " << (int)rec->getTipo() << " | " << rec->getDado() << endl;

			paridade = Pacote::Paridade( rec->getDado() );

			if ( rec->getTipo() == TIPO_EOF )
			{
				//cout << "recebi EOF" << endl;
				break;
			}

			if ( rec->getTipo() != TIPO_ACK )
			{
				//cout << "Não é ACK. VOU entrar no IF..." << endl;
				if ( paridade == rec->getCRC() )
				{
					/* manda ACK somente se a paridade estiver certa e o pacote recebido não for um ACK do servidor */
					//cout << "Paridade OK. Mandarei ACK..." << endl;
					Protocolo::MandaACK( Con );
				}
				else
				{
					/* manda NACK */
					//cout << "Vou mandar NACK ... Paridade: " << paridade << " Paridade_Pacote " << rec->getCRC() << endl;
					Protocolo::MandaNACK( Con );
					continue;
				}
			}


			/* Verifica o tipo do pacote recebido */
			switch ( rec->getTipo() )
			{
				case TIPO_ACK:
					//cout << "Recebi ACK" << endl;

					// verifica se o ACK é uma resposta ao envio de um APPEND
					if ( pack != NULL )
					{
						if ( pack->getTipo() == TIPO_APPEND )
						{
							string dado;

							cout << "Dados a serem enviados: " << endl;
							getline( cin, dado );
							Protocolo::MandaString( Con, TIPO_DADOS, dado );
							pack = NULL;
						}
						else if ( pack->getTipo() == TIPO_EDIT )
						{
							// se ainda não definimos o número da linha a ser editada...
							if ( linhaEdit == 0 )
							{
								Pacote *pack_numLinha;
								cout << "Digite o número da linha a ser editada: ";
								scanf( "%d%*c", &linhaEdit );
								char charLinha[10];
								sprintf( charLinha, "%d", linhaEdit );
								string strLinha( charLinha );
								pack_numLinha = new Pacote( strLinha.length(), 0, TIPO_NUM_LINHA, strLinha );
								Protocolo::MandaPacote( Con, pack_numLinha );
								pack_numLinha = NULL;
							}
							else
							{
								string dadosLinha;
								cout << "Digite os novos dados da linha" << endl;
								getline( cin, dadosLinha );
								cout << "dado enviado: " << dadosLinha << endl;
								Protocolo::MandaString( Con, TIPO_DADOS, dadosLinha );
								pack = NULL;
								linhaEdit = 0;
							}
						}
					}

					rec = NULL;
					break;

				case TIPO_NACK:
					// reenvia o pacote e volta do loop
					cout << "Recebi NACK. Reenviando..." << endl;
					Protocolo::MandaPacote( Con, pack );
					//Protocolo::MandaEOF( Con );
					rec = NULL;
					continue;

				case TIPO_PRINT:
					cout << "--------------" << endl;
					cout << "Recebi TIPO_PRINT " << endl;
					cout << "--------------" << endl;
					Pacote::Exibir( rec );
					rec = NULL;
					break;

				case TIPO_ERR:
					cout << "ERRO: " << rec->getDado() << endl;
					break;
			}

		}
		while ( recebido );
	}


	delete Cmd;
	delete Con;
}
