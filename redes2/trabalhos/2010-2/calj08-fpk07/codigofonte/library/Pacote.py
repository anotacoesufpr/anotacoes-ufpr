#!/usr/bin/env python
# -*- coding: utf-8 -*-

#classe os objetos pacote
class Pacote:
   #definicões iniciais
	def __init__(self,code,host,data):
		self.__message_code = code
		self.__hostID = host
		self.__data_send = data

   #recupera dados do pacote
	def getData(self):
		return self.__data_send

   #recupera ID do host
	def getHostID(self):
		return self.__hostID
	
   #recupera código que indica mudança de estado no host do pacote
	def getCode(self):
		return self.__message_code

   #configura novos dados do objeto pacote
	def setData(self,data):
		self.__data_send=data

   #configura hostID da lista de hosts para localizar esse host mais facilmente na lista de hosts
	def setHostID(self,id_host):
		self.__hostID=id_host

   #configura código que indica mudança de estado no host do pacote
	def setCode(self,code):
		self.__message_code=code
