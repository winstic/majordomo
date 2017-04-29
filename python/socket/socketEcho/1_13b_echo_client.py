#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

## 目的让设备与服务器之间的时间同步，需要ntplib模块（pip、easy_install、）

import socket
import argparse

host = 'localhost'

def echo_client(port):
	""" A simple echo client """
	# Create a TCP/IP socket
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	# Connect the socket to server
	server_address = (host, port)
	print "Connect to %s port %s" % server_address
	sock.connect(server_address)

	# Send data
	try:
		message = "Test Message. This will be echoed"
		print "Sending %s" % message
		sock.sendall(message)

		# Look for the response
		amount_received = 0;
		amount_expected = len(message)
		while amount_received < amount_expected:
			data = sock.recv(16)
			amount_received += len(data)
			print "Received: %s" % data
	except socket.errno, e:
		print "Socket error: %s" % str(e)
	except Exception, e:
		print "other exception: %s" % str(e)
	finally:
		print "Closeing connection to the server"
		sock.close()



if __name__ == '__main__':
	parser = argparse.ArgumentParser(description = 'Socket Client Example')
	parser.add_argument('--port', action = 'store', dest = 'port', type = int, required = True)
	given_args = parser.parse_args()
	port = given_args.port
	echo_client(port)