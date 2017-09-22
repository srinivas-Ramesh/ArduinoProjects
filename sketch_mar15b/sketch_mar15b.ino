#include <SoftwareSerial.h>

SoftwareSerial SSerial(3,2);// connect pin 2(software TX of arduino) to RX , pin 3(software RX of arduino) to TX of WIFI module

#define WIFI_ID "AndroidAP" //name of the wifi connection
#define PASS "dgvu5852"  // password of the wifi connection

void setup() {
  
     initializeSystem();
     
     //checkWIFIModule();
     
     //resetWIFI();  

     //connectTOWIFI();
}

void loop() {
   while(Serial.available() > 0){
    SSerial.write(Serial.read());
   }

   while(SSerial.available()>0) {
     Serial.write(SSerial.read());
     }
}



void initializeSystem(){
     Serial.begin(115200);
     while (!Serial);
     SSerial.begin(115200);//115200 baud rate works for wifi module. try changing the baud rate to 9600 or other rates, if 115200 doesn't work.
     while (!SSerial);
     Serial.println(F("ESP8266 initialization on Arduino Uno"));
     SSerial.flush();// clear the software serial buffer  
}

void checkWIFIModule(){
  SSerial.println("AT");
  if(SSerial.find("OK"));
  Serial.println(F("WIFI module identified"));
  while(SSerial.available()>0) {
  Serial.write(SSerial.read());
  }
}

void resetWIFI(){
    Serial.println(F("Resetting WIFI Module"));
    SSerial.println("AT+RST");//wifi module reset command
    delay(5000);
    while(SSerial.available()){
    Serial.write(SSerial.read());
    }
}


void connectTOWIFI(){

  String cmd="AT+CWJAP=\"";
       cmd+=WIFI_ID;
       cmd+="\",\"";
       cmd+=PASS;
       cmd+="\"";
  Serial.println(cmd);
  SSerial.println(cmd);
  delay(5000);
  while(SSerial.available()){
    Serial.write(SSerial.read());
    }
}

void makeGetCall(String URL){
  
}



