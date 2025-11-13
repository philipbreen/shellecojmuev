const int hallAPin = A0; // Blue
const int hallBPin = A1; // Green
const int hallCPin = A2; // White

static byte lastValidState = 0;

int hallA;
int hallB;
int hallC;

void setup() {
  Serial.begin(9600);
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

  // Convert to digital (0 or 1) using a threshold
  // Adjust threshold based on your Hall sensors (usually around 512)
  hallA = (analogA > 512) ? 1 : 0;
  hallB = (analogB > 512) ? 1 : 0;
  hallC = (analogC > 512) ? 1 : 0;

  // Combine bits into a 3-bit state (0–7)
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
  }

  Serial.print("State: ");
  Serial.println(state);

  switch (state) {
    case 0:
      // drive 0
      break;
    case 1:
      // drive 1
      break;
    case 2:
      // drive 2
      break;
    case 3:
      // drive 3
      break;
    case 4:
      // drive 4
      break;
    case 5:
      // drive 5
      break;
  }
}
