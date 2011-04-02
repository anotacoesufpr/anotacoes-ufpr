#!/usr/bin/env python

#importando classes
from socket import *
from time import time
from time import sleep
import sys

#variaveis necessarias para o socket TCP
BUFSIZE = 4096

#classe do cliente
class ClientMonitor:
   def __init__(self,host):
      self.__HOST = host
      self.__PORT = 6666
      #cria o socket TCP
      self.__ADDR = (self.__HOST,self.__PORT)
      self.__sock = None

   def makeConnection(self):
      self.__sock = socket( AF_INET,SOCK_STREAM)
      self.__sock.connect(self.__ADDR)

   #enviando mensagem ao servidor
   def sendCmd(self, cmd):
      self.__sock.send(cmd)

   #recebendo a resposta do servidor
   def getResults(self):
      data = self.__sock.recv(BUFSIZE)
      print 'Resposta do servidor: ', data

#instancia o cliente
if __name__ == '__main__':
   conn = ClientMonitor('localhost')
   conn.makeConnection()
   conn.sendCmd('ping -c 2 -q google.com.br')
   conn.getResults()
   #fecha socket TCP

   conn.sendCmd('BYE')
