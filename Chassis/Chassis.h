#ifndef Chassis_h
#define Chassis_h

#include "Arduino.h"

#define _VERSION_ 1
class Chassis
{
  public:
    Chassis();
    Chassis(int m1_pwm, int m1_dir, int m1_en,int m2_pwm, int m2_dir, int m2_en,int m3_pwm, int m3_dir, int m3_en);
    /*
     * Move the chassis in a given direction. This function will reset all encoder
     * values to ZERO.
     * theta: int. The direction of the chassis to move, count in anticlockwise.
     *        0
     *        |
     *        |
     * 90 ----+---- 270
     *        |
     *        |
     *       180
     * speed: int. The chassis's speed.
     */
    void move(int theta,int speed);
    /*
     * Rotate the chassis by a given degree.
     * theta: int. The angle to rotate
     *        0
     *        |
     *        |
     * 90 ----+---- 270
     *        |
     *        |
     *       180
     * speed: int. The speed in roration
     */
    int VER();
    /*
     * return: version number
     */
    void rotate(int theta,int speed);
    /*
     * Set this value of the encoder count for rotating 180 degree.
     * value: float. The encoder count for rotating 180 degree.
     */
    void setRotate180(float value);
    /*
     * Set the encoder value
     * id:    int. Motor ID
     * value: long. Value to be set
     */
    void setEncoder(int id, long value);
    /*
     * Read the encoder value 
     * id:      int. Motor ID
     * return:  long. The encoder value
     */
    long readEncoder(int id);

     /*
      //move the chassis paralelly left
      void left(int theta,int speed);
      //move the chassis paralelly right
      void right(int theta,int speed);*/

    void buzzer(int delayTime);
    
};

#endif
