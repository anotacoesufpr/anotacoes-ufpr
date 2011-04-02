/**
 * @file src/SocketException.h
 *
 */

#ifndef SOCKETEXCEPTION_H_
#define SOCKETEXCEPTION_H_

#include <iostream>
#include <exception>
#include <cerrno>


using namespace std;


/**
 * Classe para manipulação de erros de sockets. Os códigos de erros e as respectivas mensagens foram retiradas das páginas do man
 * @class SocketException
*/
class SocketException : public exception
{
	private:
		string functionName;
		string msg;
		int errorCode;

	public:
		/**
		 * Construtor da classe
		 * @param funcName Nome da função onde ocorreu a exceção
		 * @param returnValue (opcional) Por padrão é o valor de \c errno. É usado para funções que retornam um código de erro em vez de modificar o valor de \c errno.
		*/
		SocketException( string funcName, int returnValue = 0 );
		
		virtual ~SocketException() throw () {}
		
		/**
		 * Sobrecarga do método \c what da classe \c exception
		*/
		const char* what() const throw();
		
		
		/**
		 * Verifica qual erro ocorreu ao chamar a função getaddrinfo()
		 * @reutrn Retorna o valor do erro.
		*/
		int getaddrinfoException();
		
		
		
		int socketException();
		int bindException();
		int connectException();
		int listenException();
		int acceptException();
		int sendException();
		int recvException();
		int sendtoException();
		int recvfromException();
		int closeException();
		int shutdownException();
		int getpeernameException();
		int gethostnameException();
};

#endif /* SOCKETEXCEPTION_H_ */
