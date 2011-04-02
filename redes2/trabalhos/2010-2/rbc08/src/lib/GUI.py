# -*- coding: utf-8 -*-

## Arquivo com a classe GUI
# @file lib/GUI.py

import os
import sys
sys.path.append( ".." )
from config import *
from FileHandler import *

## Classe responsável pela criação da interface gráfica em HTML
class GUI( object ):
	
	##
	# Retorna uma string contendo o cabeçalho da página HTML
	# @param self Ponteiro do objeto
	# @return Retorna uma string contendo o cabeçalho da página HTML
	def getHeader( self ):
		header  = '<!DOCTYPE HTML>\n'
		header += '<html lang="pt-br">\n'
		header += '<head>\n'
		header += '<title>Interface do Monitor</title>\n'
		header += '<meta http-equiv="content-type" content="text/html; charset=utf-8" />\n'
		header += '<style type="text/css">\n'
		header += '#divEstados{ width: 650px; height: 300px; overflow: auto; border: solid 2px #000; }'
		header += '#divEventos{ width: 800px; height: 300px; overflow: auto; border: solid 2px #000; }'
		header += '#divEventos p{ margin: 3px 0; }';
		header += '</style>\n'
		header += '<meta http-equiv="refresh" content="3" />\n'
		header += '</head>\n'
		header += '<body>\n'
		header += '<h1>Interface do Monitor de Múltiplos Hosts</h1>\n'
		
		return header
	
	
	## Gera o conteúdo da div de estados de hosts
	# @param self Ponteiro do objeto
	# @param hostList List com os hosts monitorados
	# @return Retorna o código HTTML da div de estados dos hosts
	def divEstados( self, hostList ):
		content  = '<h2>Estados dos hosts monitorados</h2>';
		content += "<div id=\"divEstados\">\n";
		for objHost in hostList:
			# define a cor
			if objHost.getEstado() == HOST_ATIVO:
				cor = COR_HOST_ATIVO
			elif objHost.getEstado() == HOST_FALHO:
				cor = COR_HOST_FALHO
			else:
				cor = COR_HOST_DESCONHECIDO
			
			# O IP pode não ter sido definido ainda
			if objHost.getIp() in ( False, None ):
				ip = "desconhecido"
			else:
				ip = objHost.getIp()
			
			content += "<p style=\"font-weight: bold; color: " + cor + ";\">Host " + str( objHost.getNome() ) + "(" + str( ip ) + ") está " + str( objHost.getEstado() ) + "</p>\n";
		content += "</div>";
		
		return content;
	
	## Gera a div com os logs dos eventos
	#
	# Este método lê o arquivo que contém os logs dos eventos e adiciona seu conteúdo à interface gráfica
	# @param self Ponteiro do objeto
	# @return Retorna o código HTML da div dos eventos
	def divEventos( self ):
		content  = '<h2>Log de eventos nos hosts monitorados</h2>';
		content += "<div id=\"divEventos\">";
		
		# Se o arquivo de log de eventos existir, adiciona seu conteúdo à div
		if os.path.exists( EVENT_LOG_FILENAME ):
			FH = FileHandler();
			FH.open( EVENT_LOG_FILENAME, 'r' );
			for line in FH.readlines():
				content += "<p>" + line + "</p>";
			FH.close();		
		
		content += "</div>";
		return content;
	
	##
	# Atualiza o HTML da interface, inserindo os novos estados dos hosts
	# @param self Ponteiro do objeto
	# @param hostList List com os hosts monitorados
	def Refresh( self, hostList ):
		guiFile = FileHandler()
		guiFile.open( GUI_FILENAME, "w" )
		guiFile.write( self.getHeader() )
		guiFile.write( self.divEstados( hostList) );
		guiFile.write( self.divEventos() );
		guiFile.write( self.getFooter() )
		guiFile.close()
	
	##
	# Retorna o rodapé da página HTML da interface
	# @param self Ponteiro do objeto
	# @return Retorna o rodapé da página HTML da interface
	def getFooter( self ):
		footer  = '</body>\n'
		footer += '</html>\n'
		
		return footer
	

