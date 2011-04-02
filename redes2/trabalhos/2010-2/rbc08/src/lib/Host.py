# -*- coding: utf-8 -*-

## Arquivo com a classe Host
# @file lib/Host.py

import sys
sys.path.append( ".." )
from config import *


## Classe que representa um host em monitoração
class Host( object ):
	## Estado do host (desconhecido, falho ou ativo)
	__estado = HOST_DESCONHECIDO

	## Nome do host 
	__nome = None

	## IP do host
	__ip = None

	##
	# Construtor
	# @param self Ponteiro do objeto
	# @param estado (opcional) Estado inicial do host
	# @param nome Nome do host
	# @param ip IP do host
	def __init__( self, estado = HOST_DESCONHECIDO, nome = None, ip = None ):
		self.__estado = estado
		self.__ip = ip
		self.__nome = nome

	def getIp(self):
		return self.__ip

	def getNome(self):
		return self.__nome
		
	def getEstado(self):
		return self.__estado
	
	def setNome( self, nome ):
		self.__nome = noome
	
	def setIp( self, ip ):
		self.__ip = ip
	
	def setEstado( self, estado ):
		self.__estado = estado

