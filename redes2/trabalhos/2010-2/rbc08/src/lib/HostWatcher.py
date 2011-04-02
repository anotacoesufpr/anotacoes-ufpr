# -*- coding: utf-8 -*-

import threading
import socket
import sys
import time
sys.path.append( '..' )
from config import *
from Ping import *
from DNS import *
from Pacote import *
from Protocol import *
from Log import *
from GUI import *

## Classe que monitora um host
class HostWatcher( threading.Thread ):
	## Booleano que define quando o loop deve estar ativo
	loop = True
	
	def __init__( self, hostId, hostList, sockRec ):
		threading.Thread.__init__( self )
		self.__hostId = hostId
		self.__hostList = hostList
		self.__sockRec = sockRec
	
	def run( self ):
		P = Ping()
		D = DNS()
		log = Log( SERVER_LOG_FILENAME )
		
		try:
			while self.loop:
				if self.__hostList[self.__hostId].getIp() in [None, False]:
					msg = MSG_RESOLV_DNS.format( self.__hostList[self.__hostId].getNome() )
					log.LogMsg( msg )
					self.__hostList[self.__hostId].setIp( D.ResolveDNS( self.__hostList[self.__hostId].getNome() ) )
					if self.__hostList[self.__hostId].getIp() in [None, False]:
						msg = MSG_RESOLV_DNS_FAIL.format( self.__hostList[self.__hostId].getNome() )
						log.LogMsg( msg )
						time.sleep( PING_INTERVAL )
						continue
					else:
						msg = MSG_RESOLV_DNS_SUCCESS.format( self.__hostList[self.__hostId].getNome(), self.__hostList[self.__hostId].getIp() )
						log.LogMsg( msg )
					
				
				pingReturn = P.ping( self.__hostList[ self.__hostId ].getIp() )
					
				# Faz ping no IP do host
				msg = MSG_PING.format( self.__hostList[self.__hostId].getIp() )
				log.LogMsg( msg )
				msg = MSG_RES_PING.format( self.__hostList[self.__hostId].getIp(), pingReturn )
				log.LogMsg( msg )
				
				# Retorno zero corresponde a comando executado com sucesso
				if ( pingReturn == 0 ):
					if self.__hostList[self.__hostId].getEstado() != HOST_ATIVO:
						# Houve mudança de estado (evento)
						msg = MSG_EVENT.format( self.__hostList[self.__hostId].getNome(), self.__hostList[self.__hostId].getIp(), self.__hostList[self.__hostId].getEstado(), HOST_ATIVO )
						self.__hostList[self.__hostId].setEstado( HOST_ATIVO )
						log.LogMsg( msg )
						
						# monta um Pacote para informar o cliente
						pack = Pacote( PROTOCOL_COD_EVENT, self.__hostList[self.__hostId].getIp(), self.__hostList[self.__hostId].getNome(), self.__hostList[self.__hostId].getEstado() )
						strSend = Protocol.Pack2Str( pack )
						try:
							self.__sockRec.send( strSend )
						except socket.error, ( errno, errmsg ):
							if self.__sockRec:
								self.__sockRec.close();
							log.LogMsg( "Erro ao ao enviar mensagem ao cliente: " + str( errno ) + ": " + str( errmsg ) );
							sys.exit( 1 );
				else:
					# Não respondeu ao PING
					# Se o host for desconhecido, permanece desconhecido
					# Se o host for ativo, passa a ser falho
					if self.__hostList[self.__hostId].getEstado() == HOST_ATIVO:
						# Ocorreu mudança de estado (evento)
						msg = MSG_EVENT.format( self.__hostList[self.__hostId].getNome(), self.__hostList[self.__hostId].getIp(), self.__hostList[self.__hostId].getEstado(), HOST_FALHO )
						self.__hostList[self.__hostId].setEstado( HOST_FALHO )
						log.LogMsg( msg )
						
						# monta um Pacote para informar o cliente
						pack = Pacote( PROTOCOL_COD_EVENT, self.__hostList[self.__hostId].getIp(), self.__hostList[self.__hostId].getNome(), self.__hostList[self.__hostId].getEstado() )
						strSend = Protocol.Pack2Str( pack )
						try:
							self.__sockRec.send( strSend )
						except socket.error, ( errno, errmsg ):
							if self.__sockRec:
								self.__sockRec.close();
							log.LogMsg( "Erro ao ao enviar mensagem ao cliente: " + str( errno ) + ": " + str( errmsg ) );
							sys.exit( 1 );
					else:
						self.__hostList[self.__hostId].setEstado( HOST_DESCONHECIDO )
				
				# aguarda PING_INTERVAL segundos antes de tentar novo PING
				time.sleep( 1 )
		except KeyboardInterrupt:
			self.loop = False 
			sys.exit( 0 )
	
	def getHostId( self ):
		return self.__hostId
	
	def setLoop( self, loop ):
		self.loop = loop
