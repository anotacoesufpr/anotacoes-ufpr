#!/usr/bin/env python
# -*- coding: utf-8 -*-

#variaveis de status
DESCONHECIDO = 1
ATIVO =0
FALHO = -1

#classe dos objetos Host
class Host:
   #status inicial DESCONHECIDO
	__statushost = DESCONHECIDO

	def __init__(self,ip,nome):
		self.__iphost = ip
		self.__namehost = nome

   #configura novo status		
	def setStatus(self,status):
		self.__statushost = status

   #configura ip		
	def setIp(self,ip):
		self.__iphost = ip

   #configura hostname		
	def setName(self,nome):
		self.__namehost = nome

   #recupera hostname
	def getName(self):
		return self.__namehost

   #recupera IP
	def getIp(self):
		return self.__iphost
		
   #recupera estado do monitoramento desse host
	def getStatus(self):
		return self.__statushost
		
	
		
