#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() 
{
  Serial.begin (9600);
  Serial.println();
  //WIFI INIT
  /*WiFi.begin("BlackCultistNetwork", "0987654321000");
  Serial.print("Connecting...");
  delay(3000);
  Serial.println();
  Serial.print("Connected, IP address: ");
  delay(1000);
  Serial.println(WiFi.localIP());*/
//Use predefined PINS consts
  /*Wire.begin(D2, D1);
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.home();
  lcd.clear(); */
}

void loop() 
{
  Serial.print("Hello world. This is test:\n\t");
  /*lcd.setCursor(0, 0); // Cursor0 , Linea0
  lcd.print("Line1");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 1); // Cursor0 , Linea1
  lcd.print("Line2");
  delay(1000);
  lcd.clear(); */
}