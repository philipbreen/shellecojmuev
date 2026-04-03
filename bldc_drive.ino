// ============================================================
// BLDC Motor Controller - Teensy 4.1
// High-side PWM @ 2.5 kHz via FlexPWM | Low-side digital
// ============================================================
//
// PIN ASSIGNMENT RATIONALE (Teensy 4.1 FlexPWM timer groups):
//
//   HIGH SIDE (PWM) — one pin per separate FlexPWM module
//   so each can be driven independently without crosstalk:
//     Pin  4 → FlexPWM2 Module0  (aHighPin)
//     Pin  5 → FlexPWM2 Module1  (bHighPin)
//     Pin  6 → FlexPWM2 Module2  (cHighPin)
//
//   Setting analogWriteFrequency on pin 4 affects only Mod0,
//   pin 5 only Mod1, pin 6 only Mod2 — no interference.
//
//   LOW SIDE (digital only — no PWM needed):
//     Pin 14 → (aLowPin)
//     Pin 15 → (bLowPin)
//     Pin 16 → (cLowPin)
//
//   HALL SENSORS:
//     Pin  7 → Hall A (Blue)
//     Pin  8 → Hall B (Yellow)
//     Pin  9 → Hall C (White)
//
//   THROTTLE:
//     A0 (Pin 14 analog / use a dedicated analog pin)
//     → remapped to Pin A1 (17) to avoid conflict with aLowPin
//
// NOTE: Teensy 4.1 is 3.3V logic. Ensure your gate driver
//       inputs are 3.3V compatible, or use a level shifter.
// ============================================================

// --- Hall Sensor Pins ---
const int hallAPin = 7;   // Blue
const int hallBPin = 8;   // Yellow
const int hallCPin = 9;   // White

// --- High-Side PWM Pins (each on its own FlexPWM module) ---
const int aHighPin = 4;   // FlexPWM2 Module0 BLUE
const int bHighPin = 5;   // FlexPWM2 Module1 YELLOW
const int cHighPin = 6;   // FlexPWM2 Module2 WHITE

// --- Low-Side Digital Pins ---
const int aLowPin = 14;
const int bLowPin = 15;
const int cLowPin = 16;

// --- Throttle Potentiometer ---
// A0 == pin 14 on Teensy 4.1, which conflicts with aLowPin.
// Use A1 (pin 15) or A2 (pin 16) — here we use A16 (pin 40).
const int potPin = A16;    // Pin 40 — no conflicts

// --- PWM Config ---
const float PWM_FREQ       = 2500.0f;  // 2.5 kHz
const int   PWM_RESOLUTION = 8;        // 8-bit: 0–255, matches map() output

int SPEED = 0;

// ============================================================
void setup() {
  Serial.begin(115200);

  // Hall sensor inputs (internal keeper resistors are default;
  // use INPUT_PULLUP if your sensor outputs are open-drain)
  pinMode(hallAPin, INPUT);
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);

  // Gate driver outputs
  pinMode(aHighPin, OUTPUT);
  pinMode(bHighPin, OUTPUT);
  pinMode(cHighPin, OUTPUT);
  pinMode(aLowPin,  OUTPUT);
  pinMode(bLowPin,  OUTPUT);
  pinMode(cLowPin,  OUTPUT);

  // Set PWM resolution first, then frequency.
  // On Teensy 4.1 the order matters — resolution affects
  // how the timer modulus is calculated.
  analogWriteResolution(PWM_RESOLUTION);

  // Each of pins 4, 5, 6 is on its own FlexPWM module,
  // so these three calls are fully independent.
  analogWriteFrequency(aHighPin, PWM_FREQ);
  analogWriteFrequency(bHighPin, PWM_FREQ);
  analogWriteFrequency(cHighPin, PWM_FREQ);

  // Safe startup — all switches off before first hall read
  driveStates(0, 0, 0, 0, 0, 0);
}

// ============================================================
void loop() {
  driveMotor();
}

// ============================================================
// Pack hall sensor readings into a 3-bit state byte
// ============================================================
byte hallToState() {
  int hallA = digitalRead(hallAPin);
  int hallB = digitalRead(hallBPin);
  int hallC = digitalRead(hallCPin);
  return (byte)((hallA << 2) | (hallB << 1) | hallC);
}

// ============================================================
// Read throttle + hall state, apply commutation
// ============================================================
void driveMotor() {
  byte state = hallToState();
  SPEED = map(analogRead(potPin), 0, 1023, 0, 255);

  switch (state) {
    // aHigh  bHigh  cHigh  aLow  bLow  cLow
    case 0b001: driveStates(SPEED, 0,     0,     0, 0, 1); Serial.println("State 1"); break;
    case 0b101: driveStates(SPEED, 0,     0,     0, 1, 0); Serial.println("State 2"); break;
    case 0b100: driveStates(0,     0,     SPEED, 0, 1, 0); Serial.println("State 3"); break;
    case 0b110: driveStates(0,     0,     SPEED, 1, 0, 0); Serial.println("State 4"); break;
    case 0b010: driveStates(0,     SPEED, 0,     1, 0, 0); Serial.println("State 5"); break;
    case 0b011: driveStates(0,     SPEED, 0,     0, 0, 1); Serial.println("State 6"); break;
    default:    driveStates(0,     0,     0,     0, 0, 0); Serial.println("ERROR");   break;
  }
}

// ============================================================
// Apply switching state to gate driver pins
// Low-side written first to prevent shoot-through
// ============================================================
void driveStates(uint8_t aHigh, uint8_t bHigh, uint8_t cHigh,
                 uint8_t aLow,  uint8_t bLow,  uint8_t cLow) {
  digitalWrite(aLowPin, aLow);
  digitalWrite(bLowPin, bLow);
  digitalWrite(cLowPin, cLow);

  analogWrite(aHighPin, aHigh);
  analogWrite(bHighPin, bHigh);
  analogWrite(cHighPin, cHigh);
}