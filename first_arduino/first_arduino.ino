#include "M5Atom.h"

bool IMU6886Flag = false;
void setup()
{
  M5.begin(true, false, true);
  if (!M5.IMU.Init()) IMU6886Flag = true;
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
    case 0:// should be off 
      for (int i = 0; i < 25; i++) {
        M5.dis.drawpix(i, 0x000000);
      }
      break;

    case 1: // 
      for (int i = 0; i < 25; i++) {
        M5.dis.drawpix(i, onState ? 0x00f000 : 0x000000);
      }
      
      break;
      
    case 2:
   
      break;

    case 3:
   
      break;

    case 4:
    break;
    }
    
     if ((millis() - triggered) >= 500) {
    triggered = millis();
    onState = !onState;
     }
   
      
