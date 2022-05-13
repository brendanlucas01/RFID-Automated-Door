/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<string.h>
#include <Servo.h>

Servo myservo;
char input[12];        
int count = 0;        
int rfid_enable = 1;
int assistant_enable = 1;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "-Nfyf5TuWTF49rSh_KE8DxrbFSm31l6r";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ASUS_X00TD";
char pass[] = "ASUS_X00TD";


void open_door();
void auth_rfid();
void setup()
{
  // Debug console
  Serial.begin(9600);   // START SERIAL AT BAUD RATE OF 9600 BITS/SEC   
  myservo.attach(4);
  Blynk.begin(auth, ssid, pass);
  pinMode(16,OUTPUT);
  myservo.write(0);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

BLYNK_WRITE(V2)
{
  int command_val = param.asInt();
  if(command_val==0)
  {
    Serial.println("Door closed via App");
    myservo.write(0);
  }
  else if(command_val==1)
  {
    Serial.println("Door opened via App");
    myservo.write(180);
  }
  else if(command_val==2)
  {
    if(assistant_enable)
    {
      Serial.println("Access Granted via Assistant");
      digitalWrite(16,HIGH);
      delay(15);
      digitalWrite(16,LOW);
      open_door();
    }
    else{
      Serial.println("Assistant Access Denied");
    }
  } 
}

BLYNK_WRITE(V4)
{
 rfid_enable = param.asInt();
 if(rfid_enable)
 {
  Serial.println("RFID enabled via app");
 }
 else{
  Serial.println("RFID disabled via app");
 }
}

BLYNK_WRITE(V5)
{
 assistant_enable = param.asInt();
 if(assistant_enable)
 {
  Serial.println("Assistant enabled via app");
 }
 else{
  Serial.println("Assistant disabled via app");
 }
}

BLYNK_WRITE(V3)
{
  int command_vall = param.asInt();
  myservo.write(command_vall);
  Serial.println(command_vall);
}

void loop()
{
  Blynk.run();
  auth_rfid();
}

void open_door()
{
   Serial.println();
   myservo.write(180);
   delay(3000);
   myservo.write(0);
}

void auth_rfid()
{
//  Serial.print("Inside auth_rfid function\n");
  if(rfid_enable==1)
  {
       if(Serial.available())   // CHECK FOR AVAILABILITY OF SERIAL DATA
      {
        count = 0;      // Reset the counter to zero
        /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty 
           or till 12 Bytes (the ID size of our Tag) is read */
        while(Serial.available() && count < 12) 
        {
          input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
          count++;          // increment counter
          delay(5);
        }
         // PRINTING RFID TAG
        Serial.print(input);           
        if(strcmp(input,"5A001E1F88D3")==0)
            {
             Serial.println("Access Granted to Soham");
             open_door();
            }
         else if(strcmp(input,"550073E54F8C")==0)
            {
             Serial.println("Access Granted to Ronak");
             open_door();
       }
    } 
  }
}

//https://arduino.esp8266.com/stable/package_esp8266com_index.json
//https://dl.espressif.com/dl/package_esp32_index.json

// 
// ⸮⸮⸮$⸮⸮?ޅ⸮?
