#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "menuVisuals.h"

enum MENUS{VISUAL_MENU, MAIN_MENU, OVERRIDE_MENU, CONFIRM_WIPE_MENU, CONFIRM_OVERRIDE_MENU, CANCEL_OVERRIDE_MENU};
enum VISUAL_MENU_OPTIONS{GRAPH_SCREEN, VALUE_SCREEN, VALUE_SCREEN_2};
enum MAIN_MENU_OPTIONS{OVERRIDES_OPTION=1, RESET_DEVICE_OPTION, TURN_OFF_DISPLAY_OPTION};
enum BACK{BACK};
enum OVERRIDE_MENU_OPTIONS{CANCEL_OVERRIDE_OPTION=1};
enum CONFIRM_MENU_OPTIONS{NO,YES};
enum DISPLAY_ON_OFF{OFF,ON};

typedef struct{
    int menu;
    int option;
    int confirm;
    int OnOff;
}STATE;

bool getValuesInit();
void setValuesInit(bool boolean);
bool getGraphInit();
void setGraphInit(bool boolean);
bool getVisualInit();
void setVisualInit(bool boolean);

void setState(STATE*, MENULIST*);
void StateHandler(STATE*, MENULIST*);
void checkStates(STATE*);



#endif // STATE