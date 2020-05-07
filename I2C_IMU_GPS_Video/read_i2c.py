#! /usr/bin/python

# This script requests I2C data from the Arduino at address 4 and parses the data to
# return yaw, pitch, and roll, which it prints to the screen. 

import smbus
from time import sleep

addr = 0x04
bus = smbus.SMBus(1)

sleep(2)

while True:
    try:
	data = bus.read_i2c_block_data(addr, 0, 32)
	long_str = ""
	for d in data:
	    if d != 255 :
		long_str += chr(d)
	vals = long_str.split('|')
	print("Yaw: " + vals[0] + ", Pitch: " + vals[1] + ", Roll: " + vals[2])
    except IOError as error :
	print(error)
    except IndexError as error :
	print(error)
    sleep(1)