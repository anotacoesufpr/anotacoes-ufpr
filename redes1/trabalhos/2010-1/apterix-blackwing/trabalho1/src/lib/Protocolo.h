/**
 * Arquivo com definições de constantes, macros e a classe que representam o protocolo implementado
 * @file src/lib/Protocolo.h
 */

#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_


#include <cstdlib>
#include <memory.h>
#include <sys/poll.h>
#include <poll.h>
#include <arpa/inet.h>
#include <string>

#include "Pacote.h"
#include "Conexao.h"



using namespace std;



class Protocolo
{
	public:
		Protocolo();
		static bool MandaPacote( Conexao *, Pacote * );
		static bool RecebePacote( Conexao *,  Pacote * );
		static bool MandaString( Conexao *, uchar, string );
		static bool MandaACK( Conexao * );
		static bool MandaNACK( Conexao * );
		static bool MandaEOF( Conexao * );
		static bool MandaErro( Conexao *, string );
};

#endif
