const int hallAPin = A0; // Blue
const int hallBPin = A1; // Green
const int hallCPin = A2; // White

static byte lastValidState = 0;

int hallA, hallB, hallC;

void setup() {
  Serial.begin(9600);
  pinMode(hallAPin, INPUT);
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);
}

void loop() {
  driveMotor();
  delay(100);
}

byte hallToState() {
  // Read analog values (0–1023)
  int analogA = analogRead(hallAPin);
  int analogB = analogRead(hallBPin);
  int analogC = analogRead(hallCPin);

  // Convert analog readings to digital (0 or 1)
  const int threshold = 200;
  hallA = (analogA > threshold) ? 1 : 0;
  hallB = (analogB > threshold) ? 1 : 0;
  hallC = (analogC > threshold) ? 1 : 0;

  // Combine into a 3-bit state
  byte state = (hallA << 2) | (hallB << 1) | hallC;
  return state;
}

void driveMotor() {
  byte state = hallToState();

  if (state <= 5) {
    lastValidState = state;
  } else {
    state = lastValidState;
  }

  Serial.print("State: ");
  Serial.print(state);
  Serial.print("  A: "); Serial.print(hallA);
  Serial.print("  B: "); Serial.print(hallB);
  Serial.print("  C: "); Serial.println(hallC);
}
