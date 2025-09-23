#include <PWM.h>

int pin = 9;
int32_t frequency = 10000;

void setup() {
InitTimersSafe ();
SetPinFrequencySafe (pin, frequency);

}

void loop() {
pwmWrite (pin, 255);
}
