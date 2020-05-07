from datetime import datetime
import gps 			#you may need to pip install this module first
import requests

# This script listens for gps data being sent by gpsd, parses that data, logs it to a file
# and prints lat and lon data. It runs on the host laptop but streams data from the RPi

dt = datetime.now()

#listen on port 2947 of gpsd, use the IP of your raspberry Pi

session = gps.gps("192.168.1.223", "2947")

session.stream(gps.WATCH_ENABLE | gps.WATCH_NEWSTYLE)

f = open("gps.log", "a+")

f.write(str(dt) + "\n")

while True :
    rep = session.next()
    try :
        if (rep["class"] == "TPV") :
            print(str(rep.lat) + "," + str(rep.lon))
            f.write(str(rep.lat) + str(rep.lon)+"\n")
    except Exception as e :
        print("Got exception " + str(e))