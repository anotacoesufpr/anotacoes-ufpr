# -*- coding: utf-8 -*-

## Arquivo com a classe FileHandler
# @file lib/FileHandler.py

## Classe para manipulação de arquivos
class FileHandler( object ):
	##
	# Ponteiro para o arquivo
	FilePointer = None
	
	##
	#	Construtor da classe
	#	@param self Ponteiro do objeto
	def __init__( self ):
		self.FilePointer = None
	
	##
	#	Abre um arquivo
	#	@param self Ponteiro do objeto
	#	@param filename Caminho para o arquivo a ser aberto
	#	@param mode Modo de abertura (mesmos modos de open())
	def open( self, filename, mode ):
		self.FilePointer = open( filename, mode)
	
	##
	#	Escreve uma mensagem no arquivo
	#	@param self Ponteiro do objeto
	#	@param msg Mensagem a ser escrita no arquivo
	#
	def write( self, msg ):
		self.FilePointer.write( msg + '\n' )
	
	##
	#	Lê uma linha do arquivo
	#	@param self Ponteiro do objeto
	#	@return Retorna a linha lida
	def readline( self ):
		return self.FilePointer.readline().rstrip()
	
	##
	#	Lê todas as linhas do arquivo
	#	@param self Ponteiro do objeto
	#	@return Retorna o conteúdo lido
	def readlines( self ):
		return self.FilePointer.readlines()


	##
	#	Fecha o arquivo
	#	@param self Ponteiro do objeto
	def close( self ):
		self.FilePointer.close()
