#!/usr/bin/env python
# -*- coding: utf-8 -*-

## Arquivo com a implementação do monitor
# @file monitor.py

import socket
import time
import signal
import sys
sys.path.append( 'lib' )
from DNS import *
from GUI import *
from Ping import *
from Host import *
from Log import *
from config import *
from Pacote import *
from Protocol import *
from HostWatcher import *



##
# Função que exibe na tela a forma correta de uso do programa
def usage():
	print "Erro" 
	print "Forma de uso: " + sys.argv[0] + " <porta>"

## Função que finaliza as threads antes de encerrar o programa
#
# Esta função é chamada ao detectar o sinal SIGINT (interrupção - CTRL+C)
def stopThreads( signal, frame ):
	global threadList
	global keepLoop
	
	keepLoop = False
	
	for i in range( len( threadList ) ):
		threadList[i].setLoop( False )
	
	print "\n\n\n======================================================"
	print 'Encerrando threads para finalizar o programa...'
	print "======================================================\n\n\n"
	sys.exit(0)


# associa SIGINT à função stopThreads
signal.signal( signal.SIGINT, stopThreads )


# Verifica o número de parâmetros do programa
if len( sys.argv ) != 2:
	usage()
	sys.exit( 1 )

# Objeto para log do servidor
ServerLog = Log( SERVER_LOG_FILENAME );

# atribui a "host" o nome do host em que o programa está sendo executado
host = socket.gethostname()

# porta passada como parâmetro do programa
port = int( sys.argv[1] )

# Lista de hosts a monitorar
hostList = []

# cria o socket
try:
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
except socket.error, ( errno, errmsg ):
	if socd:
		sock.close();
	ServerLog.LogMsg( "Erro ao criar socket: " + str( errno ) + ": " + str( errmsg ) );
	sys.exit( 1 );

# evita impedir "bindar" um socket após interromper uma execução anterior (processo zumbi). Ver man 7 socket
sock.setsockopt( socket.SOL_SOCKET, socket.SO_REUSEADDR, 1 )

try:
	sock.bind( ( host, port ) )
except socket.error, ( errno, errmsg ):
	if socd:
		sock.close();
	ServerLog.LogMsg( "Erro ao fazer bind() no socket: " + str( errno ) + ": " + str( errmsg ) );
	sys.exit( 1 );

try:
	sock.listen( 1 )
except socket.error, ( errno, errmsg ):
	if socd:
		sock.close();
	ServerLog.LogMsg( "Erro ao fazer listen(): " + str( errno ) + ": " + str( errmsg ) );
	sys.exit( 1 );

try:
	sockRec, remoteAddr = sock.accept()
except socket.error, ( errno, errmsg ):
	if socd:
		sock.close();
	ServerLog.LogMsg( "Erro em accept(): " + str( errno ) + ": " + str( errmsg ) );
	sys.exit( 1 );


# recebe a lista de hosts do cliente
data = sockRec.recv( MAX_RECV_SIZE )
pack = Protocol.Str2Pack( data )
hosts = pack.getDados() # pega apenas o campo "dados", que tem a lista de hosts
    
# adiciona os hosts recebidos à lista de hosts monitorados
for hostName in hosts.rsplit( str( HOSTS_SEP ) ):
	objHost = Host( HOST_DESCONHECIDO, hostName )
	hostList.append( objHost )


# lista de threads
threadList = [None] * len( hostList )

for i in range( len( hostList ) ):
	threadList[i] = HostWatcher( i, hostList, sockRec )
	threadList[i].setDaemon( True )
	threadList[i].start()

GUI = GUI()
GUI.Refresh( hostList )

keepLoop = True
while keepLoop:
	
	GUI.Refresh( hostList )
	time.sleep( 3 )

# Fecha os sockets
sockRec.close()
sock.close()

sys.exit( 0 )
