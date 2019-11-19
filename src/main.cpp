//#include <Arduino.h>
//#include <Adafruit_GFX.h>      // include Adafruit graphics library
//#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library
#include <bikeScreen.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
 
//***********[ ST7735 TFT module connections ]***********
#define TFT_RST   D4     // TFT RST pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS    D3     // TFT CS  pin is connected to NodeMCU pin D4 (GPIO0)
#define TFT_DC    D2     // TFT DC  pin is connected to NodeMCU pin D4 (GPIO4)
// initialize ST7735 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)

//***********[ Defines ]***********
#define MAX_DATA_ARGUMENT_AMOUNT 32

//***********[ Predefined Values ]***********
const char* ssid = "InterZet610_2.4";
const char* password = "0987654321000";
String page = "";
String args[MAX_DATA_ARGUMENT_AMOUNT];
String argVals[MAX_DATA_ARGUMENT_AMOUNT];
String pulseRaw;
int argLen = 0;
bool update = false;
String temp;
const uint32_t utcOffsetInSeconds = 10800;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//***********[ Object Inits ]***********
BikeScreen tft(TFT_CS, TFT_DC, TFT_RST); //tft screen object
ESP8266WebServer server(80);

//***********[ Function Prototypes ]***********
void refresh(Adafruit_ST7735*);
void handler404();
void handlerIndex();
void handlerData();

//***********[ Inits and One-Time Run ]***********
void setup(void) 
{
  Serial.begin(9600);
  delay(10);
  Serial.println("");
  // Define NTP Client to get time
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds);
  // initialize a ST7735S chip, black tab
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  delay(500);
  tft.printf("Connecting to\n%s\n", ssid);
  WiFi.persistent(false);
  WiFi.disconnect(true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    tft.print(".");
  }
  tft.println("\nConnected.");
  server.begin();
  tft.print("Web server started,\nlocal ip is:\n");
  delay(1000);
  tft.println(WiFi.localIP().toString().c_str());
  delay(5000);
  //SCREEN INIT
  uint16_t xs[] = {0, 0, 0, 0}, 
          widths[] = {128, 128, 128, 128},
          ys[] = {0, 24, 73, 117},
          heights[] = {24, 50, 45, 40};
  tft.fillScreen(ST7735_BLACK);
  tft.drawFrame(4, xs, ys, widths, heights);
  timeClient.begin();
  timeClient.update();
  tft.drawTime(timeClient.getHours(), timeClient.getMinutes());
  tft.drawDate(daysOfTheWeek[timeClient.getDay()]);
  tft.drawBattery(90);
  tft.drawSpeed(15);
  tft.drawCadence(120);
  tft.drawPulse(85);
  //HANDLERS
  server.onNotFound(handler404);
  server.on("/", handlerIndex);
  server.on("/data", handlerData);
}

//***********[ Inf Loop ]***********
void loop(void) 
{
  server.handleClient();
  if (update)
  {
    //INTERRUPT FOR TIME UPDATE

    if (pulseRaw)
    {
      char temp[2];
      strcpy(temp, pulseRaw.c_str());
      tft.drawPulse(atoi(temp));
    }
    //String message;
    //tft.fillScreen(ST7735_BLACK);
    //tft.setCursor(0,0);
    //tft.printf("Client IP:\n%s\n", server.client().remoteIP().toString().c_str());
    //tft.println("List of args:");
    
    //for (uint8_t i = 0; i < argLen; i++)
    //  message += args[i]+" = "+argVals[i]+"\n";
    /*message += "List of -||- +1:\n";
    for (uint8_t i = 0; i < argLen; i++)
    {
      int len = argVals[i].length();
      char temp[len+1];
      strcpy(temp, argVals[i].c_str());
      message += args[i]+" = "+(atoi(temp)+1)+"\n";
    }*/
    //tft.print(message);
    update = !update;
  }
  delay(1);
}

//***********[ Function Definitions ]***********
void refresh(Adafruit_ST7735* screen)
{
  screen->print("[REFRESH IN 7s]");
  delay(7000);
  screen->fillScreen(ST7735_BLACK);
  screen->setCursor(0,0);
}

//***********[ Handlers ]***********
void handler404()
{
  String msg = String("<h1>404 Not Found.</h1><br>")+
                      "URI: "+server.uri()+"<br>"+
                      "Method: "+((server.method() == HTTP_GET)?"GET":"POST")+"<br>"
                      "Arguments: "+server.args()+"<br>";
  for (uint8_t i = 0; i < server.args(); i++)
    msg += " "+server.argName(i)+": "+server.arg(i)+"<br>";
  server.send(404, "text/html", msg);
}

void handlerIndex()
{
  String msg = String("<h1>Hello! ESP8266.</h1><br>");
  server.send(200, "text/html", msg);
}

void handlerData()
{
  if (server.hasArg("pulse"))
    pulseRaw = server.arg("pulse");
  else
    pulseRaw = "0";
  for (uint8_t i = 0; i < MAX_DATA_ARGUMENT_AMOUNT; i++)
  {
    args[i] = "0";
    argVals[i] = "0";
  }
  for(uint8_t i = 0; i < server.args(); i++)
  {
    args[i] = server.argName(i);
    argVals[i] = server.arg(i);
  }
  argLen = server.args();
  String msg = String("<h1>Hello! ESP8266.<h1><br>")+
                      "Data recieve completed.<br>"+
                      "Recieved "+server.args()+" arguments.<br>"+
                      "Argument list:<br>";
  for(uint8_t i = 0; i < server.args(); i++)
    msg += (i+1)+". "+server.argName(i)+": "+server.arg(i)+"<br>";
  update = true;
  server.send(200, "text/html", msg);
}