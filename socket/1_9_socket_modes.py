#!usr/bin/env python
#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

import socket

def socket_modes():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	# setup blocking
	# s.setblocking(1)	
	# setup nonblocking	
	s.setblocking(0)
	s.settimeout(0.5)
	# s.bind(('127.0.0.1', 0))
	s.bind(('127.0.0.1', 8080))

	socket_address = s.getsockname()
	print "Trivial Server launched on socket: %s" % str(socket_address)
	while(1):
		s.listen(1)

if __name__ == '__main__':
	socket_modes()