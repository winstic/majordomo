#!usr/bin/env python
#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

import socket

def convert_integer():
	data = 1234
	#32-bit, host byte order, network byte order
	hborderl = socket.ntohl(data)
	nborderl = socket.htonl(data)
	print "Original data: %s => Long host byte order: %s => Long network byte order: %s" % (data, hborderl, nborderl)

	#16-bit, host byte order, network byte order
	hborders = socket.ntohs(data)
	nborders = socket.htons(data)
	print "Original data: %s => short host byte order: %s => short network byte order: %s" % (data, hborders, nborders)


if __name__ == '__main__':
	convert_integer()