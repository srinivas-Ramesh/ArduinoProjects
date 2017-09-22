#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

byte id_store[2]= {0xF2 , 0xB5};


void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  byte gain = 0x70;
  Serial.println(F("setting the gain to 48db (MAX)"));
  rfid.PCD_SetAntennaGain(gain);
  Serial.println(F("Starting the scan for rfid cards"));
  
  int id_counter = 0;
  boolean tag =0, key_chain =0;

}

void loop() {
    
if ( ! rfid.PICC_IsNewCardPresent())
    return;
if ( ! rfid.PICC_ReadCardSerial())
    return;

 MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 Serial.println(rfid.PICC_GetTypeName(piccType));
 
if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    
    return;
  }
    
    if (rfid.uid.uidByte[0] == id_store[0]){
    
    Serial.println("rf tag is present");
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    return;
    }

    if (rfid.uid.uidByte[0] == id_store[1]){
    Serial.println("rf key chain is present");
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    return;
    }
    
    if (rfid.uid.uidByte[0] != id_store[0] || rfid.uid.uidByte[0] != id_store[1] ){
      Serial.println("new rf tag is present");
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      return;
    }
  }
  
    

