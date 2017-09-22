#include "DHT.h"

#define DHTPIN 7

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

/*
 * Global Constants
 */
int value;
byte tempSensorInput = 5;     //input to temperature sensor is 5V


void setup() {
   Serial.begin(9600);
   dht.begin();
}

void loop() {
  value = analogRead(0);
  Serial.print(readTemperature(value));
  Serial.print("\t"); 
  Serial.print(dht.readHumidity());
  Serial.print("\t"); 
  Serial.println(analogRead(5));
  delay(1000);
}


/*
 * read the value from analog input and convert it to temperature
 */

float readTemperature(float  value){

float temp = (value * tempSensorInput * 100)/1023; //max reading it 1023, not 1024. thus divide by 1023;
return temp;
}

