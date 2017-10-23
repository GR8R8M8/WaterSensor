#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//Define LED Pins
int ledGreenPin = D0;
int ledRedPin = D1;

//Define Water Threshold
int waterThreshold = 300; 

//WiFi Setup
char ssid[] = "ssid";    // Replace ssid with your network name
char pass[] = "password";   // Replace password with your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;

//Thingspeak Setup
unsigned long myChannelNumber = 12345; // Replace with your channel number
const char * myWriteAPIKey = "apikey"; // Replace with your API key

//Startup Code
void setup() {
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
}

void loop() {
  
  if (analogRead(A0)> waterThreshold)
   {
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledRedPin, HIGH);
   }
  else 
   {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, HIGH);
   }
 
  float w = analogRead(A0);

  ThingSpeak.setField(1,w);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  delay(20000);
}
