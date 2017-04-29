#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
#Date:2017-02-16 by wengzc

import socket
from binascii import hexlify

def ip4_conversion():
	ip_address = '127.0.0.1'
	packed_ip_address = socket.inet_aton(ip_address)
	unpacked_ip_address = socket.inet_ntoa(packed_ip_address)
	print "IP Address: %s" % ip_address, type(ip_address)
	print "Packed Address: %s" % packed_ip_address, type(packed_ip_address)
	print "Packed Address Hexlify: %s" % hexlify(packed_ip_address), type(hexlify(packed_ip_address))
	print "Unpacked Address: %s" % unpacked_ip_address, type(unpacked_ip_address)

if __name__ == '__main__':
	ip4_conversion()