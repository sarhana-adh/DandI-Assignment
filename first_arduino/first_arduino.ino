#include "M5Atom.h"

bool Flag = false;// changed IMU6886Flag to flag
void setup()
{
  M5.begin(true, false, true);
  if (!M5.IMU.Init()) IMU6886Flag = true;
}

void loop()
{
  float ax=0.0;ay=0.0,az=0.0;
  if(Flag==true)
  {
    M4.IMU.getAcceIData(&ax,&ay,&az);
  }
uint8_t FSM = 0;
bool onState = true;
float triggered = 0;



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
        M5.dis.drawpix(i, onState ? 0xffffff: 0x000000);
      }
      break;

    case 3: //Automatic Rear Mode Rear (RED): LEDs are solid during a braking event. Return to strobe when riding.
       for (int i = 0; i < 25; i++) 
      {
        M5.dis.drawpix(i, ax > 0.01 || ay > 0.01 ? 0x00f000 : onState ? 0x00f000: 0x000000);
      }
      break;

    case 4: /
      //Automatic Front Mode Rear (White): LEDs are solid during a braking event. Return to strobe when riding.
    break;
    }
    
     if ((millis() - triggered) >= 500) {
    triggered = millis();
    onState = !onState;
     }
}
      
