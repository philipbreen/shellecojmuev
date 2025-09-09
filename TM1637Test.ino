#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x0f);
}

void loop() {
  // Example: show 1.50
  uint8_t data[4];

  data[0] = display.encodeDigit(0);                // leading 0
  data[1] = display.encodeDigit(1) | 0x80;         // "1." ← dot here
  data[2] = display.encodeDigit(5);                // "5"
  data[3] = display.encodeDigit(0);                // "0"

  display.setSegments(data);

  while (1); // stop here for demo
}
