//TALK TO YA BOYYY
const int ALIN_PIN = 9;  // High-side input pin
const int AHIN_PIN = 10; // Low-side input pin
const int BHIN_PIN = 5;  // High-side input pin
const int BLIN_PIN = 6; // Low-side input pin
const int switchPin = 4; //Forward or Reverse
const int onOffPin = 3;
float R_FIXED = 1500;
int val;
float vOut;
float vIn = 5;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(switchPin, INPUT);
  pinMode(onOffPin, INPUT);
  pinMode(AHIN_PIN, OUTPUT);
  pinMode(ALIN_PIN, OUTPUT);
  pinMode(BHIN_PIN, OUTPUT);
  pinMode(BLIN_PIN, OUTPUT);

  digitalWrite(AHIN_PIN, LOW);
  digitalWrite(ALIN_PIN, LOW);
  digitalWrite(BHIN_PIN, LOW);
  digitalWrite(BLIN_PIN, LOW);
}

void loop() {
delay(2000);
pwmWrite10kHz(ALIN_PIN, 0);   // 75% duty on pin 9
pwmWrite10kHz(AHIN_PIN, 0);  // 10% duty on pin 10
  delay(2000);

pwmWrite10kHz(ALIN_PIN, 50);   // 75% duty on pin 9
pwmWrite10kHz(AHIN_PIN, 50);  // 10% duty on pin 10
}


void pwmWrite10kHz(uint8_t pin, uint8_t dutyCyclePercent) {
  // Limit duty cycle to 0–100%
  if (dutyCyclePercent > 100) dutyCyclePercent = 100;

  // Configure Timer1 only once
  static bool initialized = false;
  if (!initialized) {
    // Reset Timer1 control registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;

    // Fast PWM mode with ICR1 as TOP
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    // Non-inverting mode on OC1A (pin 9) and OC1B (pin 10)
    // We'll enable them individually below
    // Prescaler = 8
    TCCR1B |= (1 << CS11);

    // Set TOP value for 10 kHz
    // fPWM = 16MHz / (prescaler * (1 + ICR1))
    // ICR1 = (16MHz / (8 * 10kHz)) - 1 = 199
    ICR1 = 199;

    initialized = true;
  }

  if (pin == 9) {
    pinMode(9, OUTPUT);
    TCCR1A |= (1 << COM1A1);  // enable output on pin 9
    OCR1A = (dutyCyclePercent * ICR1) / 100;
  } else if (pin == 10) {
    pinMode(10, OUTPUT);
    TCCR1A |= (1 << COM1B1);  // enable output on pin 10
    OCR1B = (dutyCyclePercent * ICR1) / 100;
  }
}
