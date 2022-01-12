#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "menuVisuals.h"



enum MENUS{VISUAL_MENU, MAIN_MENU, OVERRIDES_MENU};
enum CONFIRM_MENUS{CONFIRM_OVERRIDE_MENU, CANCEL_OVERRIDE_MENU, CONFIRM_WIPE_EEPROM_MENU};
enum VISUAL_MENU_OPTIONS{VALUE,GRAPH};
enum MAIN_MENU_OPTIONS{BACK, OVERRIDES2, DISONNECT, TURNOFF};

typedef struct{
    int menu;
    int option;
    int menuType;
    int confirmMenu;
    int confirm;
    int OnOff;
} STATE;

bool getGraphInit();
void setGraphInit(bool boolean);
bool getVisualInit();
void setVisualInit(bool boolean);

void setState(STATE*, MENULIST*);
void StateHandler(STATE*, MENULIST*);



#endif
