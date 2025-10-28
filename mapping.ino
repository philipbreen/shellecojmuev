int greenPin = A0;
int bluePin  = A1;
int whitePin = A2;

int greenValue;
int blueValue;
int whiteValue;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  greenValue = analogRead(greenPin);
  blueValue  = analogRead(bluePin);
  whiteValue = analogRead(whitePin);

  Serial.print("Green: ");
  Serial.print(greenValue);
  Serial.print("  Blue: ");
  Serial.print(blueValue);
  Serial.print("  White: ");
  Serial.println(whiteValue);

  delay(100); 
}
