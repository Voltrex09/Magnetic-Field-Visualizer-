#include <LedControl.h>


#define DIN 11
#define CLK 13
#define CS  10
#define HALL_PIN A0
#define POT_PIN  A1

LedControl lc = LedControl(DIN, CLK, CS, 1);

int centerValue = 512;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  
  long sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += analogRead(HALL_PIN);
    delay(5);
  }
  centerValue = sum / 100;
}
void loop() {
  int hallRaw = analogRead(HALL_PIN);
  int diff = hallRaw - centerValue;
  int potValue = analogRead(POT_PIN);
  int sensitivity = map(potValue, 0, 1023, 10, 200);
  lc.clearDisplay(0);
  lc.setLed(0, 4, 4, true);
  int strength = constrain(abs(diff), 0, sensitivity);
  int height = map(strength, 0, sensitivity, 0, 8);

  int column;
  if (diff > 0) {
    column = 5;   
  } else {
    column = 2;   
  }

  for (int row = 7; row >= 8 - height; row--) {
    lc.setLed(0, row, column, true);
  }

  delay(40);
}
