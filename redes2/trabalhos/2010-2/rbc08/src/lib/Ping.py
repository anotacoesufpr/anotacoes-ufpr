# -*- coding: utf-8 -*-

## Arquivo com a classe ICMP
# @file lib/ICMP.py

import os
import sys
import threading
sys.path.append( ".." )
from config import *

## Classe para fazer ping com thread
class Ping( object ):
	##
	# Realiza PING
	# @param self Ponteiro do objeto
	# @param ip IP do host a ser "pingado"
	# @param tentativas (opcional) Número de tentativas do PING (padrão 4)
	# @return Retorna o valor retornado pelo comando ping do bash
	def ping( self, ip, tentativas = 4 ):
		cmd = "ping -c " + str( tentativas ) + " " + str( ip ) + " > /dev/null"
		
		# executa o comando e coloca em ret o retorno dele
		result = os.system( cmd );
		
		return int( result )
