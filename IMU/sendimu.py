#! /usr/bin/env python
'''
This should run on the Raspberry Pi, it will send IMU data from the Arduino to the laptop over TCP, it starts up a TCP server
'''
import socket
import serial
TCP_IP = '192.168.1.223'
TCP_PORT = 5005
BUFFER_SIZE = 1024

ser = serial.Serial('/dev/ttyACM0', 9600) #the port the Arduino is connected to
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

conn, addr = s.accept()
print("Connection address:", addr)

while True:
    data = ser.readline()
    conn.send(data)

conn.close()

