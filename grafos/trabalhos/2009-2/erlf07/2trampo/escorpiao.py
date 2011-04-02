#!/usr/bin/env python
#-*- coding: utf-8 -*-

import sys

def le_stdin():

	try:
		num = raw_input("Qual o numero de vertices do grafo: ")
		if not num.isdigit():
			raise ValueError('Letras detectadas')
		num = int(num)
	except ValueError,ex:
		print "Digite apenas numeros."

	else:
		MATRIZ=[]
		for i in range(num):
			print "indice %d:" % i
			MATRIZ[i] = raw_input('linha[%d]: ' % i )
			print "Linha lida: %s" % MATRIZ[i]

	finally:
		return MATRIZ
		print "saindo"


# Abrindo arquivo
try:
	if (len(sys.argv) == 1):
		MATRIZ=le_stdin()
		print "MATRIZ= %s" % MATRIZ

	elif (len(sys.argv) == 2):
		MATRIZ=open("%s" % sys.argv[1],'r')
		MATRIZ=MATRIZ.readlines()
		# removendo os \n do arquivo
		MATRIZ = [i.split() for i in MATRIZ]
	else:
		raise Exception('Um ou zero arquivo como parametro!')

except Exception,ex:
	print "Deve passar 0 ou 1 parametro"
	sys.exit(1)


# List comprehension
# l = [i.strip() for i in l]





