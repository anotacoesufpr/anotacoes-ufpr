# -*- coding: utf-8 -*-

## Arquivo com a classe Protocol
# @file lib/Protocol.py

import pickle # módulo para serialização
import sys
sys.path.append( ".." )
from config import *


## Classe que implementa o protocolo da aplicação
class Protocol( object ):
	
	##
	# Transforma uma string enviada pelo socket em um Pacote do Protocolo
	# @param string String a ser transformada em Pacote 
	# @return Retorna um objeto do tipo Pacote
	@staticmethod
	def Str2Pack( string ):
		pack = pickle.loads( string )
		return pack
	
	##
	# Transforma um Pacote do Protocolo em uma string a ser enviada via socket
	# @param pack Pacote a ser transformado em string
	# @return Retorna um string, que é o Pacote serializado
	@staticmethod
	def Pack2Str( pack ):
		string = pickle.dumps( pack )
		return string
