#!/usr/bin/env python
# -*- coding: utf-8 -*-

#importando classes

from socket import *
import sys
import os
import time

#biblioteca local
sys.path.append( 'library' )
from host import *
from functions import *
from Pacote import *
from threado import *
from Log import *
from msg import *

#variaveis necessarias para o socket TCP
BUFSIZ = 4096
PACKNUMBER = '4' #numero de pacotes que o ping envia

#classe do servidor
class ServMonitor:
   global server_log
    #metodos para as propriedades principais do servidor
   def __init__(self,port):
      #cria socket tcp
      self.__serv = socket(AF_INET,SOCK_STREAM)
      self.__server = resolveHost(gethostname())
      
      print '\nIP do server ', self.__server , '\n'
      
      self.ADR=(self.__server,port)

      # evita impedir "bindar" um socket apos interromper uma execucao anterior (processo zumbi). Ver man 7 socket
      self.__serv.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1 )
      self.__serv.bind(self.ADR)
      self.__serv.listen(1)
      self.__cli = None

      self.__run()

   #metodo que executa escuta e processamento de comando do cliente
   def __run(self):
      self.__listen()

   #metodo para escuta da conexao tcp
   def __listen(self):
      print '...escutando...'

      #recebe a conexao do cliente (tupla: instancia,endereco IP)
      try:
         cli,addr = self.__serv.accept()
         self.__cli = cli
      except:
         server_log.setMsg(MSG_CONFAIL(addr[0]))
         server_log.writeLog()
      server_log.setMsg(MSG_CONNECT.format(addr[0]))
      server_log.writeLog()


   #metodo para receber os  dados
   def recData(self):      
      data = self.__cli.recv(BUFSIZ)
      if not data:
         print 'Nenhum dado recebido!'
      return data
   
   def getDesc(self):
      return self.__serv

   def sendData(self, data):
      self.__cli.send(data)

   def closeClient(self):
      self.__cli.close()

   def closeServer(self):
      self.__serv.close()

   def closeAll(self):
      self.closeClient()
      self.closeServer()
      
#instancia servidor
if __name__ == '__main__':

   #prepara arquivo de log
   server_log=log("server.log")
   server_log.openFile()

   # Função que exibe na tela a forma correta de uso do programa
   def usage():
      print "Erro!" 
      print "Forma de uso: " + sys.argv[0] + " <porta>"

   # Verifica o número de parametros do programa
   if len( sys.argv ) != 2:
      usage()
      sys.exit( 1 )

   #prepara variaveis para execucao do servidor
   porta=int(sys.argv[1])
   serv = ServMonitor(porta)
   data=serv.recData()
   packet = unserialize(data)
   hosts_list = packet.getData()
   server_log.setMsg(MSG_LISTREC.format(hosts_list))
   server_log.writeLog()
   objhosts = []
   print hosts_list
   #resolve hosts e coloca-os em uma lista
   for host in hosts_list:
         temp_ip=resolveHost(host.strip())
         temp_host = Host(temp_ip,host.strip())
         objhosts.append(temp_host)
   
   packet.setCode(0)
   obj_send = serialize(objhosts)
   serv.sendData(obj_send)
   '''
   while(True):
      cont = 0 
      
      for temp_host in objhosts:
         status= ping(host.strip())
         print 'O host ' , temp_host.getIp() ,' retornou ' , status
         status_before = temp_host.getStatus()
         if status_before != status:
            packet.setData(status)
            packet.setHostID(cont)
            data_send=serialize(packet)
            serv.sendData(data_send)
            if ((status_before == DESCONHECIDO) and (status == ATIVO) ):
               
               print 'O host' , temp_host.getIp() , 'mudou para ativo'
               temp_host.setStatus(ATIVO)
            elif ((status_before == ATIVO) and (status == DESCONHECIDO) ):
               temp_host.setStatus(FALHO)
            elif ((status_before == FALHO) and (status ==ATIVO) ):
               temp_host.setStatus(ATIVO)
            else:
               temp_host.setStatus(DESCONHECIDO)
            
         time.sleep(2)
         cont += 1
   '''
   packet.setCode(1)
   #abre as threads para monitorar cada host de maneira independente
   cont=0
   for temp_host in objhosts:
      MyThread(temp_host,serv,cont,server_log).start()
      print 'Comecando thread do ' , temp_host.getName()      
      cont += 1
