#include "Arduino.h"
#include "config.h"

unsigned long lastInterrupt1 = 0;
unsigned long lastInterrupt2 = 0;
unsigned long lastInterrupt3 = 0;
bool isInterrupted1 = false;
bool isInterrupted2 = false;
bool isInterrupted3 = false;

void IRAM_ATTR HandleInterrupt1() {
  detachInterrupt(INTERRUPT1);
  if (!isInterrupted1) {
    isInterrupted1 = true;
    lastInterrupt1 = millis();
  }
  attachInterrupt(digitalPinToInterrupt(INTERRUPT1), HandleInterrupt1, RISING);
}

void IRAM_ATTR HandleInterrupt2() {
  detachInterrupt(INTERRUPT2);
  if (!isInterrupted2) {
    isInterrupted2 = true;
    lastInterrupt2 = millis();
  }
  attachInterrupt(digitalPinToInterrupt(INTERRUPT2), HandleInterrupt2, RISING);
}

void IRAM_ATTR HandleInterrupt3() {
  detachInterrupt(INTERRUPT3);
  if (!isInterrupted3) {
    isInterrupted3 = true;
    lastInterrupt3 = millis();
  }
  attachInterrupt(digitalPinToInterrupt(INTERRUPT3), HandleInterrupt3, RISING);
}


bool up() {
    if (isInterrupted1 && millis() - lastInterrupt1 > DEBOUNCE) {
      isInterrupted1 = false;
      return true;
    }
  return false;
}

bool down() {
    if (isInterrupted2 && millis() - lastInterrupt2 > DEBOUNCE) {
      isInterrupted2 = false;
      return true;
    }
  return false;
}

bool confirm() {
    if (isInterrupted3 && millis() - lastInterrupt3 > DEBOUNCE) {
      isInterrupted3 = false;
      return true;
    }
  return false;
}


void testButtons(){
    if(up()){Serial.println("up");}
    if(down()){Serial.println("down");}
    if(confirm()){Serial.println("confirm");}
}
