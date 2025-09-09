/*
  LCD Display Example – Battery Status

  Shows:
   • Battery Temperature (°F)
   • Battery Charge (%)
   • Timer (counts up every second)

  Wiring (16x2 LCD, HD44780, 4-bit mode):
   LCD RS pin → Arduino 12
   LCD Enable pin → Arduino 11
   LCD D4 pin → Arduino 5
   LCD D5 pin → Arduino 4
   LCD D6 pin → Arduino 3
   LCD D7 pin → Arduino 2
   LCD R/W pin → GND
   LCD VSS pin → GND
   LCD VCC pin → 5V
   10K pot: ends → 5V & GND, wiper → VO (LCD pin 3)

*/

#include <LiquidCrystal.h>

// Pins: RS, E, D4, D5, D6, D7
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Dummy values for battery data (replace with sensor/ADC readings later)
int batteryTempF = 75;     // Example: 75°F
int batteryPercent = 82;   // Example: 82%

unsigned long prevMillis = 0;
unsigned long secondsElapsed = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  // Update timer every 1000 ms
  if (currentMillis - prevMillis >= 1000) {
    prevMillis = currentMillis;
    secondsElapsed++;

    // First row: Battery Temp + %
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(batteryTempF);
    lcd.print((char)223); // degree symbol
    lcd.print("F ");

    lcd.print(batteryPercent);
    lcd.print("%");

    // Second row: Timer
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(secondsElapsed);
    lcd.print("s   "); // spaces to overwrite old chars
  }
}
