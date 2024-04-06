#include "movement.h"
#include <Wire.h>
#include <Servo.h>

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
#define SERVO_MIN 0
#define SERVO_MAX 180
#define TARGET_DIST_IN 12
#define TARGET_DIST_BW_MAX 8
#define TARGET_DIST_FW_MIN 16
#define TARGET_DIST_FW_MAX 48

static const int trig = A5, echo = A4;

Servo sensorServo;

static int origDist = 0, newDist = 0, closestDist = 1000;
static int closestServoPos = 90;

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

// Ultrasonic distance measurement Sub function
int getDistance() {
  digitalWrite(trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(trig, LOW);   
  float Fdistance = pulseIn(echo, HIGH);  
  //Fdistance= Fdistance / 58;    // in centimeters
  Fdistance = Fdistance / 148;    // in inches
  return (int)Fdistance;
}  

int scanClosest(){
  // scan the area and find the closest point to 12 ft
  sensorServo.write(0); // move the servo all the way right
  delay(1000);          // wait for servo to get in position
  for (int ii = 1; ii <= 180; ii+=10){
    sensorServo.write(ii);  // move the sensor over 10 degrees
    delay(100);             // wait for sesor to get in position
    newDist = getDistance();// get the new distance the sensor sees
    //Serial.print("newDist = ");
    //Serial.println(newDist);
    // set the closest distance to the new distance if its lower (ensure close dist > 12in)
    if (newDist < closestDist) {
      closestServoPos = ii;   // save the closest to target angle of the servo
      closestDist = newDist;  // save the closest distance
      /* Serial.print("closestDist = ");
      Serial.print(closestDist);
      Serial.print(", closestServoPos = ");
      Serial.println(closestServoPos); */
    }
  }
  sensorServo.write(90);
  delay(500);
  Serial.print("closestDist = ");
  Serial.print(closestDist);
  Serial.print(", closestServoPos = ");
  Serial.println(closestServoPos);
}

void keepDistance(int origDist){
  if (origDist > TARGET_DIST_FW_MIN && origDist < TARGET_DIST_FW_MAX){
    moveForward(100);
    stopMovement(200);
  } else if (origDist < TARGET_DIST_BW_MAX) {
    moveBackward(100);
    stopMovement(200);
  }
}

void follow() {
  Serial.println("WITHIN FOLLOW");
  setSpeed(PWM_MAX);
  bool scanPerformed = false;

  Serial.println("MOVING FORWARD");
  //moveForward(100);// move forward indefinitely
  
  origDist = getDistance();
  Serial.print("origDist = ");
  Serial.println(origDist);
  
  while (origDist <= TARGET_DIST_FW_MAX){
    Serial.println("WITHIN THE KEEP DIST LOOP");
    keepDistance(origDist);
    origDist = getDistance();
    if (origDist > TARGET_DIST_FW_MAX) break;
  }
  
  // if our middle distance is above 2*12in = 24in
  if (origDist > TARGET_DIST_FW_MAX){
    Serial.println("GONNA MOVE AFTER SCAN");
    stopMovement();
    scanClosest();
    scanPerformed = true;
  }

  // we should move because we are too far
  if (scanPerformed){
    // turn right and move
    if (closestServoPos <= 90 && closestDist <= TARGET_DIST_FW_MAX){
      Serial.println("TURNING RIGHT");
      turnRight(300);
      //turnRight((unsigned long)(340*(closestServoPos/90)));
      stopMovement(500);
      //moveForward(400);
      //stopMovement(500);
    }
    /*
    // stay in the same direction and move
    else if (89 < closestServoPos && closestServoPos < 9){
      Serial.println("MOVING FORWARD");
      moveForward(400);
    }
    */
    // turn left and move
    else if (closestDist <= TARGET_DIST_FW_MAX){
      Serial.println("TURNING LEFT");
      turnLeft(300);
      //turnLeft((unsigned long)(340*(closestServoPos/180)));
      stopMovement(500);
      //moveForward(400);
      //stopMovement(500);
    }

    else {
      // play speaker
      origDist = getDistance();
    }
  }
}

void setup() {
  //Wire.begin();
  Serial.begin(9600);
  sensorServo.attach(3, 700, 2400);

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

  follow();

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
  //long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
/* analogWrite(trig, 0);
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

  delay(100); */

  

  // temp
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  delay(10);
}
