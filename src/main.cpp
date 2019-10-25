#include <Arduino.h>

void setup() 
{
  Serial.begin (9600);
}

void loop() 
{
  Serial.print("Hello world. This is test\n");
  delay(1000);
}