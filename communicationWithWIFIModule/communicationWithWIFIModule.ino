/*
  Software serial multple serial test

  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.

  The circuit:
   RX is digital pin 10 (connect to TX of other device)
   TX is digital pin 11 (connect to RX of other device)

  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

  Not all pins on the Leonardo support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  created back in the mists of time
  modified 25 May 2012
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
//  Serial.println(F("serial comm with monitor ready"));
//  //mySerial.println("AT");
//  mySerial.write("AT+CMGF=1\r\n");
//  delay(1000);
//  mySerial.write("AT+CMGS=\"+918892164516\"\r\n");
//  delay(1000);
//  mySerial.write("hello Pradeep ,I'm Arduino Microcontroller. How are you doing?");
//  delay(1000);
//  mySerial.write(0X1A);
//  delay(20000);
}

void loop() {

  // run over and over
  while (Serial.available()) {
    //if( Serial.read ()== '|') mySerial.write((char)26);
    //Serial.write(Serial.read());
    mySerial.write(Serial.read());
  }

  while (mySerial.available())
    Serial.write(mySerial.read());

}

