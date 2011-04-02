#!/usr/bin/env python
# -*- coding: utf-8 -*-

#importando classes
from socket import *
from time import time
from time import sleep
import sys
import os
#biblioteca local
sys.path.append( 'library' )
from Pacote import *
from functions import *
from Log import *
from msg import *
from geraHtml import *

#variaveis necessarias para o socket TCP
BUFSIZ = 4096
NAVEGADOR ='firefox'
#classe do cliente
class ClientMonitor:
	def __init__(self,host,port):
		self.__HOST = host
		self.__PORT = port
		#cria o socket TCP
		self.__ADDR = (self.__HOST,self.__PORT)
		self.__sock = None

	def makeConnection(self):
		self.__sock = socket( AF_INET,SOCK_STREAM)
		self.__sock.connect(self.__ADDR)

	#enviando mensagem ao servidor
	def sendData(self, data):
		self.__sock.send(data)
   
	def recData(self):
		data = self.__sock.recv(BUFSIZ)
		if not data:
			print 'Nenhum dado recebido!'
			return False   
		return data

#instancia o cliente
if __name__ == '__main__':

   # Função que exibe na tela a forma correta de uso do programa
   def usage():
      print "Erro!" 
      print "Forma de uso: " + sys.argv[0] + ' <ip ou nome servidor>' + " <porta>" 
      
   if len( sys.argv ) != 3 :
      usage()
      sys.exit( 1 )

   #faz a leitura da entrada padrao
   servidor=sys.argv[1]
   porta=int(sys.argv[2])
   listaHosts=sys.stdin.readlines()
 
   #prepara arquivo de log
   client_log=log("client.log")
   client_log.openFile()
   
  
   #executa a conexao com o servidor
   client = ClientMonitor(servidor,porta)
	
   try:
      client.makeConnection()
   except:
      client_log.setMsg(MSG_CONFAIL.format(servidor))
      client_log.writeLog()
      sys.exit(1)

   client_log.setMsg(MSG_CONNECT.format(servidor))
   client_log.writeLog()
   #prepara envio dos hosts a serem monitorados
   packet = Pacote(0,None,listaHosts)
   packet_to_send = serialize(packet)

   client_log.setMsg(MSG_SENDHOST.format(listaHosts))
   client_log.writeLog()
   #faz o envio
   client.sendData(packet_to_send)
   pack = None
   host_id = 0

   #prepara a interface grafica
   interfaceGraphic = interface()
   

   #recebe lista de objetos de host do servidor
   rec_obj_hosts=client.recData()
   obj_hosts=unserialize(rec_obj_hosts)
   #liberar um pouco de memória 
   rec_obj_hosts=None
   interfaceGraphic.generate(obj_hosts)
   temp = os.popen(NAVEGADOR +' index.html &')
   #recebe os dados do servidor (servidor somente envia informacoes de
   #alteracao de status)
   try:
      while(True):
         rec_data=client.recData()
         if (rec_data != None) or (rec_data != "False"):
            pack = unserialize(rec_data)
            host_id = pack.getHostID()
            obj_hosts[host_id].setStatus(pack.getData())
            #gera log de mudanca de status
            if pack.getData() == ATIVO:
       		   client_log.setMsg(MSG_CHANGE_STATUS.format(listaHosts[host_id].strip(),'ATIVO'))
            elif pack.getData() == DESCONHECIDO: 
    		      client_log.setMsg(MSG_CHANGE_STATUS.format(listaHosts[host_id].strip(),'DESCONHECIDO'))
            else :
               client_log.setMsg(MSG_CHANGE_STATUS.format(listaHosts[host_id].strip(),'FALHO'))
            client_log.writeLog()
            print 'Recebido status do host: ' , listaHosts[host_id].strip() , ' que é ' , pack.getData()
            interfaceGraphic.generate(obj_hosts)
   except KeyboardInterrupt:
      client_log.setMsg(MSG_CLOSE.format(servidor))
      client_log.writeLog()
		
