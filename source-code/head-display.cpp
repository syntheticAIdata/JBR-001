#include "Arduino_LED_Matrix.h"

// JBR-001 hardware
ArduinoLEDMatrix matrix;

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

void setup() {
  matrix.begin();

  // Show the heart while JBR-001 starts
  matrix.renderBitmap(heartSmall, 8, 13);
}

void loop() {

  // Keep the heart beating
  heartbeat();

}