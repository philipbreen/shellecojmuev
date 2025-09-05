//TALK TO YA BOYYY
const int ALIN_PIN = 9;  // High-side input pin
const int AHIN_PIN = 10; // Low-side input pin
const int BHIN_PIN = 5;  // High-side input pin
const int BLIN_PIN = 6; // Low-side input pin
const int switchPin = 4;
const int onOffPin = 3;
float R_FIXED =1500;
int val;
float vOut;
float vIn =5;

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

if(digitalRead(onOffPin)==HIGH){
calculateTemperature();
  val = map(analogRead(A0), 0, 1023, 0, 255);
  if (digitalRead(switchPin)==LOW) {
    reverseDrive();
  }
  else {
    forwardDrive();
  }}
  else {
    stopMotor();
  }


}
void reverseDrive() {
  analogWrite(ALIN_PIN, 0);
  analogWrite(AHIN_PIN, 0);
  analogWrite(BLIN_PIN, 255);
  analogWrite(BHIN_PIN, val);

  Serial.print("REVERSE: ");
  Serial.println(val);

}
void forwardDrive() {
  analogWrite(BLIN_PIN, 0);
  analogWrite(BHIN_PIN, 0);
  analogWrite(ALIN_PIN, 255);
  analogWrite(AHIN_PIN, val);

  Serial.print("FORWARD: ");
  Serial.println(val);
}
void stopMotor(){
   analogWrite(BLIN_PIN, 0);
  analogWrite(BHIN_PIN, 0);
  analogWrite(ALIN_PIN, 0);
  analogWrite(AHIN_PIN, 0);
}

float calculateTemperature() {
  vOut=map(analogRead(A2),0, 1023, 0, 5000)/1000.00;
  float r = (vOut * R_FIXED)/(vIn-vOut);
  
  const float R25 = 1500.0; // Your thermistor's resistance at 25°C
  float A1_coef, B1_coef, C1_coef, D1_coef;

  if (r > 1500) {
    A1_coef = 0.003354016;
    B1_coef = 0.000290967;
    C1_coef = 0.00000163214;
    D1_coef = 0.000000071922;
  } else {
    A1_coef = 0.003354016;
    B1_coef = 0.000293391;
    C1_coef = 0.00000349431;
    D1_coef = -0.000000771269;
  }

  float lnR = log(r / R25);
  float tempK = 1.0 / (A1_coef + B1_coef * lnR + C1_coef * lnR * lnR + D1_coef * lnR * lnR * lnR);
  Serial.println(tempK - 273.15);
}
