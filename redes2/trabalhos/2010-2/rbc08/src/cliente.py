#!/usr/bin/env python
# -*- coding: utf-8 -*-

## Arquivo com a implementação do cliente
# @file cliente.py

import os
import socket
import sys
sys.path.append( 'lib' )
from Pacote import *
from Protocol import *
from Host import *
from Log import *
from config import *



##
# Função que lê a lista de hosts da entrada padrão
# @return Retorna uma lista de objetos Host com os hosts lidos
def ReadHosts():
		hosts = []
		for h in sys.stdin.readlines():
			objHost = Host( HOST_DESCONHECIDO, h.rstrip() )
			hosts.append( objHost )
		return hosts

##
# Função que exibe na tela a forma de uso correta do programa
def usage():
	print "Erro" 
	print "Forma de uso: " + sys.argv[0] + " <host> <porta>"


# verifica o número de parâmetros do programa
if len( sys.argv ) != 3:
	usage()
	sys.exit( 1 )

# Objeto para log de eventos
EventLog = Log( EVENT_LOG_FILENAME );

# Objeto para log do cliente
ClientLog = Log( CLIENT_LOG_FILENAME );

# Se existir um arquivo antigo de log de enventos, remove-o
if os.path.exists( EVENT_LOG_FILENAME ):
	os.remove( EVENT_LOG_FILENAME );

# Lê os hosts da entrada padrão
hostsList = ReadHosts();

# Transforma a lista de hosts em uma string para mandar ao monitor (servidor)
# Insere os nomes dos hosts em uma lista, depois usa o método join()
hostArr = []
for objHost in hostsList:
	hostArr.append( objHost.getNome() )
hostsListAsString = str( HOSTS_SEP ).join( hostArr )



# monta a string a ser enviada ao monitor
pack = Pacote( PROTOCOL_COD_SEND_HOSTS, None, None, None, hostsListAsString )
msgHosts = Protocol.Pack2Str( pack )

# host e porta passados por parâmetro
host = str( sys.argv[1] )
port = int( sys.argv[2] )

try:
	sockSend = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
except socket.error, ( errno, errmsg ):
	if sockSend:
		sockSend.close();
	ClientLog.LogMsg( "Erro ao criar socket: " + str( errno ) + ": " + str( errmsg ) );
	sys.exit( 1 );

ClientLog.LogMsg( "Socket criado com sucesso" );

# evita impedir "bindar" um socket após interromper uma execução anterior (processo zumbi). Ver man 7 socket
sockSend.setsockopt( socket.SOL_SOCKET, socket.SO_REUSEADDR, 1 )

try:
	sockSend.connect( ( host, port ) )
except socket.error, ( errno, errmsg ):
	if sockSend:
		sockSend.close();
	ClientLog.LogMsg( "Erro ao se conectar com o servidor: " + str( errno ) + ": " + str( errmsg ) );
	sys.exit( 1 );

ClientLog.LogMsg( "Conexão com o servidor estabelecida com sucesso" );

# envia a lista de hosts a monitorar
try:
	sockSend.send( msgHosts )
except socket.error, ( errno, errmsg ):
	if sockSend:
		sockSend.close();
	ClientLog.LogMsg( "Erro ao ao enviar mensagem ao servidor: " + str( errno ) + ": " + str( errmsg ) );
	sys.exit( 1 );

ClientLog.LogMsg( "Enviada lista de hosts ao servidor" );


# abre o navegador para exibir a interface gráfica
os.system( GUI_CMD.format( GUI_FILENAME ) );


# escuta pelas mensagens sobre eventos em hosts
while 1:
	dados = sockSend.recv( MAX_RECV_SIZE )
	if not dados:
		break
	pack = Protocol.Str2Pack( dados )
	
	# Verifica se foi recebida uma informação sobre evento
	if ( pack.getCodigo() == PROTOCOL_COD_EVENT ):
		# Atualiza a lista de hosts
		for i in range( len( hostsList ) ):
			if hostsList[i].getNome() == pack.getNomeHost():
				estadoAnterior = hostsList[i].getEstado()
				hostsList[i].setEstado( pack.getEstadoHost() )
				break
		# print MSG_EVENT.format( pack.getNomeHost(), pack.getIpHost(), str( estadoAnterior ), pack.getEstadoHost() )
		EventLog.LogMsg( MSG_EVENT.format( pack.getNomeHost(), pack.getIpHost(), str( estadoAnterior ), pack.getEstadoHost() ) );
		ClientLog.LogMsg( MSG_EVENT.format( pack.getNomeHost(), pack.getIpHost(), str( estadoAnterior ), pack.getEstadoHost() ) );

sockSend.close()




