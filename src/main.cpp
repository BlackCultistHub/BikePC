#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() 
{
  Serial.begin (9600);
  Serial.println();
  WiFi.begin("InterZet610 (5GHz)", "0987654321000");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  Serial.print("Hello world. This is test:\n\t");
  delay(1000);
}