#!/usr/bin/env python

#importando classes
from socket import *
import sys
import os

#variaveis necessarias para o socket TCP
BUFSIZ = 4096
HOST = 'localhost'
PORT = 6666
ADDR = (HOST,PORT)

#classe do servidor
class ServMonitor:
   #metodo para as propriedades principais do servidor
   def __init__(self):
      #cria socket tcp
      self.__serv = socket( AF_INET,SOCK_STREAM)
      #vincula host,port do servidor
      self.__serv.bind((ADDR))
      self.__serv.listen(5)
      self.__cli = None
      #variavel para mostrar que a escuta esta ocorrendo
      self.__imListening  = 0
      #variavel para mostrar a execucao de comandos solicitados pelo cliente
      self.__imProcessing = 0
      self.__run()

   #metodo que executa escuta e processamento de comando do cliente
   def __run(self):
      self.__imListening = 1
      while self.__imListening:
         self.__listen()
         self.__imProcessing = 1
         while self.__imProcessing:
            self.__procCmd()
         #fecha o socket do cliente
         self.__cli.close()
      #fecha o socket do servidor
      self.__serv.close()

   #metodo que processa a escuta do cliente
   def __listen(self):
     
      print '...escutando...'
      #recebe a conexao do cliente (tupla: instancia,endereco IP)
      cli,addr = self.__serv.accept()
      self.__cli = cli
      print '...conectando com: ', addr

   def __procCmd(self):
      #recebe dados do cliente
      cmd = self.__cli.recv(BUFSIZ)
      if not cmd:
         print 'nenhum comando recebido'
         return
      print 'comando recebido: ', cmd
      self.__servCmd(cmd)
      if self.__imProcessing: 
         #executa comando
         proc = os.popen(cmd)
         #le retorno do comando
         outp = proc.read()
         if outp:
            #envia ao cliente o retorno
            self.__cli.send(outp)
         else:
            self.__cli.send('nada retornado para o comando solicitado')

   def __servCmd(self,cmd):
      cmd = cmd.strip()
      if cmd == 'BYE': 
         self.__imProcessing = 0

#instancia servidor
if __name__ == '__main__':
   serv = ServMonitor()
