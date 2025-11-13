
const int hallAPin =A0; //Blue
const int hallBPin = A1; //Green
const int hallCPin = A2; //White

static byte lastValidState = 0;

int hallA;
int hallB;
int hallC;


void setup() {
  Serial.begin(9600); 
}

void loop() {
  driveMotor();
/*
  Serial.print("A: ");
  Serial.print(hallA);
  Serial.print("B: ");
  Serial.print(hallB);
  Serial.print("C: ");
  Serial.println(hallC);
*/
  delay(100); 
}
byte hallToState() {

  int hallA = digitalRead(HallAPin);
  int hallB = digitalRead(HallBPin);
  int hallC = digitalRead(HallCPin);

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
    // OR: stopMotor(); return;
  }
  Serial.println(state);
  switch (hallToState()) {
    case 0:
      //drive 0
      break;
    case 1:
      //drive 1
      break;
    case 2:
      //drive 2
      break;
    case 3:
      //drive 3
      break;
    case 4:
      //drive 4
      break;
    case 5:
      //drive 5
      break;

  }
}
