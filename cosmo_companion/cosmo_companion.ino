#include "movement.h"
#include <Wire.h>

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

static const int trig = A5, echo = A4;

void drawSquare(){
  stopMovement(500);
  setSpeed(PWM_MAX);

  for (int ii = 0; ii < 4; ++ii){
    moveForward(1000);
    stopMovement(500);
    turnLeft90();
    stopMovement(500);
  }
}

void farm(){
  stopMovement(500);
  setSpeed(PWM_MAX);

  moveForward(1000);
  stopMovement(500);

  turnRight90();
  stopMovement(500);

  moveForward(300);
  stopMovement(500);

  turnLeft90();
  stopMovement(500);

  moveBackward(1000);
  stopMovement(500);

  turnRight90();
  stopMovement(500);

  moveForward(300);
  stopMovement(500);

  turnLeft90();
  stopMovement(500);

  moveForward(1000);
  stopMovement(500);

  turnRight90();
  stopMovement(500);

  moveForward(300);
  stopMovement(500);

  turnLeft90();
  stopMovement(500);

  moveBackward(1000);
  stopMovement(500);

  turnLeft90();
  stopMovement(500);

  moveForward(900);
  stopMovement(500);

  turnRight90();
  stopMovement(500);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void setup() {
  //Wire.begin();
  Serial.begin(9600);

  // MOTOR CONTROL
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, PWM_MAX);
  analogWrite(ENB, PWM_MAX);

  // ULTRASONIC SENSOR
  pinMode(trig, OUTPUT); // output pin
  pinMode(echo, INPUT); // input pin

  // temp
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  //drawSquare();
  //farm();
  /* analogWrite(trig, 0);
  delayMicroseconds(2);
  analogWrite(trig, 255);
  delayMicroseconds(10);
  long duration = pulseIn(echo, HIGH);
  Serial.print(duration);
  Serial.println();

  Wire.requestFrom(HC_SR04_I2C_ADDR, 2);
  while (Wire.available()){
    char x = Wire.read();
    Serial.print(x);
  } */

  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  analogWrite(trig, 0);
  delayMicroseconds(2);
  analogWrite(trig, 255);
  delayMicroseconds(10);
  analogWrite(trig, 0);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  
  duration = pulseIn(echo , HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print("Sensor1: ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

  // temp
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  delay(10);
}
