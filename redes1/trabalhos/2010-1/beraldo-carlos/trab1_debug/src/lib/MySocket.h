/**
 * @file src/MySocket.h
 *
 * Definição da classe MySocket, com métodos personalizados para se trabalhar com sockets
 */

#ifndef MYSOCKET_H_
#define MYSOCKET_H_


#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netdb.h>

#include "SocketException.h"

/**
 * @class MySocket
 * Classe para criação de sockets. Possui todos os métodos com os mesmos nomes das respectivas funções em C (syscalls), com a diferença de que iniciam-se com \em underscore (_), a fim de evitar conflitos com a biblioteca padrão de sockets, e verificam a ocorrência de erros e disparam exceções. Logo, devem ser chamados dentro de blocos try/catch.
 */
class MySocket
{
	public:
		MySocket();
		static void test();
		static int _getaddrinfo( const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res) throw ( SocketException );
		static int _socket( int domain, int type, int protocol ) throw ( SocketException );
		static int _bind( int sockfd, const struct sockaddr *addr, socklen_t addrlen ) throw ( SocketException );
		static int _connect( int sockfd, const struct sockaddr *addr, socklen_t addrlen ) throw ( SocketException );
		static int _listen( int sockfd, int backlog ) throw ( SocketException );
		static int _accept( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) throw ( SocketException );
		static ssize_t _send( int sockfd, const void *buf, size_t len, int flags ) throw ( SocketException );
		static ssize_t _recv( int sockfd, void *buf, size_t len, int flags ) throw ( SocketException );
		static ssize_t _sendto( int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen ) throw ( SocketException );
		static ssize_t _recvfrom( int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen ) throw ( SocketException );
		static int _close( int fd ) throw ( SocketException );
		static int _shutdown( int sockfd, int how ) throw ( SocketException );
		static int _getpeername( int sockfd, struct sockaddr *addr, socklen_t *addrlen ) throw ( SocketException );
		static int _gethostname( char *name, size_t len ) throw ( SocketException );

};


#endif /* MYSOCKET_H_ */
