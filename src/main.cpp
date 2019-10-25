#include <Arduino.h>

void setup() 
{
  Serial.begin (9600);
}

void init()
{
  int a = 10,
      b = 5;
}

void loop() 
{
  Serial.print("Hello world. This is test:\n\t");
  Serial.print("a = 10, b = 5");
  delay(1000);
}