#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
from os import curdir, sep
import socket
import time
PORT_NUMBER = 8080



#This class will handles any incoming request from
#the browser
class myHandler(BaseHTTPRequestHandler):

	#Handler for the GET requests
	def do_GET(self):
		print  self.path

		try:
			if self.path=="/":
				self.path="/index.html"
			#communication avec le serveur qui prend les photos
			elif self.path =="/prendrePhoto":


				s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				s.connect(("127.0.0.1", 1977))
				s.send("p")
				s.send("p")
				s.close()
				return

			#communication avec le serveur qui controlle les servos moteurs

			elif self.path =="/tournerGauche":


					s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
					s.connect(("127.0.0.1", 5000))
					msgServer = s.recv(1024)
					s.send("1,10,10")
					s.close()
					return


			elif self.path =="/tournerDroite":

					s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
					s.connect(("127.0.0.1", 5000))
					msgServer = s.recv(1024)
					s.send("2,10,10")
					s.close()
					return

		except Exception:
				print "erreur de connexion"
				return
		try:
			#Check the file extension required and
			#set the right mime type

			sendReply = False
			if self.path.endswith(".html"):
				mimetype='text/html'
				sendReply = True
			if self.path.endswith(".jpg"):
				mimetype='image/jpg'
				sendReply = True
			if self.path.endswith(".jpeg"):
				mimetype='image/jpg'
				sendReply = True
			if self.path.endswith(".gif"):
				mimetype='image/gif'
				sendReply = True
			if self.path.endswith(".js"):
				mimetype='application/javascript'
				sendReply = True
			if self.path.endswith(".css"):
				mimetype='text/css'
				sendReply = True
			if self.path.endswith(".txt"):
				f= open("test.txt","a")
				f.write("ok")
				f.close()

				mimetype='text/txt'
				sendReply = True
			if sendReply == True:
				#Open the static file requested and send it
				f = open(".." + sep + self.path)
				self.send_response(200)
				self.send_header('Content-type',mimetype)
				self.end_headers()
				self.wfile.write(f.read())
				f.close()
			else :
				return
			return


		except IOError:
			self.send_error(404,'File Not Found: %s' % self.path)

try:
	#Create a web server and define the handler to manage the
	#incoming request
	server = HTTPServer(('', PORT_NUMBER), myHandler)
	print 'Started httpserver on port ' , PORT_NUMBER

	#Wait forever for incoming htto requests
	server.serve_forever()

except KeyboardInterrupt:
	print '^C received, shutting down the web server'
	server.socket.close()
