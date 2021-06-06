/*    Description:
    Use ATOM Socket to monitor the socket power, press the middle button of ATOM to switch the socket power on and off.
    Connect to the AP hotspot of the device and access 192.168.4.1 to wirelessly control the socket power and view the power voltage, current and power information. */
#include "M5Atom.h"
#include "AtomSocket.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "index.h"


CRGB led;
int color = 0;
double pitch, roll;
double r_rand = 180 / PI;
int Diceroller;
const char* ssid = "ATOM-SOCKET";
const char* password = "12345678";
CRGB HSVtoRGB(int h, int s, int v);


WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", html);
}

#define RXD 22
#define RELAY 23

ATOMSOCKET ATOM;

HardwareSerial AtomSerial(2);

bool RelayFlag = false;

String DataCreate() {
  String Data; String("green");
  switch(color){
    case 0:Data = String("orange");
    break;
    case 2:Data = String("green");
     break;
    case 3:Data = String("red");
     break;
    case 4:Data = String("yellow");
     break;
    case 5:Data = String("blue");
     break;
    case 6:Data = String("purple"); 
     break;
    default: Data = String("purple");
     break;
    ;} 
  return Data;
}

void setup() {
  M5.begin(true, true, true);
  M5.IMU.Init();
  M5.dis.drawpix(0, 0xe0ffff);
  ATOM.Init(AtomSerial, RELAY, RXD);
  WiFi.softAP(ssid, password);
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP PASSWORD: ");
  Serial.println(password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  //IP address assigned to your ESP
  server.on("/", handleRoot);

  server.on("/on", []() {
    RelayFlag = true;
    server.send(200, "text/plain", DataCreate());
  });

  server.on("/off", []() {
    RelayFlag = false;
    server.send(200, "text/plain", DataCreate());
  });

  server.on("/data", []() {
    server.send(200, "text/plain", DataCreate());
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  ATOM.SerialReadLoop();

// R,G,B from 0-255, H from 0-360, S,V from 0-100

 


  
  M5.update();
  server.handleClient();
  delay(50);
  M5.IMU.getAttitude(&pitch, &roll);
  //  Serial.printf("%.2f \n",pitch);

  double arc = atan2(pitch, roll) * r_rand + 180;
  double val = sqrt(pitch * pitch + roll * roll);
  //   Serial.printf("%.2f,%.2f,%.2f,%.2f\n", pitch, roll, arc, val);

  val = (val * 6) > 100 ? 100 : val * 6;
  led = HSVtoRGB(arc, val, 100); // calling the function 
  M5.dis.fillpix(led);
  M5.update();
  //   Diceroller = (rand() % 6) + 1;
  //  Serial.printf("%.2f \n",Diceroller);
}

// defining the function 
  CRGB HSVtoRGB(int h, int s, int v){
  CRGB ReRGB(0, 0, 0);

  float RGB_min, RGB_max;
  RGB_max = v * 2.55f;
  RGB_min = RGB_max * (100 - s) / 100.0f;

  color = h / 60;
  int difs = h % 60;
  float RGB_Adj = (RGB_max - RGB_min) * difs / 60.0f;

  switch (color)
  {
    /*   case 1:
           ReRGB.r = 255;
           ReRGB.g = 0 ;
            ReRGB.b = 0;
           break;
            Serial.printf("1 \n");*/
    case 2:
      ReRGB.r = 255 ;
      ReRGB.g = 128;
      ReRGB.b = 0;
      Serial.printf("2 \n");
      break;

    case 3:
      ReRGB.red = 0;
      ReRGB.green = 255; // green and red are switched
      ReRGB.blue = 0 ;
      Serial.printf("3 \n");
      break;
    case 4:
      ReRGB.r = 255;
      ReRGB.g = 255 ;
      ReRGB.b = 0;
      Serial.printf("4 \n");
      break;

    case 5:
      ReRGB.r = 0 ;
      ReRGB.g = 0;
      ReRGB.b = 255;
      Serial.printf("5 \n");
      break;

    case 0:
      ReRGB.r = 128;
      ReRGB.g = 255;
      ReRGB.b = 0 ;
      Serial.printf("0 \n");
      break;

    default:
      ReRGB.r = 0;
      ReRGB.g = 127;
      ReRGB.b = 255 ;
      Serial.printf("6 \n");
      Serial.printf("%.2f \n", color);

  }
  return ReRGB;
}
