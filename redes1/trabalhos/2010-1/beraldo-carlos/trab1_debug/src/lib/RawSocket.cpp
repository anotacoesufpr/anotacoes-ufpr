/**
 * @file src/lib/RawSocket.cpp
 */

#include "RawSocket.h"


/**
 * Cria um RawSocket
 */
int RawSocket::Rawsocket( const char *device )
{
	int sock;
	struct timeval tv;

//	tv.tv_usec = TEMPO_TIMEOUT;
	tv.tv_sec = 5;
	
	try
	{
		sock = MySocket::_socket( PF_PACKET, SOCK_RAW, 0 );  // Cria um socket do tipo RawSocket.
	}
	catch ( SocketException& SE )
	{
		cerr << SE.what() << endl;
		exit( 1 );
	}
	
	// Descobre o Id da interface ("eth#").
	struct ifreq ifr;

	memset( &ifr, 0, sizeof( struct ifreq ) );
	memcpy( ifr.ifr_name, device, sizeof( device ) ); // Copia a parte da memoria de 'device' em 'ifr.ifr_name'.
	
	if ( ioctl( sock, SIOCGIFINDEX, &ifr ) == -1 )
	{
		cerr << "Erro no ioctl()" << endl;
		throw( strerror( errno ) );
	}
	
	int deviceid = ifr.ifr_ifindex;

	
	// "Binda", no socket, o endereco guardado em 'sll'.
	struct sockaddr_ll sll;

	memset( &sll, 0, sizeof( sll ) );

	sll.sll_family = AF_PACKET; // Sempre AF_PACKET.
	sll.sll_ifindex = deviceid; // Id da interface. ("eth#")
	sll.sll_protocol = htons( ETH_P_ALL );  // Protocolo da Camada Fisica.

	try
	{
		MySocket::_bind( sock, ( struct sockaddr * ) &sll, sizeof( sll ) );
	}
	catch ( SocketException& SE )
	{
		cerr << SE.what() << endl;
		exit( 1 );
	}

	// Coloca a interface em modo Promiscuo.
	struct packet_mreq mr;
	memset( &mr, 0, sizeof( mr ) );
	mr.mr_ifindex = deviceid;  // Id da interface que sera mudada. ("eth#")
	mr.mr_type = PACKET_MR_PROMISC; // Modo Promiscuo.

    if ( setsockopt( sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof( mr ) ) == -1 )
    {  // Coloca o socket 'sock' em modo promiscuo.
    	cerr << "Erro ao colocar socket no modo promíscuo" << endl;
    	throw(strerror(errno));
	}


    setsockopt( sock, SOL_RAW, SO_RCVTIMEO, (void *) &tv, sizeof( struct timeval ) );

    return sock;
}
