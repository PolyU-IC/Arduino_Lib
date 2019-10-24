#include "Arduino.h"
#include "LineSensor.h"

//#define DEBUG

// Line sensor
int LTS1 = A8;
int LTS2 = A9;
int LTS3 = A10;
int LTS4 = A11;
int LTS5 = A12;
int LTS6 = A13;
int LTS7 = A14;
int LTS_NC = A15;

byte readSensor();

LineSensor::LineSensor()
{
  pinMode(LTS1, INPUT);
  pinMode(LTS2, INPUT);
  pinMode(LTS3, INPUT);
  pinMode(LTS4, INPUT);
  pinMode(LTS5, INPUT);
  pinMode(LTS6, INPUT);
  pinMode(LTS7, INPUT);
  pinMode(LTS_NC, INPUT);
}

int LineSensor::VER()
{
  return _VERSION_;
}

Landmark LineSensor::findLM()
{
  Landmark lm = LM_NotFound;
  
  // Read Line Sensor pattern
  byte LT = readSensor();
  
  int count = 0;
  int maxCount = 0;
  byte pos = 0x1;
  bool prev = LT & pos;
  
  // count number of continuous Dot
  for(int i=1;i<8;i++)
  {
    bool curr = LT & pos;
    if( (count == 0 && curr) || (curr && prev) )
    {
      count++;
    }
    else
    {
      count = 0;
    }
    
    if(count > maxCount)
      maxCount = count;
    prev = curr;
    pos = pos << 1;
  }

#ifdef DEBUG
  Serial.print("Max. count: ");Serial.println(maxCount);
#endif

  // find the Dot pattern
  bool rightLED = (LT & 0x1) == 0x1;  // right LED
  bool leftLED  = (LT & 0x40)== 0x40; // left LED
  bool mid3LED  = (LT & 0x1C)== 0x1C; // mid 3 LED
  bool midLED   = (LT & 0x8) == 0x8;  // mid LED

  // check the landmark
  String actionS = "No action";
  if( maxCount >=3 )
  {
    if( rightLED && !leftLED )
    {
      // Turn right
      actionS = "Turn right";
      lm = LM_RightJoint;
    }
    else if( !rightLED && leftLED )
    {
      // Turn left
      actionS = "Turn left";
      lm = LM_LeftJoint;
    }
    else if( LT == 0x7F )
    {
      // T-joint
      actionS = "T joint";
      lm = LM_TJoint;
    }
    else if( (mid3LED || LT == 0x38 || LT == 0x0E) && !leftLED && !rightLED )
    {
      // Cross mark
      actionS = "Cross mark";
      lm = LM_CrossMark;
    }
  }
  else
  {
    if( midLED && !(LT & 0x14))
    {
      // Forward
      actionS = "Forward";
      lm = LM_Line;
    }
    else if( LT & 0x6)  // ( LT & 0x4 || LT & 0x2)
    {
      // Forward left shifted
      actionS = "Forward left shifted";
      lm = LM_Line_LeftShifted;
    }
    else if( LT & 0x30) // ( LT & 0x10 || LT & 0x20)
    {
      // Forward right shifted
      actionS = "Forward right shifted";
      lm = LM_Line_RightShifted;
    }
    else if(LT == 0)
    {
      actionS = "LM Not Found";
      lm = LM_NotFound;
    }
  }
#ifdef DEBUG
  Serial.println(actionS);
#endif
  return lm;
}

// Read line sensor as digital.
byte readSensor()
{
  byte LT = digitalRead(LTS7)+
            digitalRead(LTS6)*2+
            digitalRead(LTS5)*4+
            digitalRead(LTS4)*8+
            digitalRead(LTS3)*16+
            digitalRead(LTS2)*32+
            digitalRead(LTS1)*64;
#ifdef DEBUG
  Serial.println("LT: "+String((byte)~LT, BIN));
#endif
  return LT;
}
