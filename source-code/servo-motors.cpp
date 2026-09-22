#include <Servo.h>

// JBR-001 hardware
Servo headServo;
Servo leftArmServo;
Servo rightArmServo;

// Servo pins
const int HEAD_SERVO_PIN = 9;
const int LEFT_ARM_SERVO_PIN = 10;
const int RIGHT_ARM_SERVO_PIN = 11;

// Servo resting positions
const int HEAD_CENTER = 90;
const int LEFT_ARM_CENTER = 90;
const int RIGHT_ARM_CENTER = 90;

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

  // Come to life
  makeMovement();
}

void loop() {

}