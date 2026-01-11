#include <LedControl.h>

#define DIN 11
#define CLK 13
#define CS  10
#define HALL_PIN A0
#define POT_PIN  A1
#define BUZZER   6
LedControl lc = LedControl(DIN, CLK, CS, 1);
int centerValue = 512;
int lastHeight = 0;
bool fieldDetected = false;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  long sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += analogRead(HALL_PIN);
    delay(5);
  }
  centerValue = sum / 100;
}

void beep(int durationMs) {
  digitalWrite(BUZZER, HIGH);
  delay(durationMs);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  int hallRaw = analogRead(HALL_PIN);
  int diff = hallRaw - centerValue;
  int potValue = analogRead(POT_PIN);
  int sensitivity = map(potValue, 0, 1023, 10, 200);

  lc.clearDisplay(0);

  int strength = constrain(abs(diff), 0, sensitivity);
  int height = map(strength, 0, sensitivity, 0, 8);
  int column = (diff > 0) ? 5 : 2;

  if (strength > 2 && !fieldDetected) {
    beep(120);
    fieldDetected = true;
  }

  if (strength <= 2) {
    fieldDetected = false;
    lastHeight = 0;
  }

  if (height > lastHeight) {
    beep(60);
  }

  lastHeight = height;

  for (int row = 7; row >= 8 - height; row--) {
    lc.setLed(0, row, column, true);
  }

  delay(40);
}
