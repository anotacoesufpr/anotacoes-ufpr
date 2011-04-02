/**
 * Arquivo com implementações de funções de uso geral
 * @file src/lib/Util.cpp
*/

#include "Util.h"

/**
 * Verifica se o usuário é root
 */
bool isRoot()
{
	int uid = (int) getuid();

	if ( uid == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool file_exists( string filename )
{
	FILE *fp;

	if ( ( fp = fopen( filename.c_str() , "r" ) ) == NULL )
	{
		switch ( errno )
		{
			case ENOENT:
				return false;
				break;
		}
	}

	fclose(fp);

	return true;
}



bool is_readable( string filename )
{
	FILE *fp;

	if ( ( fp = fopen( filename.c_str() , "r" ) ) == NULL )
	{
		switch ( errno )
		{
			case EACCES:
				return false;
				break;
		}
	}

	fclose(fp);

	return true;
}



bool is_writeable( string filename )
{
	FILE *fp;

	if ( ( fp = fopen( filename.c_str() , "r" ) ) == NULL )
	{
		switch ( errno )
		{
			case EROFS:
				return false;
				break;
		}
	}

	fclose(fp);

	return true;
}



/**
 * Ao receber o nome do arquivo, verifica se ele existe e se possui permissão de escrita.
 * @return TRUE ou FALSE
 */
bool VerificaExistenciaEscrita( string filename )
{
	if ( !file_exists( filename ) )
	{
		string errStr = "O arquivo '" + filename + "' não existe";
		throw( errStr );
		return false;
	}

	if ( !is_writeable( filename ) )
	{
		string errStr = "O arquivo '" + filename + "' não tem permissão de escrita";
		throw( errStr );
		return false;
	}

	return true;
}



bool ExisteLinha( int N, string filename )
{
	FILE *fp;
	string comando = "cat " + filename + " | wc -l";
	int linhas;

	if ( ( fp = popen( comando.c_str(), "r" ) ) == NULL )
	{
		cerr << "Erro ao abrir processo" << endl;
		return false;
	}

	fscanf( fp, "%d", &linhas );

	pclose( fp );

	printf(  "N= %d | linhas = %d\n\n", N, linhas );

	if ( N <= linhas )
	{
		return true;
	}

	return false;
}


