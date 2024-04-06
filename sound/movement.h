void setSpeed(int target_speed);

void stopMovement(int the_delay);



void moveForward(int the_delay); = {
  int melody[] = {
    NOTE_GS4
  };

  int noteDurations[] = { 2 };

  void setup() {
    for (int thisNote = 0; thisNote < 7; thisNote++){
      int noteDuration = 1000 / noteDurations[thisNote];

      tone(7, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration / 10;
      delay(pauseBetweenNotes);
      noTone(7);
    }

  };


};



void moveBackward(int the_delay) = {
  int melody[] = {
    NOTE_GS2
  };

  int noteDurations[] = { 4 };

  for (int thisNote = 0; thisNote < 1; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];

    tone(7, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.5;

    delay(pauseBetweenNotes);

    noTone(7);
  }
};


void turnLeft(int the_delay);

void turnRight(int the_delay);

void turnLeft90();

void turnRight90();