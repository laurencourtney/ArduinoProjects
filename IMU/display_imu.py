#! /usr/bin/env python
'''
This prints IMU data from the Arduino
'''
import serial

ser = serial.Serial('/dev/ttyACM0', 9600) #the port the Arduino is connected to

while True:
    data = ser.readline()
    print(data)

