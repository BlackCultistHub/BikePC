#include <Arduino.h>

void setup() 
{
  Serial.begin (9600);
}

int a = 10,
      b = 5;

void loop() 
{
  Serial.print("Hello world. This is test:\n\t");
  Serial.print("a = 10, b = 5\n\t");
  int c = a + b;
  Serial.print("Summ is = ");
  Serial.print(c);
  Serial.print("\n");
  delay(1000);
}