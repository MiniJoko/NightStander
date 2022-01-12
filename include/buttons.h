#ifndef BUTTONS
#define BUTTONS

#include <Arduino.h>

void IRAM_ATTR HandleInterrupt1();
void IRAM_ATTR HandleInterrupt2();
void IRAM_ATTR HandleInterrupt3();

bool up();
bool down();
bool confirm();

void testButtons();
#endif // BUTTONS
