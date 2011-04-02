# -*- coding: utf-8 -*-

## Arquivo com a classe DNS
# @file lib/DNS.py

from socket import gethostbyname

## A classe DNS possui métodos relacionados a DNS, como resolução domínios 
class DNS( object ):
	
	##
	# Resolve um DNS e retorna o IP encontrado
	# @param self Ponteiro do objeto
	# @param hostname Nome do host cujo DNS deve ser resolvido
	# @return Retorna o IP do host ou False em caso de falha
	def ResolveDNS( self, hostname ):
		if hostname:
			try:
				result = gethostbyname( hostname )
			except:
				return False
			return result
		return False
