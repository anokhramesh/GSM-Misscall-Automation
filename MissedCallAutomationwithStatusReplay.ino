#include <SoftwareSerial.h>//Install softwareserial library
#include "Adafruit_FONA.h"// Install Adafruit FONA library 
 
#define FONA_RX            8// Connect RXD pin of Sim800 to D8 pin of arduino
#define FONA_TX            7// Connect TXD pin of Sim800 to D7 pin of arduino
#define FONA_RST           4
 
#define FONA_RI_INTERRUPT  0
int x=1;
int relay =5;// Connect Relay to D5 pin of Arduino
char sendto[21] = "+971557407961"; // Enter your mobile Number here which you are using to make call.
char message[141] = "GSM Switch is ONLINE."; // SMS message when Sim 800 connected to network
char switchon[141]= "SWITCH STATUS - ON"  ;//SMS message when Device is Turned ON
char switchoff[141]= "SWITCH STATUS - OFF";//SMS message when Device is Turned OFF
String ramesh;
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {
  
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  Serial.begin(115200);
  Serial.println(F("FONA incoming call example"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(3000);
  fonaSS.begin(4800); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
  
  if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
  }
  else {
    Serial.println(F("Caller id notification disabled"));
  }
 
   fona.sendSMS(sendto, message);
   
   delay(1000);
}
 
void loop(){
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    digitalWrite(relay,HIGH);
    x=1;
     }
     else
     fona.callerIdNotification(true, FONA_RI_INTERRUPT);
  char phone[32] ={0};
   if (x==1)
 {
  if(fona.incomingCallNumber(phone)){
   Serial.println(F("RING!"));
    Serial.print(F("Phone Number: "));
    ramesh=phone;
    if(ramesh==sendto)
    {
    Serial.println(ramesh);
    digitalWrite(relay,LOW);
    Serial.print("ON");
   fona.sendSMS(sendto, switchon);
   delay(35000);
    if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
    x=2;
    } // reenable call id
  }
else if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) 
    Serial.println(F("Caller id notification enabled."));

  
  }  // incoming call check
 }// X==1 loop

 if (x==2)
 {
  if(fona.incomingCallNumber(phone)){
    
    Serial.println(F("RING!"));
    Serial.print(F("Phone Number: "));
 ramesh=phone;
    if(ramesh==sendto)
    {
    Serial.println(ramesh);
    digitalWrite(relay,HIGH);
    Serial.print("OFF");
    fona.sendSMS(sendto, switchoff);
    delay(35000);
    if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
    x=1;
  } // reenable call id
    }
  else if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) 
    Serial.println(F("Caller id notification enabled."));
  } // incoming call check
 }// X==2 loop

 
}//Loop
