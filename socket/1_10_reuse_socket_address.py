#!usr/bin/env python
#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

import sys
import socket

def reuse_socket_addr():
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# Get the old state of the SO_REUSEADDR option
	old_state = sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)
	print "Old sock state: %s" % old_state

	# Enable the SO_REUSEADDR option
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	new_state = sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)
	print "New sock state: %s" % new_state

	local_port = 8096

	srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	srv.bind(('', local_port))
	srv.listen(1)
	print "Listening on port: %s" % local_port
	while True:
		try:
			connection, addr = srv.accept()
			print "Connected by %s:%s" % (addr[0], addr[1])
		except KeyboardInterrupt:
			break
		except socket.error, e:
			print "%s" % (msg,)


if __name__ == '__main__':
	reuse_socket_addr()