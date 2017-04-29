#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
#Date:2017-02-16 by wengzc

import socket

def get_remote_machine_info():
	remote_host = 'www.python.org'
	try:
		print "Ip address: %s" % socket.gethostbyname(remote_host)
	except socket.error, err_msg:
		print "%s: %s" % (remote_host, err_msg)

if __name__ == '__main__':
	get_remote_machine_info()