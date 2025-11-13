// Hall sensor pins
const int hallAPin = A0; // Blue
const int hallBPin = A1; // Green
const int hallCPin = A2; // White

static byte lastValidState = 0;
int hallA, hallB, hallC;

void setup() {
  Serial.begin(9600);

  // Enable internal pull-ups to avoid floating inputs
  pinMode(hallAPin, INPUT_PULLUP);
  pinMode(hallBPin, INPUT_PULLUP);
  pinMode(hallCPin, INPUT_PULLUP);
}

void loop() {
  driveMotor();
  delay(100);
}

byte hallToState() {
  // Read active-low Hall sensors (invert logic)
  hallA = !digitalRead(hallAPin);
  hallB = !digitalRead(hallBPin);
  hallC = !digitalRead(hallCPin);

  // Combine into 3-bit state
  byte state = (hallA << 2) | (hallB << 1) | hallC;

  // Debug print
  Serial.print("A: "); Serial.print(hallA);
  Serial.print("  B: "); Serial.print(hallB);
  Serial.print("  C: "); Serial.print(hallC);
  Serial.print("  State: "); Serial.println(state);

  return state;
}

void driveMotor() {
  byte state = hallToState();

  if (state <= 5) {
    lastValidState = state;
  } else {
    state = lastValidState;
  }

  // Example motor control cases
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
