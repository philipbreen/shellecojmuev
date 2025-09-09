#include <Arduino.h>
#include <TM1637Display.h>

// Pins
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x0f); // max brightness
}

void loop() {
  for (int whole = 0; whole <= 10; whole++) {
    for (int decimal = 0; decimal <= 99; decimal++) {
      // Split into digits
      int d0 = whole / 10;       // tens of whole
      int d1 = whole % 10;       // ones of whole
      int d2 = decimal / 10;     // tenths
      int d3 = decimal % 10;     // hundredths

      uint8_t data[4];
      data[0] = display.encodeDigit(d0);
      data[1] = display.encodeDigit(d1) | 0x80; // add decimal point here
      data[2] = display.encodeDigit(d2);
      data[3] = display.encodeDigit(d3);

      display.setSegments(data);

      delay(50); // speed of counting
    }
  }

  display.clear();
  delay(1000);
}
