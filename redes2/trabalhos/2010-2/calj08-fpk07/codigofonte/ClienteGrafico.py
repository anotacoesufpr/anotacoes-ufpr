#!/usr/bin/env python
# -*- coding: utf-8 -*-

#importando classes
import sys
sys.path.append('library')
from socket import *
from time import time
from time import sleep

from Pacote import *
from functions import *
from Log import *
from msg import *
import gtk
import gobject


#variaveis necessarias para o socket TCP
BUFSIZ = 4096

#classe do cliente tcp
class ClientMonitor:
   global BUFSIZ
   def __init__(self,host,port):
      self.__HOST = host
      self.__PORT = port
      #cria o socket TCP
      self.__ADDR = (self.__HOST,self.__PORT)
      self.__sock = None

   def makeConnection(self):
      self.__sock = socket( AF_INET,SOCK_STREAM)
      self.__sock.connect(self.__ADDR)

   #enviando mensagem ao servidor
   def sendData(self, data):
      self.__sock.send(data)

   def recData(self):
      data = self.__sock.recv(BUFSIZ)
      if not data:
         print 'Nenhum dado recebido!'
         return False
      return data

#classe do cliente grafico
class MainWindow(gtk.Window):
   global servidor
   global porta
   def __init__(self):
      gtk.Window.__init__(self, gtk.WINDOW_TOPLEVEL)
      self.connect("destroy", self.quit)
      self.connect("delete_event", self.quit)
      self.show()

      self.set_usize(500, 210)
      self.main_box = gtk.VBox(False, 1)
      self.main_box.set_border_width(1)
      self.add(self.main_box)
      self.body()
      #self.server()
      self.main_box.show()

   def body(self):
      textbox = self.textbox = gtk.TextView()
      textbox.set_editable(True)
      self.main_box.pack_start(textbox, True, True, 0)
      textbox.show()

      entry = self.entry = gtk.Entry(1024)
      self.main_box.pack_start(entry, True, True, 0)
      entry.show()

      send = gtk.Button('Enviar')
      send.connect('clicked', self.send)
      self.main_box.pack_start(send, True, True, 0)
      send.show()

   def send(self, data=None, widget=None):
      #faz a leitura dos hosts na interface
      listaHosts = self.entry.get_text() 
      print listaHosts
      #executa a conexao com o servidor
      client = ClientMonitor(servidor,porta)
      client.makeConnection()

      #prepara envio dos hosts a serem monitorados
      packet = Pacote(0,None,listaHosts)
      packet_to_send = serialize(packet)

      #faz o envio
      client.sendData(packet_to_send)
      pack = None
      host_id = 0
      self.entry.set_text('')      

      #recebe os dados do servidor (servidor somente envia informacoes de
      #alteracao de status)
      while(True):
         rec_data=client.recData()
         if rec_data != None :
            pack = unserialize(rec_data)
            host_id = pack.getHostID()
            #gera log de mudanca de status
            client_log.setMsg(MSG_CHANGE_STATUS.format(listaHosts[host_id].strip(),pack.getData()))
            client_log.writeLog()
            print 'Recebido status do host: ' , listaHosts[host_id].strip()   

   def quit(self, *args):
      self.hide()
      self.destroy()
      gtk.main_quit()


#instancia o cliente
if __name__ == '__main__':

   #Função que exibe na tela a forma correta de uso do programa
   def usage():
      print "Erro!"
      print "Forma de uso: " + sys.argv[0] + ' <ip ou nome servidor>' + " <porta>"

   if len( sys.argv ) != 3 :
      usage()
      sys.exit( 1 )

   #configura as variaveis do cliente
   servidor=sys.argv[1]
   porta=int(sys.argv[2])

   #prepara arquivo de log
   client_log=log("client.log")
   client_log.openFile()
   client_log.setMsg(MSG_CONNECT.format(servidor))
   client_log.writeLog()

   #inicializa interface grafica
   MainWindow()
   gtk.main()
