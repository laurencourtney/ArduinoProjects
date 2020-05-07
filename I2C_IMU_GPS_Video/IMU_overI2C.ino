#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>

/* This will use the Adafruit BNO055 library to get IMU data, 
 *  it will assign an address of 0x04 to the Arduino which will
 *  be the slave in an I2C connection with the Rasberry Pi. It 
 *  will send the IMU data over this Wire connection. 
 */

Adafruit_BNO055 bno = Adafruit_BNO055(55);

int addr = 0x04;

//data to send to RPi
char imu_data[256];

char roll[32];
char pitch[32];
char yaw[32];

//sends the IMU data to the RPi
void sendIMUData() {
  Wire.write(imu_data);
}

void setup() {
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  
  Serial.println("Orientation Sensor Data"); Serial.println("");

  if (!bno.begin())
  {
    Serial.print("Oops, no BNO055 detected, check wiring or I2C addr");
    while(1);
  }
  delay(1000);
  
  bno.setExtCrystalUse(true); //set up BNO sensor

  Wire.begin(addr); //set up wire

  //callbacks for I2C
  Wire.onRequest(sendIMUData); //send the IMU data when requested
}

void loop() {
  //get a new sensor event
  sensors_event_t event;
  bno.getEvent(&event);
  dtostrf(event.orientation.x, 5, 2, yaw);
  Serial.println(yaw);
  dtostrf(event.orientation.y, 5, 2, pitch);
  Serial.println(pitch);
  dtostrf(event.orientation.z, 5, 2, roll);
  Serial.println(roll);
  sprintf(imu_data, "%s|%s|%s", yaw, pitch, roll);
  Serial.println(imu_data);
  delay(100);

}
