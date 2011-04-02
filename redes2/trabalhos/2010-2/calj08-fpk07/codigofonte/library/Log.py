#!/usr/bin/env python
# -*- coding: utf-8 -*-

from time import *

#classe que define propriedades e métodos dos logs
class log:
   #formato padrão de tempo a ser gravado no arquivo)
	__timeformat=strftime("%a, %d %b %Y %H:%M:%S: ", localtime())

   #recebe o nome do arquivo de log
	def __init__(self,arquivo):
		self.__log_file = arquivo

   #escreve no arquivo de log
	def writeLog(self):
		self.__timeformat=strftime("%a, %d %b %Y %H:%M:%S: ", localtime())
		self.__file.write(self.__timeformat + self.__msg + '\n')

   #configura a mensagem que possivelmente será escrita
	def setMsg(self,message):
		self.__msg = str(message)
   
   #recupera a mensagem que possivelmente seria escrita
	def getMsg(self):
		return self.__msg

   #abre arquivo de log
	def openFile(self):
		self.__file=open(self.__log_file , 'a')
	
   #fecha arquivo de log
	def closeFile(self):
		self.__file.close()
