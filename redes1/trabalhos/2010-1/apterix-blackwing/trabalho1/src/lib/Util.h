/**
 * Arquivo com cabeçalhos de funções de uso geral
 * @file src/lib/Util.h
*/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <exception>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

/**
 * Verifica se queme stá executando o programa é root
 * @return Retorna TRUE se for root, ou false caso contrário
*/
bool isRoot();



/**
 * Verifica se o arquivo existe
 */
bool file_exists( string filename );


/**
 * Verifica se o arquivo possui permissão de leitura
 */
bool is_readable( string );


/**
 * Verifica se o arquivo possui permissão de escrita
 */
bool is_writeable( string );

/**
 * Verfifica se o arquivo existe e se tem permissão de escrita
 */
bool VerificaExistenciaEscrita( string filename );


/*
 * Verifica se existe a linha N no arquivo filename
 */
bool ExisteLinha( int N, string filename );


#endif
