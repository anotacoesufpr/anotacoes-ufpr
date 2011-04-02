/**
 * @file src/lib/RawSocket.h
 */

#ifndef RAWSOCKET_H
#define RAWSOCKET_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>  // Cabecalho Ethernet.
#include <net/if.h>        // Estrutura 'ifr'.
#include <netinet/in.h>    // Definicao de protocolos.
#include <sys/time.h>

#include "MySocket.h"
#include "Pacote.h"

using namespace std;

/**
 * Classe que cria RawSocket
 * Esta classe herda os métodos e propriedades da classe MySocket
 */
class RawSocket : public MySocket
{
	public:
		static int Rawsocket( const char * );
};

#endif
