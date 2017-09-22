
#include <SoftwareSerial.h>

SoftwareSerial SIM900Serial(6, 7); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  SIM900Serial.begin(9600);
  Serial.println(F("serial comm with monitor ready"));
  SIM900Serial.println("AT");
}

void loop() {

  // run over and over
  while (Serial.available()) {
    //Serial.write(Serial.read());
    SIM900Serial.write(Serial.read());
  }

while (SIM900Serial.available())
    Serial.write(SIM900Serial.read());
  //ReadFromSIM900();

}

String ReadFromSIM900(){
  /*
   * post call commands
   * 
   * AT+SAPBR = 3,1,"Contype","GPRS"
   * AT+SAPBR = 3,1,"APN","TATA DOCOMO INTERNET"  //"Airtel Internet"
   * AT+SAPBR = 1,1
   * AT+SAPBR =2,1
   * AT+HTTPINIT
   * AT+HTTPPARA = "CID",1
   * AT+HTTPPARA = "URL","http://posttestserver.com/post.php"
   * AT+HTTPPARA = "CONTENT","text/plain"
   * AT+HTTPDATA = 100,100000
   * 
   * 100 refers to the number of charecters that we are going to input. and 100000 refers to 100 seconds of wait time to take the input. 
   * 
   * IMPORTANT NOTE:
   * --------------
   * Once we enter httpdata command it replies with download. then exactly 100 charecters needs to be fed into SIM900. Also note the carriage returns,spaces,new line charecters are to counted.
   * Thus only if the number given in HTTPDATA matches with the total number of charecters which was fed we get a OK response.
   * 
   * now go ahead and call the below command to make the post call.
   * AT+HTTPACTION =1
   * AT+HTTPREAD
   * 
   */
  
}

