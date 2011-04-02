# -*- coding: utf-8 -*-

## Arquivo com a classe Pacote
# @file lib/Pacote.py

## Classe que representa o pacote do protocolo, que é enviado entre o cliente e o monitor
class Pacote( object ):
	__codigo	= None
	__ipHost	= None
	__nomeHost	= None
	__estadoHost= None
	__dados		= None
	
	def __init__( self, cod = None, ip = None, nome = None, estado = None, dados = None ):
		self.__codigo = cod
		self.__ipHost = ip
		self.__nomeHost = nome
		self.__estadoHost = estado
		self.__dados = dados
	
	def setCodigo( self, cod ):
		self.__codigo = cod
	
	def setIpHost( self, ip ):
		self.__ipHost = ip
	
	def setNomeHost( self, nome ):
		self.__nomeHost = nome
	
	def setEstadoHost( self, estado ):
		self.__estadoHost = estado
	
	def setDados( self, dados ):
		self.__dados = dados
	
	def getCodigo( self ):
		return self.__codigo
	
	def getIpHost( self ):
		return self.__ipHost
	
	def getNomeHost( self ):
		return self.__nomeHost
	
	def getEstadoHost( self ):
		return self.__estadoHost
	
	def getDados( self ):
		return self.__dados
