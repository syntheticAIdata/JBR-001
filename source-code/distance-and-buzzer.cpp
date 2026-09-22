#include <Modulino.h>

// JBR-001 hardware
ModulinoBuzzer buzzer;
ModulinoDistance distanceSensor;

// Distance detection
const float DETECTION_DISTANCE = 200.0;
const float RESET_DISTANCE = 250.0;

bool objectDetected = false;

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

void setup() {
  Modulino.begin();

  buzzer.begin();
  distanceSensor.begin();

  // Say hello
  playHello();
}

void loop() {

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