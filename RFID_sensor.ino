#include<string.h>
#include<Servo.h>


char input[12];
int count = 0;
int flag=0;
// SETUP FUNCTION
Servo myservo;
void open_door();

void setup()
{

    Serial.begin(9600); // START SERIAL AT BAUD RATE OF 9600 BITS/SEC
    pinMode(A0,INPUT);
    myservo.attach(5);
    myservo.write(90);
    delay(500);
}

void loop()
{
   flag = analogRead(A0);
  if(Serial.available()) // CHECK FOR AVAILABILITY OF SERIAL DATA
  { 
      count = 0; // Reset the counter to zero
      
      while(Serial.available() && count < 12) {
      
          input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
          
          count++; // increment counter 
          delay(5); 
      }
      // PRINTING RFID TAG
      Serial.println(input);
//      Serial.println();
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
  Serial.println(flag);
  if(flag>600)
   {
      Serial.println("door opened via assistant");
      open_door();
    }
     

}

void open_door()
{
   Serial.println();
   myservo.write(180);
   delay(3000);
   myservo.write(90);
}
