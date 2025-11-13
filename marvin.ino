const int hallAPin = A0; // Blue
const int hallBPin = A1; // Green
const int hallCPin = A2; // White

static byte lastValidState = 0;

int hallA, hallB, hallC;

void setup() {
  Serial.begin(9600);
  pinMode(hallAPin, INPUT_PULLUP); // internal pull-up just in case
  pinMode(hallBPin, INPUT_PULLUP);
  pinMode(hallCPin, INPUT_PULLUP);
}

void loop() {
  driveMotor();
  delay(100);
}

byte hallToState() {
  hallA = digitalRead(hallAPin);
  hallB = digitalRead(hallBPin);
  hallC = digitalRead(hallCPin);

  // note: Hall sensors are often active low (reverse bits if needed)
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
