#ifndef OVERRIDES
#define OVERRIDES
#include <Arduino.h>
#include "menuVisuals.h"

typedef struct{
  String name;
  String symbol;
  String insulinPercent;
}OVERRIDE;

typedef struct{
  int size;
  OVERRIDE overrides[20];
}OVERRIDE_LIST;

void addOverrides(MENU* menu);
void cancelOverride();
void override(int);

#endif // OVERRIDES
