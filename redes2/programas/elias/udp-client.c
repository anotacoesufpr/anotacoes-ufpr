/* cliente.c
   Elias P. Duarte Jr. */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ) 
{
	int sockdescr;
	int numbytesrecv;
	struct sockaddr_in sa;
	struct hostent *hp;
	char buf[BUFSIZ+1];
	char *host;
	char *dados;
	unsigned int i;

	if ( argc != 4 )
	{
		printf( "Uso correto: %s <nome-servidor> <porta> <dados>\n", argv[0] );
		exit( 1 );
	}

	host = argv[1];
	dados = argv[3];

	if ( ( hp = gethostbyname( host ) ) == NULL )
	{
		puts( "Nao consegui obter endereco IP do servidor." );
		exit( 1 );
	}

	bcopy( (char *) hp->h_addr, (char *) &sa.sin_addr, hp->h_length );
	sa.sin_family = hp->h_addrtype;

	sa.sin_port = htons( atoi( argv[2] ) );

	if ( ( sockdescr = socket( hp->h_addrtype, SOCK_DGRAM, 0 ) ) < 0 )
	{
		puts( "Nao consegui abrir o socket." );
		exit( 1 );
	}

	if ( sendto( sockdescr, dados, strlen( dados ) + 1, 0, (struct sockaddr *) &sa, sizeof sa) != strlen( dados ) + 1)
	{
		puts("Nao consegui mandar os dados"); 
		exit(1);
	}
	/* end while }*/

	recvfrom( sockdescr, buf, BUFSIZ, 0, (struct sockaddr *) &sa, &i );

	printf( "Sou o cliente, recebi: %s\n", buf );
   
	close( sockdescr );
	
	return 0;
}



















