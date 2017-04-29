#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

import socket

def modify_socket_timeout():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	#settimeout参数可以是浮点数秒或None，None表示的是禁用套接字操作的超时检测
	print "Default socket timeout: %s" % s.gettimeout()
	s.settimeout(100)
	print "Current socket timeout: %s" % s.gettimeout()

if __name__ == '__main__':
	modify_socket_timeout()