#include <Encoder.h>
#include "Arduino.h"
#include "Chassis.h"

// Encoder
Encoder encoderMotor0(3, 23); // 0
Encoder encoderMotor1(2, 22); // 1
Encoder encoderMotor2(21, 24); // 2

int motor0_PWM = 9;
int motor0_DIR = 7;
int motor0_EN  = 12;
int motor0_A   = 3;
int motor0_B   = 23;

int motor1_PWM = 8;
int motor1_DIR = 10;
int motor1_EN  = 13;
int motor1_A   = 2;
int motor1_B   = 22;

int motor2_PWM = 11;
int motor2_DIR = 49;
int motor2_EN  = 48;
int motor2_A   = 21;
int motor2_B   = 24;

int buz_PWM = 6;



float _rotate_180 = 13500;

void motor(int motorID, int speed, bool dir);

int Chassis::VER()
{

   return _VERSION_;

}

Chassis::Chassis()
{
  //Motor 1
  pinMode(motor0_PWM, OUTPUT);
  pinMode(motor0_DIR, OUTPUT);
  pinMode(motor0_EN,  OUTPUT);
  pinMode(motor0_A,   INPUT_PULLUP);
  pinMode(motor0_B,   INPUT_PULLUP);
  //Motor 2
  pinMode(motor1_PWM, OUTPUT);
  pinMode(motor1_DIR, OUTPUT);
  pinMode(motor1_EN,  OUTPUT);
  pinMode(motor1_A,   INPUT_PULLUP);
  pinMode(motor1_B,   INPUT_PULLUP);
  //Motor 3
  pinMode(motor2_PWM, OUTPUT);
  pinMode(motor2_DIR, OUTPUT);
  pinMode(motor2_EN,  OUTPUT);
  pinMode(motor2_A,   INPUT_PULLUP);
  pinMode(motor2_B,   INPUT_PULLUP);

  //Buzzer
  pinMode(buz_PWM, OUTPUT);
}

Chassis::Chassis(int m0_pwm, int m0_dir, int m0_en,int m1_pwm, int m1_dir, int m1_en,int m2_pwm, int m2_dir, int m2_en)
{
  motor0_PWM = m0_pwm;
  motor0_DIR = m0_dir;
  motor0_EN  = m0_en;
  
  motor1_PWM = m1_pwm;
  motor1_DIR = m1_dir;
  motor1_EN  = m1_en;
  
  motor2_PWM = m2_pwm;
  motor2_DIR = m2_dir;
  motor2_EN  = m2_en;

  //Motor 1
  pinMode(motor0_PWM, OUTPUT);
  pinMode(motor0_DIR, OUTPUT);
  pinMode(motor0_EN,  OUTPUT);
  pinMode(motor0_A,   INPUT_PULLUP);
  pinMode(motor0_B,   INPUT_PULLUP);
  //Motor 2
  pinMode(motor1_PWM, OUTPUT);
  pinMode(motor1_DIR, OUTPUT);
  pinMode(motor1_EN,  OUTPUT);
  pinMode(motor1_A,   INPUT_PULLUP);
  pinMode(motor1_B,   INPUT_PULLUP);
  //Motor 3
  pinMode(motor2_PWM, OUTPUT);
  pinMode(motor2_DIR, OUTPUT);
  pinMode(motor2_EN,  OUTPUT);
  pinMode(motor2_A,   INPUT_PULLUP);
  pinMode(motor2_B,   INPUT_PULLUP);
}

void Chassis::move(int theta,int speed)
{
  encoderMotor0.write(0);
  encoderMotor1.write(0);
  encoderMotor2.write(0);
  
  float Fa = speed*cos( (150-theta) * PI/180);
  float Fb = speed*cos( (30-theta) * PI/180);
  float Fc = speed*cos( (270-theta) * PI/180);

  motor(0, abs(Fa), Fa < 0);
  motor(1, abs(Fb), Fb > 0);
  motor(2, abs(Fc), Fc < 0);
}

/*
 * Commented function is the additional function 
 * to move the car parallely left OR parallely right
 */
 
/*void Chassis::left(int theta,int speed){
  encoderMotor0.write(0);
  encoderMotor1.write(0);
  encoderMotor2.write(0);
  
  float Fa = speed*cos( (120-theta) * PI/180);
  float Fb = speed*cos( (120-theta) * PI/180);
  float Fc = speed*cos( (30-theta) * PI/180);

  motor(0, abs(Fa), Fa > 0);
  motor(1, abs(Fb), Fb < 0);
  motor(2, abs(Fc), Fc > 0);
}

void Chassis::right(int theta,int speed){
  encoderMotor0.write(0);
  encoderMotor1.write(0);
  encoderMotor2.write(0);
  
  float Fa = speed*cos( (120-theta) * PI/180);
  float Fb = speed*cos( (120-theta) * PI/180);
  float Fc = speed*cos( (30-theta) * PI/180);

  motor(0, abs(Fa), Fa < 0);
  motor(1, abs(Fb), Fb > 0);
  motor(2, abs(Fc), Fc < 0);
}*/

void Chassis::setRotate180(float value)
{
  _rotate_180 = abs(value);
}

void Chassis::rotate(int theta,int speed)
{
  float COUNT_180 = _rotate_180;
  
  encoderMotor0.write(0);
  encoderMotor1.write(0);
  encoderMotor2.write(0);

  float count = floor(COUNT_180 * (abs(theta) / 180.0) );
  
  motor(0, speed, theta < 0);
  motor(1, speed, theta > 0);
  motor(2, speed, theta < 0);

  int fr = 0;
  int fl = 0;
  int fm = 0;
  
  do
  {
    fr = abs(encoderMotor0.read());
    fl = abs(encoderMotor1.read());
    fm = abs(encoderMotor2.read());
  }while(fr < count && fl < count && fm < count);

  move(0,0);
}

void Chassis::setEncoder(int id, long value)
{
  switch(id)
  {
    case 0:
      encoderMotor0.write(value);
      break;

    case 1:
      encoderMotor1.write(value);
      break;

    case 2:
      encoderMotor2.write(value);
      break;
  }
}

long Chassis::readEncoder(int id)
{
  switch(id)
  {
    case 0:
      return encoderMotor0.read();

    case 1:
      return encoderMotor1.read();

    case 2:
      return encoderMotor2.read();
  }
}

void Chassis::buzzer(int delayTime){
  digitalWrite(buz_PWM,HIGH);
  delay(delayTime);
  digitalWrite(buz_PWM,LOW);
}

/* 
 * Control the motor speed and direction 
 * motirID: int: ID of the motor
 * speed:   int: Speed of the motor
 * dir:     bool: Direction of the motor
 */
void motor(int motorID, int speed, bool dir) 
{
  int pwm_pin, en_pin, dir_pin;
  
  if (motorID == 0)
  {
    pwm_pin = motor0_PWM;
    dir_pin = motor0_DIR;
    en_pin = motor0_EN;
  }
  else if (motorID == 1) 
  {
    pwm_pin = motor1_PWM;
    dir_pin = motor1_DIR;
    en_pin = motor1_EN;
  }
  else if (motorID == 2)
  {
    pwm_pin = motor2_PWM;
    dir_pin = motor2_DIR;
    en_pin = motor2_EN;
  }

  if (dir == HIGH)
    speed = 255 - speed;

  analogWrite (pwm_pin, speed);
  digitalWrite(dir_pin, dir);
  digitalWrite(en_pin, 1);
}
