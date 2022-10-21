#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include "IRremote.h"
#define NATHAN_ID "82 A4 37 BB"

int  sensorPin  =  A0;
int  sensorValue =  0;
int receiver = 2;
int buttonApin = 3;
int buttonBpin = 4;
int buttonCpin = 5;
int buttonDpin = 6;
int buzzer = 1;
Servo myservo;
int pos = 0;
;int  val;
int buttonpin=7;
#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
IRrecv irrecv(receiver);    
decode_results results;
void translateIR()
{
  switch(results.value) 
{ 
  case 0xFFA25D: myservo.detach();break;
  case 0xFF6897: myservo.write(10); delay (100); ("0"); break;
  case 0xFF30CF: myservo.write(90); delay (100); ("1"); break;
  case 0xFF18E7: myservo.attach(8);("2"); break;
  case 0xFF629D: digitalWrite(buzzer,HIGH); myservo.detach(); break;
  case 0xFFA857: digitalWrite(buzzer,LOW); break;
("}
delay(500);
}
")
void setup()
{
   pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
  pinMode(buttonDpin, INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
   myservo.attach(8);
   irrecv.enableIRIn();
   SPI.begin(); 
   mfrc522.PCD_Init();
   for (byte i = 0; i < 6; i++) {
   key.keyByte[i] = 0xFF;
}
}

void loop()
 { 
  if(digitalRead(buttonCpin) == LOW)
  {
    myservo.attach(8);
  }
   if (irrecv.decode(&results))
  
 {
 translateIR(); 
 irrecv.resume(); // receive the next value             
 delay(500);   
 } 
{ 
val=digitalRead(buttonpin);//read the value of the digital interface 3 assigned to val 
if(val==LOW)
{
 myservo.detach();
}
}
  {
 if (digitalRead(buttonDpin) == LOW)
 {
 digitalWrite(buzzer,HIGH);
 myservo.detach();
}
  }
{ 
  if (digitalRead(buttonBpin) == LOW)
{
  myservo.write (10);
  delay(100);
}    
 if (digitalRead(buttonApin) == LOW)
 { 
 myservo.write(90); 
 delay(500);
 }
  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  
  delay(200);
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }  
  Serial.println();
}
  byte newUid[] = NEW_UID;
  if ( mfrc522.MIFARE_SetUid(newUid, (byte)4, true) ) {
  }
  
  // Halt PICC and re-select it so DumpToSerial doesn't get confused
  mfrc522.PICC_HaltA();
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  myservo.write (10);
      Serial.println(F("Wrote new UID to card."));
  Serial.println(F("New UID and contents:"));
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  delay(2000);
} 
 

 
