/*
 * SMART RETAIL SHOPPPING
 * 
 * AUTHOR: SRINIVAS RAMESH RAO
 */


/* ---------------------------------
 *        PIN CONFIGURATION
 *  
 *             MFRC522      Arduino       
 *             Reader/PCD   Uno           
 * Signal      Pin          Pin           
 * ---------------------------------
 * RST/Reset   RST          9             
 * SPI SS      SDA(SS)      10            
 * SPI MOSI    MOSI         11  
 * SPI MISO    MISO         12    
 * SPI SCK     SCK          13  
 */

#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

SoftwareSerial SIM900Serial(6, 7); // RX, TX

MFRC522 rfid(SS_PIN, RST_PIN); 

MFRC522::MIFARE_Key key;

byte nfcId[3];

boolean item_in_basket_status = false;

void setup() {

  Serial.begin(9600);

  SIM900Serial.begin(9600);
  
  SPI.begin();
  
  rfid.PCD_Init();
  
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  initializeSIM900();
  
}

void loop() {

    //verify if new tag is present
    if ( !rfid.PICC_IsNewCardPresent())
      return;

    // Verify if the tag has been read
    if ( !rfid.PICC_ReadCardSerial())
      return;


    if (rfid.uid.uidByte[0] != nfcId[0] || rfid.uid.uidByte[1] != nfcId[1] || rfid.uid.uidByte[2] != nfcId[2] || 
        rfid.uid.uidByte[3] != nfcId[3]) {
      
      Serial.println(F("An item has been detected in the basket."));

      // Store NUID into nfcId array
      for (byte i = 0; i < 4; i++) {
        nfcId[i] = rfid.uid.uidByte[i];
      }
      
      //printHex(rfid.uid.uidByte, rfid.uid.size);

      sendDataToServer(rfid.uid.uidByte, rfid.uid.size);
      
      Serial.println();
    }
    
    else {
      //printHex(rfid.uid.uidByte, rfid.uid.size);
    }
    

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}



void initializeSIM900(){

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
