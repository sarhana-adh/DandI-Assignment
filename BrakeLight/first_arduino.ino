#include "M5Atom.h"

bool IMU6886Flag = false;// changed IMU6886Flag to flag
// IMU6886Flag is from example, there were some issue when variables changed, don't know why it worked
const int n_average = 18;

void setup()
{
  M5.begin(true, false, true);
  if (!M5.IMU.Init()) IMU6886Flag = true;
}

uint8_t FSM = 0;
bool onState = true;
float triggered = 0;
float prevMovement = 0;
float deaccThreshold = 0.06;

float ax = 0.0, ay = 0.0, az = 0.0,nax = 0.0, nay = 0.0, naz = 0.0, avgax = 0.0, avgay = 0.0, avgaz = 0.0; 
bool Deaccelerating = false;


void loop()
{
  if (IMU6886Flag == true) {
    M5.IMU.getAccelData(&ax, &ay, &az);
  // to reset after 4 press

  if (M5.Btn.wasPressed())
  {
    FSM++;
    if (FSM >= 4)
    {
      FSM = 0;
    }
  }


  switch (FSM)
  {
    case 0:// OFF: All LEDs off
      for (int i = 0; i < 25; i++) {
        M5.dis.drawpix(i, 0x000000);
      }
      break;

    case 1: // Manual Rear strobe (RED): LEDs strobe at a predetermined interval
      for (int i = 0; i < 25; i++) {
        M5.dis.drawpix(i, onState ? 0x00f000 : 0x000000);
      }

      break;

    case 2: //Manual Front strobe (WHITE): LEDs strobe at a predetermined interval
      for (int i = 0; i < 25; i++)
      {
        M5.dis.drawpix(i, onState ? 0xffffff : 0x000000);
      }
      break;

    case 3: //Automatic Rear Mode Rear (RED): LEDs are solid during a braking event. Return to strobe when riding.
     M5.IMU.getAccelData(&ax, &ay, &az);
      checkDeaccelerating(ax, ay);// calls the function 
      for (int i = 0; i < 25; i++)
      {
        M5.dis.drawpix(i, ((Deaccelerating) ? (0x00f000) : (onState ? 0x00f000 : 0x000000))); 
        // strobes when not accelerating        
      }

      break;
    case 4:
      //Automatic Front Mode Rear (White): LEDs are solid during a braking event. Return to strobe when riding.
     M5.IMU.getAccelData(&ax, &ay, &az);
      checkDeaccelerating(ax, ay);// calls the function 
      for (int i = 0; i < 25; i++)
      {
        M5.dis.drawpix(i, ((Deaccelerating) ? (0xffffff) : (onState ? 0xffffff : 0x000000))); 
        // strobes when not accelerating        
      }
      break;

    default:
      break;
  }

  if ((millis() - triggered) >= 500) {
    triggered = millis();
    onState = !onState;

  }

      delay(50);
  M5.update();
}}


void checkDeaccelerating(float oldax, float olday)
{
  M5.IMU.getAccelData(&ax, &ay, &az);
  
//calculating the avergae of acceration data 
// simple "running average" method

  avgax = ((avgax * (n_average - 1)) + ax) / n_average;
  avgay = ((avgay * (n_average - 1)) + ay) / n_average;
  avgaz = ((avgaz * (n_average - 1)) + az) / n_average;


  if ((avgax - ax) > deaccThreshold && (avgay - ay)>deaccThreshold)
  {
    Deaccelerating = true;
  }
  else
  {
    Deaccelerating = false;
  }
  oldax = ax; olday = ay;
}
