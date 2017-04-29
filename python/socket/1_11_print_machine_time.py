#!usr/bin/env python
# -*- coding: utf-8 -*-

#Python Networking Programming
#This program is optimized for Python 2.7. 
#It may run on any other Python with/without modifications.
##Date:2017-02-16 by wengzc

## 目的让设备与服务器之间的时间同步，需要ntplib模块（pip、easy_install、）

import ntplib
from time import ctime

def print_machine_time():
	ntp_client = ntplib.NTPClient()
	response = ntp_client.request('3.cn.pool.ntp.org')
	print ctime(response.tx_time)

if __name__ == '__main__':
	print_machine_time()