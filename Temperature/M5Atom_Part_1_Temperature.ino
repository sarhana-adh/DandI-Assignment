#include <M5Atom.h>
#include <string>


float temp, average;
int result;
bool IMU6886Flag = false;
float TRecord[720];
float ShortTRecord[5] = {0, 0, 0, 0, 0};
int i = 1;
int ctr = 0;
int count = 0;
int Shortcount = 0;
float aX, aY, aZ;
float accX, accY, accZ;
float gX, gY, gZ;
String T;
char unit = 'C';
bool end0 = false, end1 = false, end2 = false;
extern uint8_t image_zero[77], image_one[77], image_two[77], image_three[77], image_four[77], image_five[77], image_six[77], image_seven[77], image_eight[77], image_nine[77], image_C[77], image_F[77], image_point[77];
uint8_t * modes[13] = { (uint8_t *)image_zero, (uint8_t *)image_one, (uint8_t *)image_two, (uint8_t *)image_three, (uint8_t *)image_four, (uint8_t *)image_five, (uint8_t *)image_six, (uint8_t *)image_seven, (uint8_t *)image_eight, (uint8_t *)image_nine, (uint8_t *)image_C, (uint8_t *)image_F, (uint8_t *)image_point};
int rectime = millis();
int hour24 = millis();

void display(char character)
{
  if (character == '0') M5.dis.displaybuff(modes[0]);
  if (character == '1') M5.dis.displaybuff(modes[1]);
  if (character == '2') M5.dis.displaybuff(modes[2]);
  if (character == '3') M5.dis.displaybuff(modes[3]);
  if (character == '4') M5.dis.displaybuff(modes[4]);
  if (character == '5') M5.dis.displaybuff(modes[5]);
  if (character == '6') M5.dis.displaybuff(modes[6]);
  if (character == '7') M5.dis.displaybuff(modes[7]);
  if (character == '8') M5.dis.displaybuff(modes[8]);
  if (character == '9') M5.dis.displaybuff(modes[9]);
  if (character == 'C') M5.dis.displaybuff(modes[10]);
  if (character == 'F') M5.dis.displaybuff(modes[11]);
  if (character == '.') M5.dis.displaybuff(modes[12]);
}

int round(int n)
{
  int a = (n / 10) * 10;

  int b = a + 10;

  return (n - a > b - n) ? b : a;
}

void recordtemp()
{
  if (millis() - rectime >= 120000)
  {
    M5.IMU.getTempData(&temp);
    TRecord[count] = temp;
    if (Shortcount == 5)
    {
      Shortcount = 4;
      for (int u = 0; u < 4; u++)
      {
        ShortTRecord[u] = ShortTRecord[u + 1];
      }
    }
    ShortTRecord[Shortcount] = temp;
    Serial.printf("%f ", ShortTRecord[Shortcount]);
    count++;
    Shortcount++;
    if (count == 720) count = 0;
    rectime = millis();
  }
}

void setup() {
  M5.begin(true, false, true);
  if (!M5.IMU.Init()) IMU6886Flag = true;
}
void loop() {
  M5.IMU.getAccelData(&aX, &aY, &aZ);
  if (aX >= 50) M5.dis.clear();
  M5.update();
  recordtemp();

  if (aZ < 0.1 && abs(aX) < 0.1 && abs(aY) < 0.1)
  {
    if (M5.Btn.wasPressed())
    {

Start:
      M5.update();
      while (true)
      {
        recordtemp();
        M5.IMU.getAccelData(&gX, &gY, &gZ);
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        if (i >= 0) {
          if (accX >= 0.8) {
            end2 = true;
          }

          if (accX < 0 && accX > -1 && (end2 || end0)) {
            end1 = true;
          }

          if (accX <= -0.8) {
            end0 = true;
          }

          if (end1 && end2) {
            i++;
            end0 = false;
            end1 = false;
            end2 = false;
            delay(500);
          }

          if (end0 && end1) {
            i--;
            end0 = false;
            end1 = false;
            end2 = false;
            delay(500);
          }

          if (gZ > 1.3)
          {
            i = 6;
            break;
          }

          if (i > 5) i = 1;
          if (i < 1) i = 5;
          M5.dis.displaybuff(modes[i]);
        }
        if (M5.Btn.wasPressed()) break;
        M5.update();
      }

      switch (i)
      {
        case 1:
          M5.IMU.getTempData(&temp);
          Serial.printf("%.2f ", temp);
          if (unit == 'C')
          {
            T = (String)temp + "C";
          }
          else
          {
            temp = 1.8 * (temp) + 32;
            T = (String)temp + "F";
            Serial.printf("%f", temp);
          }
          for (int y = 0; y < T.length(); y++)
          {
            M5.dis.clear();
            delay(400);
            display(T[y]);
            delay(700);
            M5.dis.clear();
            delay(400);
          }
          goto Start;
          break;
        case 2:
          ctr = 0;
          for (int a = 0; a < 720; a++)
          {
            if ((int)TRecord[a] != 0)
            {
              ctr++;
            }
          }
          average = 0;
          for (int a = 0; a < 720; a++)
          {
            average = average + TRecord[a];

          }

          average = average / ctr;
          Serial.printf("%f ", average);


          if (unit == 'C')
          {
            T = (String)average + "C";
            Serial.printf("%f", average);
          }
          else
          {
            average = 1.8 * (average) + 32;
            T = (String)average + "F";
            Serial.printf("%f", average);
          }
          for (int y = 0; y < T.length(); y++)
          {
            M5.dis.clear();
            delay(400);
            display(T[y]);
            delay(700);
            M5.dis.clear();
            delay(400);
          }
          goto Start;
          break;
        case 3:
          M5.dis.drawpix(0, 0xffffff);
          M5.dis.drawpix(1, 0x0000ff);
          M5.dis.drawpix(2, 0xff5500);
          M5.dis.drawpix(3, 0xffff00);
          M5.dis.drawpix(4, 0x00f000);
          M5.IMU.getTempData(&temp);
          for (int x = 5; x < 25; x++)
          {
            if (temp < 0) M5.dis.drawpix(x, 0xffffff);
            if (temp > 0 && temp < 10) M5.dis.drawpix(x, 0x0000ff);
            if (temp > 10 && temp < 20) M5.dis.drawpix(x, 0xffff00);
            if (temp > 20 && temp < 30) M5.dis.drawpix(x, 0xff5500);
            if (temp > 30) M5.dis.drawpix(x, 0x00f000);
          }
          break;
        case 4:
          M5.dis.clear();
          for (int a = 20; a < 25; a++)
          {
            result = round((int)ShortTRecord[a - 20]) / 10;
            Serial.printf("%i", result);
            for (int x = 20 + (a - 20); x > (20 + (a - 20)) - (result * 5); x = x - 5)
            {
              M5.dis.drawpix(x, 0xff5500);
            }
          }
          break;
        case 5:
          if (unit == 'C') unit = 'F';
          else unit = 'C';
          goto Start;
          break;
        case 6:
          M5.dis.clear();
          break;
      }

    }
  }
}
