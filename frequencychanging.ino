// Arduino Uno - 10 kHz PWM on pin 3 using Timer2

void setup() {
  pinMode(3, OUTPUT);  // Set pin 3 as PWM output

  // Reset Timer2 control registers
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  // Fast PWM mode with TOP = OCR2A
  TCCR2A |= (1 << WGM21) | (1 << WGM20);  // Mode bits
  TCCR2B |= (1 << WGM22);

  // Non-inverting mode on OC2B (pin 3)
  TCCR2A |= (1 << COM2B1);

  // Set prescaler to 8
  TCCR2B |= (1 << CS21);

  // Set TOP value for 10 kHz
  // fPWM = 16MHz / (prescaler * (1 + OCR2A))
  // OCR2A = (16MHz / (8 * 10kHz)) - 1 = 199
  OCR2A = 199;

  // Set duty cycle (0–199). 100 ≈ 50%
  OCR2B = 100;
}

void loop() {
  // Nothing here, PWM runs in hardware
}
