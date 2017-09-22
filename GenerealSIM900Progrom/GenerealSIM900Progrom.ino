#include <SoftwareSerial.h>


SoftwareSerial SIM900Serial(6, 7); // RX, TX


void setup() {
 // put your setup code here, to run once:
  Serial.begin(9600);
  SIM900Serial.begin(9600);

  Serial.println(F("Initializing SIM900 for HTTP connection"));
  
  SIM900Serial.println("AT+SAPBR = 3,1,\"Contype\",\"GPRS\"");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+SAPBR = 3,1,\"APN\",\"Airtel Internet\"");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());
  
  SIM900Serial.println("AT+SAPBR = 1,1");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+SAPBR = 2,1");

  delay(2000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+HTTPINIT");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+HTTPSSL = 1");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+HTTPPARA = \"CID\",1");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+HTTPPARA = \"URL\",\"https://smartshopi322373trial.hanatrial.ondemand.com/smartshop/app/items\"");//httpbin.org/post

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+HTTPPARA = \"CONTENT\",\"text/plain\"");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());
  Serial.println(F("SIM900 module ready"));
}

void loop() {
  // put your main code here, to run repeatedly:
sendDataToServer("Hello", 5);
}

void sendDataToServer(byte *data, byte dataSize){

  //Serial.print("dataSize is :");
  //Serial.println(dataSize);

  SIM900Serial.print("AT+HTTPDATA = ");
  SIM900Serial.print(dataSize);
  SIM900Serial.println(",15000");

  delay(1000);
  
  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  //SIM900Serial.println("Hello");
  for (byte i = 0; i < dataSize; i++) {
    SIM900Serial.print(data[i],DEC);
  }
  SIM900Serial.println();

  delay(1000);

  SIM900Serial.println("AT+HTTPACTION =1");

  delay(5000);

  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());

  SIM900Serial.println("AT+HTTPREAD");

  delay(1000);

  while (SIM900Serial.available())
  Serial.write(SIM900Serial.read());
}

