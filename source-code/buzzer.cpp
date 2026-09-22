#include <Modulino.h>

// JBR-001 hardware
ModulinoBuzzer buzzer;

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

  // Say hello
  playHello();
}

void loop() {

}