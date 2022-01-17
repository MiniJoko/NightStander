#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"
#include "GFX.h"
#include "WiFiManager.h"
#include "menuVisuals.h"
#include "state.h"
#include "graphVisual.h"
#include "SGVandDirectionVisual.h"
#include "deviceTime.h"
#include "buttons.h"
#include "nightscoutData.h"
#include "overrides.h"

void setup() {
  pinMode(INTERRUPT1, INPUT_PULLDOWN);
  pinMode(INTERRUPT2, INPUT_PULLDOWN);
  pinMode(INTERRUPT3, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT1), HandleInterrupt1, RISING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT2), HandleInterrupt2, RISING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT3), HandleInterrupt3, RISING);

  EEPROM.begin(512);

  Serial.begin(115200);

  GetWifi();
  delay(500);

  InitDisplay();
  initWifiCred();
  if(!initWIFI()){
    initWifiCred();
  };
  initArduinoTime();
  GetFromEEPROM();
  storeOverrides();
}

void loop() {

  MENU mainMenu;
  mainMenu.title="Main Menu";
  addOption(&mainMenu, "Back");
  addOption(&mainMenu, "Remote overrides");
  addOption(&mainMenu, "Reset Device");
  addOption(&mainMenu, "Turn off display");

  MENU Overrides;
  Overrides.title="Overrides";
  addOption(&Overrides, "Back");
  addOption(&Overrides, "Cancel Override");
  addOverrides(&Overrides);

  MENU visual;
  visual.optionCount=3;

  MENULIST menuList;
  menuList.menus[0]=&visual;
  menuList.menus[1]=&mainMenu;
  menuList.menus[2]=&Overrides;

  STATE state;
  state.menu=0;
  state.option=0;
  state.confirm=0;
  state.OnOff=1;

  while(true){
    setState(&state, &menuList);
    StateHandler(&state, &menuList);
  }

}
