# -*- coding: utf-8 -*-

#importando classes
import sys
import os

#biblioteca local
sys.path.append( 'library' )
from host import *
from functions import *
from Pacote import *
from threado import *
from Log import *
from msg import *

class interface():

   def generate(self,listaHosts):
      self.lista = listaHosts
      genereatingHtml = open("index.html", "w")
      genereatingHtml.write(self.getHeader())
      genereatingHtml.write(self.getBody(self.lista))
      genereatingHtml.write(self.getFooter())
      genereatingHtml.close()

   #gera cabecalho do HTML
   def getHeader(self):
      headHtml = '<html>\n'
      headHtml += '<head><title>Trabalho de Redes II - Monitor WEB</title>\n'
      headHtml += '<meta http-equiv="content-type" content="text/html; charset=utf-8"/>\n'
      headHtml += '<meta http-equiv="refresh" content="10">\n'
      headHtml += '</head>\n'
      return headHtml

   #define as cores conforme os estados de acordo com o solicitado pelo projeto
   def getBody(self,listaHosts):
      contentHtml = '<body>\n'
      contentHtml += '<h1> Trabalho de Redes II</h1><br>\n'
      contentHtml += '<h1> Monitor WEB</h1><br>\n'
      for h in listaHosts:
         status = h.getStatus()
         #se for DESCONHECIDO (cinza)
         if status == 1:
            contentHtml += '<br><img src="images/unknown.png"><br><font color="#5a4e4e"> O Host ' + h.getName() + ' está com status DESCONHECIDO</font><br><br>\n'
         #se for host FALHO (vermelho)
         elif status == -1:
            contentHtml += '<br><img src="images/fault.png"><br><font color="#d41414"> O Host ' + h.getName() + ' está com status FALHO</font><br><br>\n'
         #sem falha (verde)
         else:
            contentHtml += '<br><img src="images/nofault.png"<br><font color="#0f9b00"> O Host ' + h.getName() + ' está com status SEM FALHA</font><br><br>\n'
      contentHtml += '<br><body>\n'
      return contentHtml

   #gera o rodapé
   def getFooter(self):
      footer = '</html>\n'
      return footer
