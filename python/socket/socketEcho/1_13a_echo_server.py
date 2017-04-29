#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

## socket server

import sys
import socket
import argparse

host = 'localhost'
data_payload = 2048
backlog = 5

def echo_server(port):
	""" A simple echo server """
	# Create a TCP socket
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	# Enable reuse address/port
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# Bind the socket to the (address,port)
	server_address = (host, port)
	sock.bind(server_address)
	print "Starting up echo server on %s port %s" % server_address
	# Listen to clients, backlog argument specifies the max no. of queued connections
	sock.listen(backlog)
	while True:
		print "Waiting to receive message from client"
		client, address = sock.accept()
		data = client.recv(data_payload)
		if data:
			print "Data: %s" % data
			client.send(data)
			print "sent %s bytes back to %s" % (data, address)
		# end connection
		client.close()


if __name__ == '__main__':
	parser = argparse.ArgumentParser(description = 'Socket Server Example')
	parser.add_argument('--port', action = 'store', dest = 'port', type = int, required = True)
	given_args = parser.parse_args()
	port = given_args.port;
	echo_server(port)