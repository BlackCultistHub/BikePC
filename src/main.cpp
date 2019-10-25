#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() 
{
  Serial.begin (9600);
  Serial.println();
  WiFi.begin("BlackCultistNetwork", "0987654321000");
  Serial.print("Connecting...");
  delay(3000);
  Serial.println();
  Serial.print("Connected, IP address: ");
  delay(1000);
  Serial.println(WiFi.localIP());
}

void loop() 
{
  Serial.print("Hello world. This is test:\n\t");
  delay(1000);
}