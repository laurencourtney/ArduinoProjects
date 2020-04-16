#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Arduino_FreeRTOS.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

//just one task for this assignment
void TaskImu( void *pvParameters );

void setup(void) 
{
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }

  Serial.println("Orientation Sensor Data"); Serial.println("");
  
  xTaskCreate(TaskImu
    , "IMU"
    , 256
    , NULL
    , 1
    , NULL); 

}

void loop(void) 
{
  //leave empty
}

void TaskImu( void *pvParameters ) 
{
  (void) pvParameters;

  /* Initialize the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055, check connections */
      Serial.print("Oops, no BNO055 detected, check wiring.");
      while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);

  for(;;)
  {
    /* get a new sensor event*/
    sensors_event_t event;
    bno.getEvent(&event);

    /* Display the data */
    Serial.print("Yaw: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tPitch: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tRoll: ");
    Serial.print(event.orientation.z, 4);
    Serial.println("");
    vTaskDelay(5);
  }
}
