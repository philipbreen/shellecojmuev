const int hallAPin = A0; // Blue
const int hallBPin = A1; // Green
const int hallCPin = A2; // White

const int threshold = 100;
static byte lastValidState = 0;

int hallA, hallB, hallC;

void setup() {
  Serial.begin(9600);
  pinMode(hallAPin, INPUT);  // using external pull-ups
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);
}

void loop() {
  driveMotor();
  delay(100);
}

byte hallToState() {
  // Read analog values and threshold them
  int aRaw = analogRead(hallAPin);
  int bRaw = analogRead(hallBPin);
  int cRaw = analogRead(hallCPin);

  hallA = (aRaw > threshold) ? 1 : 0;
  hallB = (bRaw > threshold) ? 1 : 0;
  hallC = (cRaw > threshold) ? 1 : 0;

  // Combine bits: A=Blue, B=Green, C=White
  byte pattern = (hallA << 2) | (hallB << 1) | hallC;

  // Map pattern to motor state number (1–6)
  byte motorState = 0;
  switch (pattern) {
    case 0b001: motorState = 1; break; // White high
    case 0b101: motorState = 2; break; // Blue + White
    case 0b100: motorState = 3; break; // Blue
    case 0b110: motorState = 4; break; // Green + Blue
    case 0b010: motorState = 5; break; // Green
    case 0b011: motorState = 6; break; // Green + White
    default: motorState = 0; break;    // invalid
  }

  return motorState;
}

void driveMotor() {
  byte state = hallToState();

  if (state >= 1 && state <= 6) {
    lastValidState = state;
  } else {
    state = lastValidState; // use last valid if invalid
  }

  Serial.print("A(Blue): "); Serial.print(hallA);
  Serial.print("  B(Green): "); Serial.print(hallB);
  Serial.print("  C(White): "); Serial.print(hallC);
  Serial.print("  -> State: ");
  if (state == 0) Serial.println("INVALID");
  else Serial.println(state);

  // You can add drive logic per state below:
  switch (state) {
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
    case 6:
      // drive 6
      break;
  }
}
