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

static void stopMovement(int the_delay){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MIN);
  delay(the_delay);
}

static void moveForward(int the_delay){
  analogWrite(IN1, PWM_MAX);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, 240);
  delay(the_delay);
}

static void moveBackward(int the_delay){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MAX);
  analogWrite(IN3, 240);
  analogWrite(IN4, PWM_MIN);
  delay(the_delay);
}

static void turnLeft(int the_delay){
  analogWrite(IN1, PWM_MIN);
  analogWrite(IN2, PWM_MAX);
  analogWrite(IN3, PWM_MIN);
  analogWrite(IN4, PWM_MAX);
  delay(the_delay);
}

static void turnRight(int the_delay){
  analogWrite(IN1, PWM_MAX);
  analogWrite(IN2, PWM_MIN);
  analogWrite(IN3, PWM_MAX);
  analogWrite(IN4, PWM_MIN);
  delay(the_delay);
}

static void turnLeft90(){
  setSpeed(PWM_MAX);
  turnLeft(340);
}

static void turnRight90(){
  setSpeed(PWM_MAX);
  turnRight(340);
}

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
  drawSquare();
  farm();
}
