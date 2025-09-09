#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x0f);
}

void loop() {
  for (int whole = 0; whole <= 10; whole++) {
    for (int decimal = 0; decimal <= 99; decimal++) {
      int value = whole * 100 + decimal; // e.g., 1.50 → 150

      // 0b0100 → decimal point after 2nd digit (xx.xx)
      display.showNumberDecEx(value, 0b0100, true);

      delay(50);
    }
  }

  display.clear();
  delay(1000);
}
