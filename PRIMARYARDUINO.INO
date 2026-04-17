// TALK TO YA BOYYY (CLEAN FIXED VERSION)

const int AHIN_PIN = 10;   // ONLY HIGH SIDE PIN (OC1B)
const int throttlePin = A0;

const long frequency = 10000;   // 10kHz PWM
const int maxDuty = 100;

int sensorValue = 0;
int output = 0;

long freqVal;

void setupPWM10kHz() {
  // Reset Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // Fast PWM mode 14 (TOP = ICR1)
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);

  // Prescaler = 8
  TCCR1B |= (1 << CS11);

  // Set TOP for 10kHz
  freqVal = (16000000 / (8 * frequency)) - 1;
  ICR1 = freqVal;

  // Enable OC1B (Pin 10 output)
  TCCR1A |= (1 << COM1B1);
}

void pwmWrite10kHz_Pin10(int dutyPercent) {
  dutyPercent = constrain(dutyPercent, 0, 100);
  OCR1B = (dutyPercent * ICR1) / 100;
}

void setup() {
  Serial.begin(9600);

  pinMode(AHIN_PIN, OUTPUT);
  pinMode(throttlePin, INPUT);

  digitalWrite(AHIN_PIN, LOW);

  setupPWM10kHz();
}

void loop() {
  sensorValue = analogRead(throttlePin);
  if (sensorValue<10){
    sensorValue=0;
  }
  output = map(sensorValue, 0, 1023, 0, maxDuty);
  output = constrain(output, 0, maxDuty);

  pwmWrite10kHz_Pin10(output);

  Serial.println(output);

  delay(20);
}
