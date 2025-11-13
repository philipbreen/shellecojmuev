void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
}

void loop() {
  int a = digitalRead(A0);
  int b = digitalRead(A1);
  int c = digitalRead(A2);

  Serial.print("A0: "); Serial.print(a);
  Serial.print("  A1: "); Serial.print(b);
  Serial.print("  A2: "); Serial.println(c);
  delay(200);
}
