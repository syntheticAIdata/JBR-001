#include <Servo.h>
#include <Modulino.h>
#include "Arduino_LED_Matrix.h"

// JBR-001 hardware
Servo headServo;
Servo leftArmServo;
Servo rightArmServo;

ModulinoBuzzer buzzer;
ModulinoDistance distanceSensor;

ArduinoLEDMatrix matrix;

// Servo pins
const int HEAD_SERVO_PIN = 9;
const int LEFT_ARM_SERVO_PIN = 10;
const int RIGHT_ARM_SERVO_PIN = 11;

// Servo resting positions
const int HEAD_CENTER = 90;
const int LEFT_ARM_CENTER = 90;
const int RIGHT_ARM_CENTER = 90;

// Distance detection
const float DETECTION_DISTANCE = 200.0;
const float RESET_DISTANCE = 250.0;

bool objectDetected = false;

// Small heart
// flipped to match display orientation
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


// Large heart
// flipped to match display orientation
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

// Heartbeat animation
unsigned long heartbeatTimer = 0;
int heartbeatStep = 0;

void heartbeat() {
  unsigned long now = millis();

  switch (heartbeatStep) {

    case 0:
      matrix.renderBitmap(heartLarge, 8, 13);
      heartbeatTimer = now;
      heartbeatStep = 1;
      break;

    case 1:
      if (now - heartbeatTimer >= 120) {
        matrix.renderBitmap(heartSmall, 8, 13);
        heartbeatTimer = now;
        heartbeatStep = 2;
      }
      break;

    case 2:
      if (now - heartbeatTimer >= 100) {
        matrix.renderBitmap(heartLarge, 8, 13);
        heartbeatTimer = now;
        heartbeatStep = 3;
      }
      break;

    case 3:
      if (now - heartbeatTimer >= 160) {
        matrix.renderBitmap(heartSmall, 8, 13);
        heartbeatTimer = now;
        heartbeatStep = 4;
      }
      break;

    case 4:
      if (now - heartbeatTimer >= 700) {
        heartbeatStep = 0;
      }
      break;
  }
}

// Play JBR-001's friendly greeting
void playHello() {
  buzzer.tone(523, 120);   // C5
  delay(150);

  buzzer.tone(659, 120);   // E5
  delay(150);

  buzzer.tone(784, 180);   // G5
  delay(210);

  buzzer.tone(1047, 250);  // C6
  delay(270);
}

// Perform JBR-001's startup movement
void makeMovement() {

  // Look left, right, then forward
  headServo.write(70);
  delay(400);

  headServo.write(110);
  delay(400);

  headServo.write(HEAD_CENTER);
  delay(400);

  // Move both arms
  leftArmServo.write(70);
  rightArmServo.write(110);
  delay(500);

  leftArmServo.write(110);
  rightArmServo.write(70);
  delay(500);

  // Return to resting position
  leftArmServo.write(LEFT_ARM_CENTER);
  rightArmServo.write(RIGHT_ARM_CENTER);
  delay(500);
}

void setup() {
  Modulino.begin();

  buzzer.begin();
  distanceSensor.begin();
  matrix.begin();

  // Show the heart while JBR-001 starts
  matrix.renderBitmap(heartSmall, 8, 13);

  // Move each servo to its resting position
  headServo.attach(HEAD_SERVO_PIN);
  headServo.write(HEAD_CENTER);
  delay(400);

  leftArmServo.attach(LEFT_ARM_SERVO_PIN);
  leftArmServo.write(LEFT_ARM_CENTER);
  delay(400);

  rightArmServo.attach(RIGHT_ARM_SERVO_PIN);
  rightArmServo.write(RIGHT_ARM_CENTER);
  delay(400);

  delay(500);

  // Say hello and come to life
  playHello();
  makeMovement();
}

void loop() {

  // Keep the heart beating
  heartbeat();

  // React when someone approaches
  if (distanceSensor.available()) {
    float distance = distanceSensor.get();

    if (distance < DETECTION_DISTANCE && !objectDetected) {
      objectDetected = true;
      playHello();
    }

    // Ready for the next greeting once they move away
    if (distance > RESET_DISTANCE) {
      objectDetected = false;
    }
  }
}