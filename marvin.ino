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
  int analogA = analogRead(hallAPin);
  int analogB = analogRead(hallBPin);
  int analogC = analogRead(hallCPin);

  // Use lower threshold
  const int threshold = 65;

  hallA = (analogA > threshold) ? 1 : 0;
  hallB = (analogB > threshold) ? 1 : 0;
  hallC = (analogC > threshold) ? 1 : 0;

  Serial.print("Green: ");
  Serial.print(analogB);
  Serial.print("  Blue: ");
  Serial.print(analogA);
  Serial.print("  White: ");
  Serial.println(analogC);

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
  Serial.println(state);
}
