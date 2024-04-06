#include "movement.h"
#include "Arduino.h"

#define HC_SR04_I2C_ADDR 0x57
#define LCD_I2C_ADDR 0x27
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define PWM_MAX 255
#define PWM_MIN 0

void setSpeed(int target_speed){
  if (target_speed > 255 || target_speed < 0)
    target_speed = 127;
  analogWrite(ENA, target_speed);
  analogWrite(ENB, target_speed);
}

void stopMovement(unsigned long the_delay=0){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MIN);
  if (the_delay != 0){
    delay(the_delay);  
  }
}

void moveForward(unsigned long the_delay=0){
  analogWrite(IN1, 240);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MAX);
  if (the_delay != 0){
    delay(the_delay);  
  }
}

void moveBackward(unsigned long the_delay){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MAX);
  analogWrite(IN3, PWM_MAX);
  analogWrite(IN4, PWM_MIN);
  delay(the_delay);
}

void turnLeft(unsigned long the_delay){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MAX);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MAX);
  delay(the_delay);
}

void turnRight(unsigned long the_delay){
  analogWrite(IN1, PWM_MAX);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MAX);
  analogWrite(IN4, PWM_MIN);
  delay(the_delay);
}

void turnLeft90(){
  setSpeed(PWM_MAX);
  turnLeft(460);
}

void turnRight90(){
  setSpeed(PWM_MAX);
  turnRight(420);
}