#define SIGNAL_PIN A0

float ref_voltage = 1.1;
const int samples = 5;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {

  long total = 0;

  for(int i = 0; i < samples; i++) {
    total += analogRead(SIGNAL_PIN);
  }

  float adc_value = total / (float)samples;

  float voltage = adc_value * ref_voltage / 1023.0;
  float voltage_mV = voltage * 1000;

  Serial.print("Voltage (mV): ");
  Serial.println(voltage_mV);

  delay(50);
}
