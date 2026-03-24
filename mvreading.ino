#define SIGNAL_PIN A0

const int oversamples = 4096;
float vref = 3.3;

const float MAX_AMPS = 15.0;
const unsigned long UNSAFE_DURATION = 333; 

unsigned long overLimitStart = 0;
bool isOverLimit = false;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {

  long total = 0;

  for (int i = 0; i < oversamples; i++) {
    total += analogRead(SIGNAL_PIN);
  }

  float avg = total / (float)oversamples;

  float voltage = avg * vref / 4095.0;
  float mv = voltage * 1000.0 + 2;  // your offset
  float amps = mv; // 1 mV = 1 A

  unsigned long currentTime = millis();

  // Check if over limit
  if (amps > MAX_AMPS) {
    if (!isOverLimit) {
      overLimitStart = currentTime;
      isOverLimit = true;
    }

    // Check duration
    if (currentTime - overLimitStart >= UNSAFE_DURATION) {
      Serial.print("UNSAFE TRUE | Amps: ");
      Serial.println(amps, 0);
      return;
    }
  } else {
    isOverLimit = false;
  }

  // Safe case
  Serial.print("UNSAFE FALSE | Amps: ");
  Serial.println(amps, 0);

  delay(100);
}
