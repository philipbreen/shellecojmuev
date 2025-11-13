const int hallAPin = A0; // Blue
const int hallBPin = A1; // Green
const int hallCPin = A2; // White

const int threshold = 200;

void setup() {
  Serial.begin(9600);
  pinMode(hallAPin, INPUT);  // external pull-ups already wired
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);
}

void loop() {
  // Read analog voltages and threshold to 0/1
  int aRaw = analogRead(hallAPin);
  int bRaw = analogRead(hallBPin);
  int cRaw = analogRead(hallCPin);

  int hallA = (aRaw > threshold) ? 1 : 0;
  int hallB = (bRaw > threshold) ? 1 : 0;
  int hallC = (cRaw > threshold) ? 1 : 0;

  // Combine bits: A=Blue, B=Green, C=White
  byte pattern = (hallA << 2) | (hallB << 1) | hallC;

  // Map 3-bit pattern to your state number (1–6)
  byte stateNumber = 0;
  switch (pattern) {
    case 0b001: stateNumber = 1; break; // White high
    case 0b101: stateNumber = 2; break; // Blue + White
    case 0b100: stateNumber = 3; break; // Blue
    case 0b110: stateNumber = 4; break; // Green + Blue
    case 0b010: stateNumber = 5; break; // Green
    case 0b011: stateNumber = 6; break; // Green + White
    default: stateNumber = 0; break;    // invalid (000 or 111)
  }

  Serial.print("A(Blue): "); Serial.print(hallA);
  Serial.print("  B(Green): "); Serial.print(hallB);
  Serial.print("  C(White): "); Serial.print(hallC);
  Serial.print("  -> State: ");
  if (stateNumber == 0) Serial.println("INVALID");
  else Serial.println(stateNumber);

  delay(100);
}
