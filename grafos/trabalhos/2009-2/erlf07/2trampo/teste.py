#!/usr/bin/env python
#-*- coding: utf-8 -*-

import sys

print "recebi %d parametros" % (len(sys.argv)-1)

for i in range(1,len(sys.argv)):
	print sys.argv[i]


