# -*- coding: utf-8 -*-

## Arquivo com a classe Log
# @file lib/Log.py

import sys
from time import localtime
sys.path.append( ".." )
from config import *
from FileHandler import *

## Classe para geração de logs
class Log( object ):
	
	## Construtor
	# @param logFileName Nome do arquivo de log a ser usado
	def __init__( self, logFileName ):
		self.logFileName = logFileName
	
	## Adiciona "msg" ao arquivo de log
	# @param self Ponteiro do objeto
	# @param msg Mensagem a ser escrita no log
	def LogMsg( self, msg ):
		# Pega data e hora locais
		localTime = localtime()
		
		# Monta string com data e hora (YYYY-MM-DD HH:MM:SS)
		strDateTime = '{0:02}'.format(localTime[0]) + "-" + '{0:02}'.format(localTime[1]) + "-" + '{0:02}'.format(localTime[2]) + " " + '{0:02}'.format(localTime[3]) + ":" + '{0:02}'.format(localTime[4]) + ":" + '{0:02}'.format(localTime[5])
		Log = FileHandler()
		Log.open( self.logFileName, 'a' )
		Log.write( "[" + strDateTime + "]: " + msg )
		Log.close()
