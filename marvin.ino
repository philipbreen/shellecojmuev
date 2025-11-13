const int hallAPin = A0; // Blue
const int hallBPin = A1; // Green
const int hallCPin = A2; // White

void setup() {
  Serial.begin(9600);

  // External pull-ups already exist → use plain INPUT
  pinMode(hallAPin, INPUT);
  pinMode(hallBPin, INPUT);
  pinMode(hallCPin, INPUT);
}

void loop() {
  // Read the raw voltages
  int aRaw = analogRead(hallAPin);
  int bRaw = analogRead(hallBPin);
  int cRaw = analogRead(hallCPin);

  // Convert analog values (0–1023) into digital 0/1 with a threshold
  // If you see only 1s, lower threshold to ~300
  int threshold = 512;

  int hallA = (aRaw > threshold) ? 1 : 0;
  int hallB = (bRaw > threshold) ? 1 : 0;
  int hallC = (cRaw > threshold) ? 1 : 0;

  Serial.print("A: "); Serial.print(hallA);
  Serial.print("  B: "); Serial.print(hallB);
  Serial.print("  C: "); Serial.print(hallC);
  Serial.print("   (raw: ");
  Serial.print(aRaw); Serial.print(",");
  Serial.print(bRaw); Serial.print(",");
  Serial.print(cRaw); Serial.println(")");
  
  delay(100);
}
