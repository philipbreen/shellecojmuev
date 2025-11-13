const int hallAPin = A0; // Blue (treated as MSB)
const int hallBPin = A1; // Green (middle bit)
const int hallCPin = A2; // White (LSB)

const int threshold = 200; // your requested threshold

void setup() {
  Serial.begin(9600);
  pinMode(hallAPin, INPUT); // using external pull-ups to 5V
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);
}

void loop() {
  // read analog and convert to 0/1
  int aRaw = analogRead(hallAPin);
  int bRaw = analogRead(hallBPin);
  int cRaw = analogRead(hallCPin);

  int hallA = (aRaw > threshold) ? 1 : 0;
  int hallB = (bRaw > threshold) ? 1 : 0;
  int hallC = (cRaw > threshold) ? 1 : 0;

  // pack bits: A = bit2, B = bit1, C = bit0
  byte pattern = (hallA << 2) | (hallB << 1) | hallC;

  // map the binary pattern to your state numbers (1..6)
  // pattern decimal -> state:
  // 1 -> 1, 5 -> 2, 4 -> 3, 6 -> 4, 2 -> 5, 3 -> 6
  byte stateNumber = 0; // 0 = invalid/unexpected pattern
  switch (pattern) {
    case 1: stateNumber = 1; break; // 001
    case 5: stateNumber = 2; break; // 101
    case 4: stateNumber = 3; break; // 100
    case 6: stateNumber = 4; break; // 110
    case 2: stateNumber = 5; break; // 010
    case 3: stateNumber = 6; break; // 011
    default: stateNumber = 0; break; // invalid (000 or 111)
  }

  Serial.print("pattern: ");
  Serial.print(pattern);                 // raw decimal of bits
  Serial.print("  A:"); Serial.print(hallA);
  Serial.print(" B:"); Serial.print(hallB);
  Serial.print(" C:"); Serial.print(hallC);
  Serial.print("  -> State: ");
  if (stateNumber == 0) Serial.println("INVALID");
  else Serial.println(stateNumber);

  delay(100);
}
