  #include <SoftwareSerial.h>
   
   #define SSID "SAP-Internet"
   #define PASS "Savinirs@1994"
   #define DST_IP "220.181.111.85" //baidu.com
   SoftwareSerial SSerial(3, 2); // RX, TX
   void setup()
   {
     // Open serial communications and wait for port to open:
     //serial 2 is to esp8266 
     SSerial.begin(115200);//9600 (mine), 57600, 115200
     while (!SSerial);
     Serial.begin(9600);
     while (!Serial);
     Serial.println(F("ESP8266 Demo on Arduino Uno"));
    
      while(SSerial.available()>0)
      Serial.print( SSerial.read());
      SSerial.flush();
     //test if the module is ready
     SSerial.println("AT+RST");
     delay(1000);
     Serial.println(F("Resetting module"));

     while(SSerial.available()>0) {
    Serial.write(SSerial.read());
  }
     if(SSerial.find("Ready")||SSerial.find("ready"))
     {
       //dbgSerial.println("Module is ready");
       Serial.println("Module is ready");
     }
     else
     {  
       //dbgSerial.println("Module have no response.");
       Serial.println("Module have no response.");
     //  while(1);
     }
     delay(1000);
     //connect to the wifi
     boolean connected=false;
     for(int i=0;i<5;i++)
     {
       if(connectWiFi())
       {
         connected = true;
         break;
       }
     }
     if (!connected){while(1);}
     delay(5000);
     //print the ip addr
     /*
   SSerial.println("AT+CIFSR");
     Serial.println("ip address:");
     while (SSerial.available())
     Serial.write(SSerial.read());
   
   */
     //set the single connection mode
     SSerial.println("AT+CIPMUX=0");
   }
   void loop()
   {
     String cmd = "AT+CIPSTART=\"TCP\",\"";
     cmd += DST_IP;
     cmd += "\",80";
     SSerial.println(cmd);
     //dbgSerial.println(cmd);
     Serial.println(cmd);
     if(SSerial.find("Error")) return;
     cmd = "GET / HTTP/1.0\r\n\r\n";
     SSerial.print("AT+CIPSEND=");
     SSerial.println(cmd.length());
     if(SSerial.find(">"))
     {
       //dbgSerial.print(">");
       Serial.print(">");
       }else
       {
         SSerial.println("AT+CIPCLOSE");
         //dbgSerial.println("connect timeout");
         Serial.println("connect timeout");
         delay(1000);
         return;
       }
       SSerial.print(cmd);
       delay(2000);
       //Serial.find("+IPD");
       while (SSerial.available())
       {
         char c = SSerial.read();
         //dbgSerial.write(c);
         Serial.write(c);
         //if(c=='\r') dbgSerial.print('\n');
         if(c=='\r') Serial.print('\n');
       }
       //dbgSerial.println("====");
       Serial.println("====");
       delay(1000);
     }
     boolean connectWiFi()
     {
       SSerial.println("AT+CWMODE=1");
       String cmd="AT+CWJAP=\"";
       cmd+=SSID;
       cmd+="\",\"";
       cmd+=PASS;
       cmd+="\"";
       //dbgSerial.println(cmd);
       SSerial.println(cmd);
       Serial.println(cmd);
       delay(2000);
       if(SSerial.find("OK"))
       {
         //dbgSerial.println("OK, Connected to WiFi.");
         Serial.println("OK, Connected to WiFi.");
         return true;
         }else
         {
           //dbgSerial.println("Can not connect to the WiFi.");
           Serial.println("Can not connect to the WiFi.");
           return false;
         }
       }
