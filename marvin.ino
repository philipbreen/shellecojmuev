const int ALIN_PIN = 9;  // High-side input pin
const int AHIN_PIN = 10; // Low-side input pin
const int BHIN_PIN = 5;  // High-side input pin
const int BLIN_PIN = 6; // Low-side input pin
const int switchPin = 4; //Forward or Reverse
const int onOffPin = 3;
const int hallAPin =7; //Blue
const int hallBPin = 8; //Green
const int hallCPin = 4; //White

  static byte lastValidState = 0;

int hallA;
int hallB;
int hallC;
int sensorvalue, output;
float R_FIXED = 1500;
int val;
float vOut;
float vIn = 5;
long frequency = 10000;
long freqVal;
bool highFreq = true;

void setup() {
  freqVal = ((16000000 / (8 * frequency)) - 1);
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(switchPin, INPUT);
  pinMode(onOffPin, INPUT);
  pinMode(AHIN_PIN, OUTPUT);
  pinMode(ALIN_PIN, OUTPUT);
  pinMode(BHIN_PIN, OUTPUT);
  pinMode(BLIN_PIN, OUTPUT);
  pinMode(hallAPin, INPUT);
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);
  digitalWrite(AHIN_PIN, LOW);
  digitalWrite(ALIN_PIN, LOW);
  digitalWrite(BHIN_PIN, LOW);
  digitalWrite(BLIN_PIN, LOW);
  //analogWrite(ALIN_PIN, 127);
}


void loop() {
/*
  sensorvalue = analogRead(A0);
  if (highFreq == true) {
    output = map(sensorvalue, 0, 1023, 0, 100);
    pwmWrite10kHz(ALIN_PIN, output);
  }
  else {
    output = map(sensorvalue, 0, 1023, 0, 255);
    analogWrite(ALIN_PIN, output);
  }

*/
driveMotor();
  delay(100);

}
byte hallToState() {
  /*if (digitalRead(HallAPin) == 0 && digitalRead(HallBPin) == 0 && digitalRead(HallCPin) == 1) {
    motorState = 0;
  }
  else if (digitalRead(HallAPin) == 1 && digitalRead(HallBPin) == 0 && digitalRead(HallCPin) == 1) {
    motorState = 1;
  }
  else if (digitalRead(HallAPin) == 1 && digitalRead(HallBPin) == 0 && digitalRead(HallCPin) == 0) {
    motorState = 2;
  }
  else if (digitalRead(HallAPin) == 1 && digitalRead(HallBPin) == 1 && digitalRead(HallCPin) == 0) {
    motorState = 3;
  }
  else if (digitalRead(HallAPin) == 0 && digitalRead(HallBPin) == 1 && digitalRead(HallCPin) == 0) {
    motorState = 4;
  }
  else if (digitalRead(HallAPin) == 0 && digitalRead(HallBPin) == 0 && digitalRead(HallCPin) == 0) {
    motorState = 5;
  }*/


  int hallA = digitalRead(HallAPin);
  int hallB = digitalRead(HallBPin);
  int hallC = digitalRead(HallCPin);

  byte state = (hallA << 2) | (hallB << 1) | hallC;
  return state;

}
void driveMotor() {
  byte state = hallToState();

  if (state <= 5) {
    lastValidState = state;
  } else {
    // invalid reading, reuse last valid one or stop motor
    state = lastValidState;
    // OR: stopMotor(); return;
  }
  Serial.println(state);
  switch (hallToState()) {
    case 0:
      //drive 0
      break;
    case 1:
      //drive 1
      break;
    case 2:
      //drive 2
      break;
    case 3:
      //drive 3
      break;
    case 4:
      //drive 4
      break;
    case 5:
      //drive 5
      break;

  }
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
    //freqVal=((16000000 / (8 * frequency)) - 1);
    ICR1 = freqVal;
    Serial.println(ICR1);
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
