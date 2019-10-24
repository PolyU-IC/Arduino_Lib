#ifndef LineSensor_h
#define LineSensor_h

#include "Arduino.h"
#define _VERSION_ 1
// Define all the landmarks can find on the map
enum Landmark
{
  LM_NotFound = 0,
  LM_Line,
  LM_Line_RightShifted,
  LM_Line_LeftShifted,
  LM_CrossMark,
  LM_LeftJoint,
  LM_RightJoint,
  LM_TJoint,
};

class LineSensor
{
  public:
    LineSensor();
    int VER();
    /* 
     * Find the landmark 
     * return:  Landmark. landmark found
     */
    Landmark findLM();
};

#endif
