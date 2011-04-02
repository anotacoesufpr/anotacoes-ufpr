/**
 * @file src/SocketException.cpp
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <cerrno>

#include "SocketException.h"


SocketException::SocketException( string funcName, int returnValue  )
{
	functionName = funcName;
	errorCode = returnValue == 0 ? errno : returnValue;
	
	/* Verifica o nome da função onde ocorreu a exceção para chamar o método correspondente */
	if ( strcmp( funcName.c_str(), "_getaddrinfo" ) == 0 )
	{
		this->getaddrinfoException();
	}
	else if ( strcmp( funcName.c_str(), "_socket" ) == 0 )
	{
		this->socketException();
	}
	else if ( strcmp( funcName.c_str(), "_bind") == 0 )
	{
		this->bindException();
	}
	else if ( strcmp( funcName.c_str(), "_connect" ) == 0 )
	{
		this->connectException();
	}
	else if ( strcmp( funcName.c_str(), "_listen" ) == 0 )
	{
		this->listenException();
	}
	else if ( strcmp( funcName.c_str(), "_accept" ) == 0 )
	{
		this->acceptException();
	}
	else if ( strcmp( funcName.c_str(), "_send" ) == 0 )
	{
		this->sendException();
	}
	else if ( strcmp( funcName.c_str(), "_recv" ) == 0 )
	{
		this->recvException();
	}
	else if ( strcmp( funcName.c_str(), "_sendto" ) == 0 )
	{
		this->sendtoException();
	}
	else if ( strcmp( funcName.c_str(), "_recvfrom" ) == 0 )
	{
		this->recvfromException();
	}
	else if ( strcmp( funcName.c_str(), "_close" ) == 0 )
	{
		this->closeException();
	}
	else if ( strcmp( funcName.c_str(), "_shutdown" ) == 0 )
	{
		this->shutdownException();
	}
	else if ( strcmp( funcName.c_str(), "_getpeername" ) == 0 )
	{
		this->getpeernameException();
	}
	else if ( strcmp( funcName.c_str(), "_gethostname" ) == 0 )
	{
		this->gethostnameException();
	}
}
/*-------------------------------*/





const char* SocketException::what() const throw()
{
	string ret = "Exceção na função \"" + this->functionName + "\": " + msg.c_str();
	return ret.c_str();
}
/*-------------------------------*/



int SocketException::getaddrinfoException()
{
	switch ( this->errorCode )
	{
		case EAI_ADDRFAMILY:
			this->msg = "The specified network host does not have any network addresses in the requested address family.";
			break;

		case EAI_AGAIN:
			this->msg = "The name server returned a temporary failure indication.  Try again later.";
			break;

		case EAI_BADFLAGS:
			this->msg = "hints.ai_flags contains invalid flags; or, hints.ai_flags included AI_CANONNAME and name was NULL.";
			break;

		case EAI_FAIL:
			this->msg = "The name server returned a permanent failure indication.";
			break;

		case EAI_FAMILY:
			this->msg = "The requested address family is not supported.";
			break;

		case EAI_MEMORY:
			this->msg = "Out of memory.";
			break;

		case EAI_NODATA:
			this->msg = "The specified network host exists, but does not have any network addresses defined.";
			break;

		case EAI_NONAME:
			this->msg = "The node or service is not known; or both node and service are NULL; or AI_NUMERICSERV was specified in hints.ai_flags and service was not a numeric port-number string.";
			break;

		case EAI_SERVICE:
			this->msg = "The requested service is not available for the requested socket type.  It may be available through another socket type.  For example, this error could occur if service was \"shell\" (a service only available on stream sockets), and either hints.ai_protocol was IPPROTO_UDP, or hints.ai_socktype was SOCK_DGRAM;  or  the  error  could  occur  if  service  was  not  NULL,  and      hints.ai_socktype was SOCK_RAW (a socket type that does not support the concept of services).";
			break;

		case EAI_SOCKTYPE:
			this->msg = "The requested socket type is not supported.  This could occur, for example, if hints.ai_socktype and hints.ai_protocol are inconsistent (e.g., SOCK_DGRAM and IPPROTO_TCP, repectively).";
			break;

		case EAI_SYSTEM:
			this->msg = "Other system error, check errno for details.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}
	
	return errorCode;
}
/*------------------------*/


int SocketException::socketException()
{
	switch ( this->errorCode )
	{
		case EACCES:
			this->msg = "Permission to create a socket of the specified type and/or protocol is denied.";
			break;

		case EAFNOSUPPORT:
			this->msg = "The implementation does not support the specified address family.";
			break;

		case EINVAL:
			this->msg = "Unknown protocol, protocol family not available or invalid flags in type.";
			break;

		case EMFILE:
			this->msg = "Process file table overflow.";
			break;

		case ENFILE:
			this->msg = "The system limit on the total number of open files has been reached.";
		
		case ENOBUFS:
		case ENOMEM:
			this->msg = "Insufficient memory is available.  The socket cannot be created until sufficient resources are freed.";
			break;

		case EPROTONOSUPPORT:
			this->msg = "The protocol type or the specified protocol is not supported within this domain.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}
	
	return this->errorCode;
}
/*-------------------------------*/


int SocketException::bindException()
{
	switch ( this->errorCode )
	{
		case EACCES:
			this->msg = "The address is protected, and the user is not the superuser OR Search permission is denied on a component of the path prefix.  (See also path_resolution(7).)";
			break;

		case EADDRINUSE:
			this->msg = "The given address is already in use.";
			break;

		case EBADF:
			this->msg = "sockfd is not a valid descriptor.";
			break;

		case EINVAL:
			this->msg = "The socket is already bound to an address OR The addrlen is wrong, or the socket was not in the AF_UNIX family.";
			break;

		case ENOTSOCK:
			this->msg = "sockfd is a descriptor for a file, not a socket.";
			break;

		case EADDRNOTAVAIL:
			this->msg = "A nonexistent interface was requested or the requested address was not local.";
			break;

		case EFAULT:
			this->msg = "addr points outside the user's accessible address space.";
			break;

		case ELOOP:
			this->msg = "Too many symbolic links were encountered in resolving addr.";
			break;

		case ENAMETOOLONG:
			this->msg = "addr is too long.";
			break;

		case ENOENT:
			this->msg = "The file does not exist.";
			break;

		case ENOMEM:
			this->msg = "Insufficient kernel memory was available.";
			break;

		case ENOTDIR:
			this->msg = "A component of the path prefix is not a directory.";
			break;

		case EROFS:
			this->msg = "The socket inode would reside on a read-only file system.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}
	
	return this->errorCode;
}
/*-------------------------*/



int SocketException::connectException()
{
	switch ( this->errorCode )
	{
		case EACCES:
			this->msg = "For Unix domain sockets, which are identified by pathname: Write permission is denied on the socket file, or search permission is denied for one of the directories  in  the  path  prefix. (See also path_resolution(7).) OR The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule.";
			break;
              
		case EPERM:
			this->msg = "The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule.";
			break;

		case EADDRINUSE:
			this->msg = "Local address is already in use.";
			break;

		case EAFNOSUPPORT:
			this->msg = "The passed address didn't have the correct address family in its sa_family field.";
			break;

		case EAGAIN:
			this->msg = "No  more free local ports or insufficient entries in the routing cache.  For AF_INET see the description of /proc/sys/net/ipv4/ip_local_port_range ip(7) for information on how to increase the number of local ports.";
			break;

		case EALREADY:
			this->msg = "The socket is non-blocking and a previous connection attempt has not yet been completed.";
			break;

		case EBADF:
			this->msg = "The file descriptor is not a valid index in the descriptor table.";
			break;

		case ECONNREFUSED:
			this->msg = "No-one listening on the remote address.";
			break;

		case EFAULT:
			this->msg = "The socket structure address is outside the user's address space.";
			break;

		case EINPROGRESS:
			this->msg = "The socket is non-blocking and the connection cannot be completed immediately.  It is possible to select(2) or poll(2) for completion by selecting the socket for writing.  After select(2) indicates  writability,  use  getsockopt(2)  to  read  the  SO_ERROR  option at level SOL_SOCKET to determine whether connect() completed successfully (SO_ERROR is zero) or unsuccessfully (SO_ERROR is one of the usual error codes listed here, explaining the reason for the failure).";
			break;

		case EINTR:
			this->msg = "The system call was interrupted by a signal that was caught; see signal(7).";
			break;

		case EISCONN:
			this->msg = "The socket is already connected.";
			break;

		case ENETUNREACH:
			this->msg = "Network is unreachable.";
			break;

		case ENOTSOCK:
			this->msg = "The file descriptor is not associated with a socket.";
			break;

		case ETIMEDOUT:
			this->msg = "Timeout while attempting connection.  The server may be too busy to accept new connections.  Note that for IP sockets the timeout may be very long  when  syncookies  are  enabled  on  the server.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*---------------------------*/




int SocketException::listenException()
{
	switch ( this->errorCode )
	{
		case EADDRINUSE:
			this->msg = "Another socket is already listening on the same port.";
			break;

		case EBADF:
			this->msg = "The argument sockfd is not a valid descriptor.";
			break;

		case ENOTSOCK:
			this->msg = "The argument sockfd is not a socket.";
			break;

		case EOPNOTSUPP:
			this->msg = "The socket is not of a type that supports the listen() operation.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*-------------------------*/





int SocketException::acceptException()
{
	switch ( this->errorCode )
	{
		//case EAGAIN: <- mesmo código que EWOULDBLOCK
		case EWOULDBLOCK:
			this->msg = "The  socket  is  marked non-blocking and no connections are present to be accepted.  POSIX.1-2001 allows either error to be returned for this case, and does not require these constants to have the same value, so a portable application should check for both possibilities.";
			break;

		case EBADF:
			this->msg = "The descriptor is invalid.";
			break;

		case ECONNABORTED:
			this->msg = "A connection has been aborted.";
			break;

		case EFAULT:
			this->msg = "The addr argument is not in a writable part of the user address space.";
			break;

		case EINTR:
			this->msg = "The system call was interrupted by a signal that was caught before a valid connection arrived; see signal(7).";
			break;

		case EINVAL:
			this->msg = "Socket is not listening for connections, or addrlen is invalid (e.g., is negative) OR (accept4()) invalid value in flags.";
			break;

		case EMFILE:
			this->msg = "The per-process limit of open file descriptors has been reached.";
			break;

		case ENFILE:
			this->msg = "The system limit on the total number of open files has been reached.";
			break;

		case ENOBUFS:
		case ENOMEM:
			this->msg = "Not enough free memory.  This often means that the memory allocation is limited by the socket buffer limits, not by the system memory.";
			break;

		case ENOTSOCK:
			this->msg = "The descriptor references a file, not a socket.";
			break;

		case EOPNOTSUPP:
			this->msg = "The referenced socket is not of type SOCK_STREAM.";
			break;

		case EPROTO:
			this->msg = "Protocol error.";
			break;

		case EPERM:
			this->msg = "Firewall rules forbid connection.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*-------------------------*/




int SocketException::sendException()
{
	switch ( this->errorCode )
	{
		case EACCES:
			this->msg = "(For  Unix  domain sockets, which are identified by pathname) Write permission is denied on the destination socket file, or search permission is denied for one of the directories the path prefix.  (See path_resolution(7).)";
			break;

		// case EAGAIN: <- mesmo código que EWOULDBLOCK
		case EWOULDBLOCK:
			this->msg = "The socket is marked non-blocking and the requested operation would block.  POSIX.1-2001 allows either error to be returned for this case, and does not require these constants to have the same value, so a portable application should check for both possibilities.";
			break;

		case EBADF:
			this->msg = "An invalid descriptor was specified.";
			break;

		case ECONNRESET:
			this->msg = "Connection reset by peer.";
			break;

		case EDESTADDRREQ:
			this->msg = "The socket is not connection-mode, and no peer address is set.";
			break;

		case EFAULT:
			this->msg = "An invalid user space address was specified for an argument.";
			break;

		case EINTR:
			this->msg = "A signal occurred before any data was transmitted; see signal(7).";
			break;

		case EINVAL:
			this->msg = "Invalid argument passed.";
			break;

		case EISCONN:
			this->msg = "The connection-mode socket was connected already but a recipient was specified.  (Now either this error is returned, or the recipient specification is ignored.)";
			break;

		case EMSGSIZE:
			this->msg = "The socket type requires that message be sent atomically, and the size of the message to be sent made this impossible.";
			break;

		case ENOBUFS:
			this->msg = "The  output  queue for a network interface was full.  This generally indicates that the interface has stopped sending, but may be caused by transient congestion.  (Normally, this does not occur in Linux.  Packets are just silently dropped when a device queue overflows.)";
			break;

		case ENOMEM:
			this->msg = "No memory available.";
			break;

		case ENOTCONN:
			this->msg = "The socket is not connected, and no target has been given.";
			break;

		case ENOTSOCK:
			this->msg = "The argument sockfd is not a socket.";
			break;

		case EOPNOTSUPP:
			this->msg = "Some bit in the flags argument is inappropriate for the socket type.";
			break;

		case EPIPE:
			this->msg = "The local end has been shut down on a connection oriented socket.  In this case the process will also receive a SIGPIPE unless MSG_NOSIGNAL is set.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*-----------------------*/




int SocketException::recvException()
{
	switch ( this->errorCode )
	{
		// case EAGAIN: <- mesmo código que EWOULDBLOCK
		case EWOULDBLOCK:
			this->msg = "The socket is marked non-blocking and the receive operation would block, or a receive timeout had been set and the timeout expired before data was received.   POSIX.1-2001  allows  either error to be returned for this case, and does not require these constants to have the same value, so a portable application should check for both possibilities.";
			break;

		case EBADF:
			this->msg = "The argument sockfd is an invalid descriptor.";
			break;

		case ECONNREFUSED:
			this->msg = "A remote host refused to allow the network connection (typically because it is not running the requested service).";
			break;

		case EFAULT:
			this->msg = "The receive buffer pointer(s) point outside the process's address space.";
			break;

		case EINTR:
			this->msg = "The receive was interrupted by delivery of a signal before any data were available; see signal(7).";
			break;

		case EINVAL:
			this->msg = "Invalid argument passed.";
			break;

		case ENOMEM:
			this->msg = "Could not allocate memory for recvmsg().";
			break;

		case ENOTCONN:
			this->msg = "The socket is associated with a connection-oriented protocol and has not been connected (see connect(2) and accept(2)).";
			break;

		case ENOTSOCK:
			this->msg = "The argument sockfd does not refer to a socket.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*------------------------*/




/* ocorream os mesmos erros de send() */
int SocketException::sendtoException()
{
	this->sendException();

	return this->errorCode;
}
/*---------------------------*/


/* ocorrem os mesmos erros de recv() */
int SocketException::recvfromException()
{
	this->recvException();

	return this->errorCode;
}
/*----------------------------*/


int SocketException::closeException()
{
	switch ( this->errorCode )
	{
		case EBADF:
			this->msg = "fd isn't a valid open file descriptor.";
			break;

		case EINTR:
			this->msg = "The close() call was interrupted by a signal; see signal(7).";
			break;

		case EIO:
			this->msg = "An I/O error occurred.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*----------------------------*/




int SocketException::shutdownException()
{
	switch ( this->errorCode )
	{
		case EBADF:
			this->msg = "sockfd is not a valid descriptor.";
			break;

		case ENOTCONN:
			this->msg = "The specified socket is not connected.";
			break;

		case ENOTSOCK:
			this->msg = "sockfd is a file, not a socket.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*-----------------------------*/



int SocketException::getpeernameException()
{
	switch ( this->errorCode )
	{
		case EBADF:
			this->msg = "The argument sockfd is not a valid descriptor.";
			break;

		case EFAULT:
			this->msg = "The addr argument points to memory not in a valid part of the process address space.";
			break;

		case EINVAL:
			this->msg = "addrlen is invalid (e.g., is negative).";
			break;

		case ENOBUFS:
			this->msg = "Insufficient resources were available in the system to perform the operation.";
			break;

		case ENOTCONN:
			this->msg = "The socket is not connected.";
			break;

		case ENOTSOCK:
			this->msg = "The argument sockfd is a file, not a socket.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*--------------------------*/



int SocketException::gethostnameException()
{
	switch ( this->errorCode )
	{
		case EFAULT:
			this->msg = "name is an invalid address.";
			break;

		case EINVAL:
			this->msg = "len is negative or, for sethostname(), len is larger than the maximum allowed size.";
			break;

		case ENAMETOOLONG:
			this->msg = "(glibc gethostname()) len is smaller than the actual size.  (Before version 2.1, glibc uses EINVAL for this case.)";
			break;

		case EPERM:
			this->msg = "For sethostname(), the caller did not have the CAP_SYS_ADMIN capability.";
			break;
		
		default:
			char str[256];
			sprintf( str, "Unknown exception. errno value: %d | SocketException::errorCode value: %d\n",  errno, this->errorCode );
			this->msg = str;
			break;
	}

	return this->errorCode;
}
/*-----------------------------*/
