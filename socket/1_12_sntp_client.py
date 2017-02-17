#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

## 目的让设备与服务器之间的时间同步，不使用第三方库
## 使用UDP(SOCK_DGRAM) 连接服务器

import sys
import socket
import struct
import time

NTP_SERVER = "0.cn.pool.ntp.org"
TIME1970 = 2208988800L 

def sntp_client():
	client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	data = '\x1b' + 47 * '\0'
	client.sendto(data, (NTP_SERVER, 123))
	data, address = client.recvfrom(1024)
	if data:
		print "Response received from:", address
	t = struct.unpack('!12I', data)[10]
	t -= TIME1970
	print "\tTime=%s" % time.ctime(t)

if __name__ == '__main__':
	sntp_client()