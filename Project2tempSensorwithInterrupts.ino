#include <dht.h> //DHT11.zip library

dht DHT;
unsigned long time;
int chk;
double celc;
double fahr;
volatile boolean get_temp = true; 
volatile int seconds = 0; //volatile so it can be used in the interrupt

#define DHT11_PIN 7

void setup() 
{
  Serial.begin(9600);
  //stop interrupts
  cli();
  //setup the timer4 interrupt at 1Hz
  TCCR4A = 0; //set this register to 0
  TCCR4B = 0; //set this register to 0
  TCNT4 = 0; //initialize counter value to 0
  // set compare match register for 1Hz increments
  OCR4A = 15624/1; // (16*10^6) / (1*1024) - 1 < 65536 to fit 16 bit timer
  //turn on CTC mode
  TCCR4B |= (1 << WGM12);
  //set CS12 and CS10 bits for 1024 prescalar (allows for 1Hz)
  TCCR4B |= (1 << CS12) | (1 << CS10);
  //enable timer compare interrupt
  TIMSK4 |= (1 << OCIE4A);
  //allow interrupts
  sei();
}

ISR(TIMER4_COMPA_vect)
{
  seconds++;
  if (seconds % 10 == 0)
  {
    get_temp = true;
  }
  else 
  {
    get_temp = false;
  }
}

void loop() {
  if (get_temp == true) 
  {
    time = seconds; //time = millis() / 1000 is also an option
    chk = DHT.read11(DHT11_PIN);
    celc = DHT.temperature;
    fahr = celc * 1.8 + 32;
    Serial.print(time);
    Serial.print(", ");
    Serial.println(fahr);
    get_temp = false;
  }
}
  
