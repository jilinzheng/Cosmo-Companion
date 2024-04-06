#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define PWM_MAX 255
#define PWM_MIN 0

static void setSpeed(int target_speed){
  if (target_speed > 255 || target_speed < 0)
    target_speed = 127;
  analogWrite(ENA, target_speed);
  analogWrite(ENB, target_speed);
}

static void stopMovement(){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MIN);
}

static void moveForward(){
  analogWrite(IN1, PWM_MAX);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, 220);
}

static void moveBackward(){
  analogWrite(IN1, PWM_MAX);
  analogWrite(IN2, PWM_MAX);
  analogWrite(IN3, PWM_MAX);
  analogWrite(IN4, PWM_MIN);
}

static void turnLeftForward(){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MAX);
}

static void turnRightForward(){
  analogWrite(IN1, PWM_MAX);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MIN);
}

static void turnLeftBackward(){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MAX);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MIN);
}

static void turnRightBackward(){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MAX);
  analogWrite(IN4, PWM_MIN);
}

void drawSquare(){
  stopMovement();

  for (int ii = 0; ii < 4; ++ii){
    moveForward();
    delay(500);
    stopMovement();
    delay(500);
    turnLeftForward();
    delay(500);
    stopMovement();
    delay(500);
  }
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, PWM_MAX);
  analogWrite(ENB, PWM_MAX);
}

void loop() {
  //drawSquare();
  setSpeed(PWM_MAX);
  moveForward();
  delay(1000);
  stopMovement();
  delay(3000);
/* 
  turnLeftForward();
  delay(500);
  stopMovement();
  delay(500);
  turnRightForward();
  delay(500);
  stopMovement();
  delay(500);
  turnLeftBackward();
  delay(500);
  stopMovement();
  delay(500);
  turnRightBackward();
  delay(500);
  stopMovement();
  delay(500);
   */
}
