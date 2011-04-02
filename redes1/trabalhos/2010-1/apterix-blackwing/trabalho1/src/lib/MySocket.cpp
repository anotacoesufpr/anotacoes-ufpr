/**
 * @file src/MySocket.cpp
 *
 * Possui aa implementações dos métodos da classe MySocket
 */


#include "MySocket.h"
#include "SocketException.h"


MySocket::MySocket()
{

}
/*---------------------------------___*/


void MySocket::test()
{
	throw SocketException( "getaddrinfo" );
}




int MySocket::_getaddrinfo( const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
	throw ( SocketException )
{
	int returnValue;
	
	if ( ( returnValue = getaddrinfo( node, service, hints, res ) ) != 0 )
	{
		throw SocketException( __FUNCTION__, returnValue );
	}
	
	return returnValue;
}
/*----------------------------*/


int MySocket::_socket( int domain, int type, int protocol )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = socket( domain, type, protocol ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*-------------------------*/



int MySocket::_bind( int sockfd, const struct sockaddr *addr, socklen_t addrlen )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = bind( sockfd, addr, addrlen ) ) == -1 )
	{	
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*---------------------------------*/



int MySocket::_connect( int sockfd, const struct sockaddr *addr, socklen_t addrlen )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = connect( sockfd, addr, addrlen ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*-----------------------------*/



int MySocket::_listen( int sockfd, int backlog )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = listen( sockfd, backlog ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*---------------------------------------------*/



int MySocket::_accept( int sockfd, struct sockaddr *addr, socklen_t *addrlen )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = accept( sockfd, addr, addrlen ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*---------------------------------------*/



ssize_t MySocket::_send( int sockfd, const void *buf, size_t len, int flags )
	throw ( SocketException )
{
	ssize_t ret;
	
	if ( ( ret = send( sockfd, buf, len, flags ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*----------------------------------------*/



ssize_t MySocket::_recv( int sockfd, void *buf, size_t len, int flags )
	throw ( SocketException )
{
	ssize_t ret;
	
	if ( ( ret = recv( sockfd, buf, len, flags ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*--------------------------------*/



ssize_t MySocket::_sendto( int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen )
	throw ( SocketException )
{
	ssize_t ret;
	
	if ( ( ret = sendto( sockfd, buf, len, flags, dest_addr, addrlen ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*-----------------------------*/



ssize_t MySocket::_recvfrom( int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen )
	throw ( SocketException )
{
	ssize_t ret;
	
	if ( ( ret = recvfrom( sockfd, buf, len, flags, src_addr, addrlen ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*-------------------------------*/



int MySocket::_close( int fd )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = close( fd ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*-----------------------------*/


int MySocket::_shutdown( int sockfd, int how )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = shutdown( sockfd, how ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*------------------------------*/



int MySocket::_getpeername( int sockfd, struct sockaddr *addr, socklen_t *addrlen )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = getpeername( sockfd, addr, addrlen ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*-------------------------------*/


int MySocket::_gethostname( char *name, size_t len )
	throw ( SocketException )
{
	int ret;
	
	if ( ( ret = gethostname( name, len ) ) == -1 )
	{
		throw SocketException( __FUNCTION__ );
	}
	
	return ret;
}
/*--------------------------------*/
