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
      // Build number like "12.34"
      int value = whole * 100 + decimal; // e.g., 12*100 + 34 = 1234

      // Show with decimal point at position 2 (between digits 2 and 3)
      display.showNumberDecEx(value, 0b01000000, true);

      delay(50); // Adjust speed here (50ms per step)
    }
  }

  // After finishing, clear and loop again
  display.clear();
  delay(1000);
}
