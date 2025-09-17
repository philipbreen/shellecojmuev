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
  analogWrite(ALIN_PIN, 255);
  analogWrite(AHIN_PIN, 126);
  delay(2000);
    analogWrite(ALIN_PIN, 255);
  analogWrite(AHIN_PIN, 0);
}
