#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x0f); // Max brightness
}

void loop() {
  // Count from 00.00 to 10.99
  for (int whole = 0; whole <= 10; whole++) {
    for (int decimal = 0; decimal <= 99; decimal++) {
      // Compute digits: XX.XX
      int left = whole / 10;         // tens
      int right = whole % 10;        // ones
      int d1 = decimal / 10;         // tenths
      int d2 = decimal % 10;         // hundredths

      uint8_t data[4];
      data[0] = display.encodeDigit(left);
      data[1] = display.encodeDigit(right) | 0x80; // add decimal point here
      data[2] = display.encodeDigit(d1);
      data[3] = display.encodeDigit(d2);

      display.setSegments(data);

      delay(50); // adjust counting speed
    }
  }

  // After finishing, clear and restart
  display.clear();
  delay(1000);
}
