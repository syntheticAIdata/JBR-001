#include "Arduino_LED_Matrix.h"
#include <Servo.h>

ArduinoLEDMatrix matrix;
Servo motorleftarm;
Servo motorrightarm;
Servo motorhead;

unsigned long lastArmMove = 0;
bool armsUp = false;

// Small heart - flipped upside down
uint8_t heartSmall[8][13] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,1,1,1,0,0,0,0,0},
  {0,0,0,0,1,1,1,1,1,0,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,0,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,1,1,1,1,0,0},
  {0,0,0,1,1,0,0,0,1,1,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0}
};


// Large heart - flipped upside down
uint8_t heartLarge[8][13] = {
  {0,0,0,0,1,1,1,1,1,0,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,0,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,0,1,1,1,1,1,0},
  {0,0,1,1,1,0,0,0,1,1,1,0,0}
};


void heartbeat() {

  matrix.renderBitmap(heartLarge, 8, 13);
  delay(120);

  matrix.renderBitmap(heartSmall, 8, 13);
  delay(100);

  matrix.renderBitmap(heartLarge, 8, 13);
  delay(160);

  matrix.renderBitmap(heartSmall, 8, 13);
  delay(700);
}


void setup() {

  matrix.begin();

  //  9 - head
  // 11 - right
  // 10 - left

  motorleftarm.attach(10);
  motorrightarm.attach(11);
  delay(1000);

  motorleftarm.write(90);
  motorrightarm.write(90);
  delay(1000);

}


void loop() {

  // Heart keeps pulsating
  heartbeat();

  if (millis() - lastArmMove >= 1000) {
    lastArmMove = millis();
    armsUp = !armsUp;

    motorleftarm.write(armsUp ? 90 : 50);
    motorrightarm.write(armsUp ? 130 : 90);
  }
}