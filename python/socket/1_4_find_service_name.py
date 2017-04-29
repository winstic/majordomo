#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

import socket

def find_service_name():
	for port in [80, 25, 53]:
		print "Port: %s => service name: %s" % (port, socket.getservbyport(port))
	print "Port: %s => service name: %s" % (80, socket.getservbyport(80, 'tcp'))
	print "Port: %s => service name: %s" % (25, socket.getservbyport(25, 'tcp'))
	print "Port: %s => service name: %s" % (53, socket.getservbyport(53, 'udp'))

if __name__ == '__main__':
	find_service_name()