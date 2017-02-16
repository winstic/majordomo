#!usr/bin/env python
#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

import socket

def print_machine_info():
	host_name = socket.gethostname()
	ip_address = socket.gethostbyname(host_name)
	print "Host name: %s" % host_name
	print "Ip Address: %s" % ip_address

if __name__ == '__main__':
	print_machine_info()