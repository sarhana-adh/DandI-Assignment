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
#include "1.c";
#include "2.c";
#include "3.c";
#include "4.c";
#include "5.c";
#include "6.c";


int color;
double pitch, roll;
double r_rand = 180 / PI;
int Diceroller;
const char* ssid = "Group-10";
const char* password = "12345678";


WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", html);
}

#define RXD 22
#define RELAY 23

ATOMSOCKET ATOM;

HardwareSerial AtomSerial(2);

bool RelayFlag = false;

bool diceState = true;

String DataCreate() {
  String Data;
  switch(color){
    case 0:Data = String("red");
    break;
    case 1:Data = String("orange");
     break;
    case 2:Data = String("yellow");
     break;
    case 3:Data = String("green");
     break;
    case 4:Data = String("blue");
     break;
    case 5:Data = String("purple"); 
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

  server.on("/changeState", [](){
      String state = server.arg("state");
      Serial.println(state);
      
      if(state == "DICE"){
         diceState = true;
      }else{
        diceState = false;
      }

      server.send(200, "text/plain", "SUCCESS");
    });

  server.on("/data", []() {
    server.send(200, "text/plain", DataCreate());
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  ATOM.SerialReadLoop();
  M5.update();
  server.handleClient();
  delay(50);
  M5.IMU.getAttitude(&pitch, &roll);

  double arc = atan2(pitch, roll) * r_rand + 180;
   int arcint = int(arc);
   Serial.printf("%i \n", arcint);
  // the boolean should be here
  if (!diceState) {
    FillRGB(arc);
  }
  else {
    Diceroller(arc);
  }

  M5.update();

}
  
void Diceroller(double h) {

  color = int (h / 60);

  switch (color)
  {
    case 0:
      M5.dis.displaybuff((uint8_t *)image_1, 0, 0);
      break;

    case 1:
      M5.dis.displaybuff((uint8_t *)image_2, 0, 0);
      break;

    case 2:
      M5.dis.displaybuff((uint8_t *)image_3, 0, 0);
      break;

    case 3:
      M5.dis.displaybuff((uint8_t *)image_4, 0, 0);
      break;

    case 4:
      M5.dis.displaybuff((uint8_t *)image_5, 0, 0);
      break;

    case 5:
      M5.dis.displaybuff((uint8_t *)image_6, 0, 0);
      break;
  }


};


// defining the function for
void FillRGB(double h) {
  CRGB ReRGB(0, 0, 0);
  color = int(h / 60); // h value  0 to 360  color 0 to 5
  switch (color)
  {
    case 0: // red 
      ReRGB.r = 0;
      ReRGB.g = 255;
      ReRGB.b = 0;  
      Serial.printf("1 \n"); 
      break;

    case 1: // orange 
      ReRGB.r = 128;
      ReRGB.g = 255;
      ReRGB.b = 0;
      Serial.printf("2 \n");
      break;
      

    case 2: // yellow
      ReRGB.red = 255;
      ReRGB.green = 255; // green and red are switched
      ReRGB.blue = 0 ;
      Serial.printf("3 \n");
      break;
      
    case 3: // green
      ReRGB.r = 255;
      ReRGB.g = 0 ;
      ReRGB.b = 0;
      Serial.printf("4 \n");
      break;

    case 4: // blue 
      ReRGB.r = 0 ;
      ReRGB.g = 0;
      ReRGB.b = 255;
      Serial.printf("5 \n");
      break;

    case 5: // purple 
      ReRGB.r = 0;
      ReRGB.g = 127;
      ReRGB.b = 255 ;
      Serial.printf("0 \n");
      break;

    default:
      ReRGB.r = 0;
      ReRGB.g = 127;
      ReRGB.b = 255 ;
      Serial.printf("6 \n");
      Serial.printf("%.2f \n", color);

  }
  M5.dis.fillpix(ReRGB);
}
