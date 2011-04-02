#!/usr/bin/env python
# -*- coding: utf-8 -*-

import threading
from functions import *
from Pacote import *
import time
from host import *
from msg import *


#classe que define propriedades e métodos de cada thread de monitoramento
class MyThread( threading.Thread ):
   
   #definições iniciais das propriedades
   def __init__(self,host_obj,server,cont,log):
      threading.Thread.__init__(self)
      self.__serv = server
      self.__host=host_obj
      self.__packet=Pacote(1,0,0)
      self.__host_id = cont
      self.__server_log = log

   #executa a função de monitoramento
   def run( self ):
      while(True):
         print 'Fazendo ping no host;' , self.__host.getName()
         self.__status=ping(self.__host.getName())
         self.__server_log.setMsg(MSG_PING.format(self.__host.getName()))
         self.__server_log.writeLog()
         self.__status_before = self.__host.getStatus() 
         if self.__status==2:
			   self.__status=DESCONHECIDO
         #se status for alterado, avisa o cliente
         if self.__status_before != self.__status:
            self.__packet.setHostID(self.__host_id)
           
            #tratando as mudanças de estado
            if ((self.__status_before == DESCONHECIDO) and (self.__status == ATIVO)):
               self.__host.setStatus(ATIVO)
               if self.__host.getIp == 0:
                  self.__host.setIp = resolveHost(self.__host.getName())
               #print 'O host' , self.__host.getIp() , 'mudou para ATIVO'
               self.__server_log.setMsg(MSG_CHANGE_STATUS.format(self.__host.getName(),'ATIVO'))
               self.__server_log.writeLog()
            elif ((self.__status_before == ATIVO) and (self.__status == DESCONHECIDO or self.__status == 2)):
               self.__host.setStatus(FALHO)
               self.__server_log.setMsg(MSG_CHANGE_STATUS.format(self.__host.getName(),' FALHO'))
               self.__server_log.writeLog()
               #print 'O host' , self.__host.getIP() , 'mudou para FALHO'
            elif ((self.__status_before == FALHO) and (self.__status ==ATIVO)):
               self.__host.setStatus(ATIVO)
               self.__server_log.setMsg(MSG_CHANGE_STATUS.format(self.__host.getName(),'ATIVO'))
               self.__server_log.writeLog()
               #print 'O host' , self.__host.getIp() , 'mudou para ATIVO'
            else:
               self.__host.setStatus(DESCONHECIDO)
               self.__server_log.setMsg(MSG_CHANGE_STATUS.format(self.__host.getIp(),' DESCONHECIDO'))
               self.__server_log.writeLog()
               #print 'O host' , self.__host.getIp() , 'mudou para DESCONHECIDO'
            self.__packet.setData(self.__host.getStatus())
            self.__data_send=serialize(self.__packet)
            self.__serv.sendData(self.__data_send)
         time.sleep(30)
