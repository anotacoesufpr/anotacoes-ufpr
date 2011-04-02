#!/usr/bin/env python
# -*- coding: utf-8 -*-

from socket import * 
import os
import pickle

PACKNUMBER = '4' #numero de pacotes que o ping envia

#executa ping
def ping(host):
	system_ping = os.popen('ping -c ' + PACKNUMBER + ' -q ' + host + ' > /dev/null ; echo $?')
	status_ping=system_ping.readline()
	system_ping.close()	
	return int(status_ping)
	
#executa resolucao de nome
def resolveHost(hostname):
	try:
		ip = gethostbyname(hostname)					
	except:
		print 'Nao foi possivel resolver: ' , hostname
		return 0

		
	return ip
	
def serialize(obj):
	obj_string = pickle.dumps(obj)
	return obj_string

def unserialize(data):
	data_obj = pickle.loads(data)
	return data_obj
