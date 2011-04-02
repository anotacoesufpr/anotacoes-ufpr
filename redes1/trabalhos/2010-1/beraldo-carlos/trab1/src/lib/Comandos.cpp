/**                                                                                                                                 /*
 * @file src/lib/Comandos.cpp
 */

#include "Comandos.h"

Comandos::Comandos()
{
	// inicia o vetor com os comandos aceitos
	this->comandosAceitos.push_back( 'L' );
	this->idComandos.push_back( TIPO_LS );

	this->comandosAceitos.push_back( 'C' );
	this->idComandos.push_back( TIPO_CD );

	this->comandosAceitos.push_back( 'F' );
	this->idComandos.push_back( TIPO_FOPEN );

	this->comandosAceitos.push_back( 'A' );
	this->idComandos.push_back( TIPO_APPEND );

	this->comandosAceitos.push_back( 'W' );
	this->idComandos.push_back( TIPO_EDIT );

	this->comandosAceitos.push_back( 'Q' );
	this->idComandos.push_back( TIPO_SAIR );
}


/**
 * Retorna o ID de um comando
 */
int Comandos::IDComando( char cmd )
{
	cmd = toupper( cmd );

	for ( int i = 0, total = this->comandosAceitos.size(); i < total; i++ )
	{
		if ( this->comandosAceitos.at( i ) == cmd )
		{
			return this->idComandos.at( i );
		}
	}

	return 0;
}


/**
 * Sai do programa
 */
void Comandos::Sair()
{
	cout  <<  "\n Volte sempre! =) \n" << endl;
	exit( 0 );
}


/**
 * Verifica se o comando digitado é válido
 */
bool Comandos::VerificarComando( string comando )
{
	bool valido = false;
	char cmd;

	// não pode ser usado pipeline e redirecionamento nos comandos
	if ( comando.find( "|" ) != string::npos || comando.find( ">" ) != string::npos || comando.find( "<" ) != string::npos )
	{
		cerr << "Não é permitido usar Pipeline ou Redirecionamento no comando!" << endl;
		return false;
	}

	// coloca em "cmd" o comando digitado, sem parâmetros
	istringstream s_comando( comando );
	s_comando >> cmd;

	cmd = toupper( cmd );

	for ( int i = 0, total = (int)this->comandosAceitos.size(); i < total; i++ )
	{
		if ( cmd == this->comandosAceitos.at( i ) )
		{
			valido = true;
		}
	}

	if ( !valido )
	{
		cerr << "Comando inválido" << endl;
		this->ImprimirComandos();
		return false;
	}

	return true;
}


/**
 * Imprime os comandos que podem ser usados no programa
 */
void Comandos::ImprimirComandos()
{
	cout << "Comandos aceitos: ";

	for ( int i = 0, tamArr = (int) this->comandosAceitos.size(); i < tamArr; i++ )
	{
		cout << this->comandosAceitos.at( i ) << ", ";
	}

	cout << endl;
}


/**
 * Executa LS e manda o resultado ao cliente
 */
string Comandos::Ls( Conexao *Con )
{
	char buffer[ TAM_DADOS + 2 ]; // soma 2 para \n e \0
	ostringstream saidaComando;
	FILE *fp;

	if ( ( fp = popen( "ls", "r" ) ) == NULL )
	{
		cerr << "Erro ao executar popen para fazer ls" << endl;
		return false;
	}

	while ( fgets( buffer, TAM_DADOS, fp ) )
	{
		saidaComando << buffer;
	}

	pclose( fp );

	return saidaComando.str();
}


/**
 * Faz um CD no diretório atual do servidor para o diretório "path"
 */
bool Comandos::Cd( string path )
{
	if ( chdir( path.c_str() ) != 0 )
	{
		cerr << "Erro ao fazer CD para " << path << endl;
		return false;
	}

	return true;
}


/**
 * Retorna o conteúdo de um arquivo
 */
string Comandos::Fopen( string filename )
{
	char buffer[ TAM_DADOS + 2 ]; // soma 2 para \n e \0
	ostringstream saidaComando;
	FILE *fp;
	string comando = "cat -n " + filename;


	if ( !file_exists( filename ) )
	{
		string errStr = "Arquivo '" + filename + "' não existe";
		throw ( errStr );
		return false;
	}

	if ( !is_readable( filename ) )
	{
		string errStr = "Arquivo '" + filename + "' não possui permissão de leitura";
		throw ( errStr );
		return false;
	}


	if ( ( fp = popen( comando.c_str(), "r" ) ) == NULL )
	{
		cerr << "Erro ao executar popen para fazer cat" << endl;
		return false;
	}

	while ( fgets( buffer, TAM_DADOS, fp ) )
	{
		saidaComando << buffer;
	}

	pclose( fp );

	return saidaComando.str();
}






/**
 * Faz o APPEND no arquivo
 */
bool Comandos::Append( string filename, string dado )
{
	FILE *fp;

	if ( ( fp = fopen( filename.c_str(), "a" ) ) == NULL )
	{
		cerr << "Erro ao abrir o arquivo " + filename + " para fazer append";
		return false;
	}

	fprintf( fp, "%s\n", dado.c_str() );

	fclose( fp );

	return true;
}



bool Comandos::Edit( string filename, int linhaEditada, string dado )
{
	FILE *fp_tmp; // arquivo onde serão salvas as novas linhas
	FILE *fp_orig;
	int TAM_LINHA = 500;
	char linha[TAM_LINHA];
	string nomeArqTemp = "file_tmp";
	int cont = 1;

	if ( ( fp_tmp = fopen( nomeArqTemp.c_str(), "w" )  ) == NULL )
	{
		cerr << "Erro ao abrir arquivo temporário para escrita" << endl;
		return false;
	}

	if ( ( fp_orig = fopen( filename.c_str(), "r" )  ) == NULL )
	{
		cerr << "Erro ao abrir arquivo original para leitura" << endl;
		return false;
	}


	// edita as linhas de 1 até "linhaEditada"
	while ( cont < linhaEditada )
	{
		fgets( linha, TAM_LINHA, fp_orig );
		fprintf( fp_tmp, "%s", linha );
		cont++;
	}


	// escreve a nova linha
	fprintf( fp_tmp, "%s\n", dado.c_str() );

	// descarta a linha editada
	fgets( linha, TAM_LINHA, fp_orig );

	while ( fgets( linha, TAM_LINHA, fp_orig ) != NULL )
	{
		fprintf( fp_tmp, "%s", linha );
	}

	fclose( fp_tmp );
	fclose( fp_orig );

	rename( nomeArqTemp.c_str(), filename.c_str() );

	return true;
}



