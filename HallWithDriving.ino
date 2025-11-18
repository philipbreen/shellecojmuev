const int hallAPin = 5; // Blue
const int hallBPin = 6; // Green
const int hallCPin = 7; // White
int hallA, hallB, hallC;
const int threshold = 100;
const int SPEED= 100;
const int aLowPin;
const int bLowPin;
const int cLowPin;
const int aHighPin;
const int bHighPin;
const int cHighPin;

void setup() {
  Serial.begin(9600);
  pinMode(hallAPin, INPUT);
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);
}

void loop() {
  driveMotor();
  //delay(100);
}

byte hallToState() {
  int hallA = digitalRead(hallAPin);
  int hallB = digitalRead(hallBPin);
  int hallC = digitalRead(hallCPin);

  byte hallState = (hallA << 2) | (hallB<< 1) | hallC;

 return hallState;
}

void driveMotor() {
  byte state = hallToState();
/*
  Serial.print("A(Blue): "); Serial.print(hallA);
  Serial.print("  B(Green): "); Serial.print(hallB);
  Serial.print("  C(White): "); Serial.print(hallC);
  Serial.print("  -> Value: ");
  if (state == 0) Serial.println("INVALID");
  else Serial.println(state);
*/
  switch (state) {
    case 0b001:
      driveStates(SPEED, 0, 0, 0, 0, 1); 
      Serial.println("Driving from State 1");
      break;
    case 0b101:
      driveStates(SPEED, 0, 0, 0, 1, 0); 
      Serial.println("Driving from State 2");
      break;
    case 0b100:
      driveStates(0, 0, SPEED, 0, 1, 0); 
      Serial.println("Driving from State 3");
      break;
    case 0b110:
      driveStates(0, 0, SPEED, 1, 0, 0); 
      Serial.println("Driving from State 4");
      break;
    case 0b010:
      driveStates(0, SPEED, 0, 1, 0, 0); 
      Serial.println("Driving from State 5");
      break;
    case 0b011:
      driveStates(0, SPEED, 0, 0, 0, 1); 
      Serial.println("Driving from State 6");
      break;
    default:
      driveStates(0, 0, 0, 0, 0, 0); 
      Serial.println("NOT DRIVING - ERROR");
      break;
  }
}

void driveStates(uint8_t aHigh, uint8_t bHigh, uint8_t cHigh, uint8_t aLow, uint8_t bLow, uint8_t cLow){
  digitalWrite(aLowPin, aLow);
  digitalWrite(bLowPin, bLow);
  digitalWrite(cLowPin, cLow);

  analogWrite(aHighPin, aHigh);
  analogWrite(bHighPin, bHigh);
  analogWrite(cHighPin, cHigh);
}

