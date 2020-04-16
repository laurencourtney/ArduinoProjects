
''' 
This file should run on the host laptop as a client, it will continously receive IMU data from the Raspberry Pi and print it to the screen
'''
import socket

print("Running")
TCP_IP = '192.168.1.223' #IP of the Raspberry Pi
TCP_PORT = 5005
BUFFER_SIZE = 4096
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

while True :
    data = s.recv(BUFFER_SIZE)
    print(str(data))