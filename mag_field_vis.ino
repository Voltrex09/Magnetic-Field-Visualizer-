#include <LedControl.h>


LedControl lc = LedControl(11, 13, 10, 1);


const int hallPin = A0;
const int potPin  = A1;


int baseline = 512;

void setup() {
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);     
  lc.clearDisplay(0);

  
  delay(500);

  
  baseline = analogRead(hallPin);
}

void loop() {
  int hallValue = analogRead(hallPin);
  int sensitivity = analogRead(potPin);

  
  int delta = hallValue - baseline;

  
  int maxRange = map(sensitivity, 0, 1023, 20, 200);

  
  int level = map(abs(delta), 0, maxRange, 0, 4);
  level = constrain(level, 0, 4);

  
  lc.clearDisplay(0);

  
  if (delta > 0) {
    
    for (int i = 0; i < level; i++) {
      lc.setRow(0, 3 - i, B00111000);
    }
  } else if (delta < 0) {
    
    for (int i = 0; i < level; i++) {
      lc.setRow(0, 4 + i, B00111000);
    }
  }

  delay(60);  
}
