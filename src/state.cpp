#include "Arduino.h"
#include "state.h"
#include "config.h"
#include "GFX.h"
#include "buttons.h"
#include "menuVisuals.h"
#include "overrides.h"
#include "SGVandDirectionVisual.h"
#include "graphVisual.h"
#include "WiFiManager.h"

bool graphInit = false;
bool visualInit = false;

bool getGraphInit(){
    return graphInit;
}

void setGraphInit(bool boolean){
    graphInit = boolean;
}

bool getVisualInit(){
    return visualInit;
}

void setVisualInit(bool boolean){
    visualInit = boolean;
}

void setState(STATE* state, MENULIST* menuList){
    if(state->OnOff==1){
        if(up()){
            if(state->menuType == 0){
                if(state->menu==0 && state->option==0){graphInit=false;}
                else if(state->menu==0 && state->option==1){visualInit=false;}
                state->option--;
                if(state->option == -1){state->option = menuList->menus[state->menu]->optionCount-1;}
            }else if(state->menuType == 1){
                if(state->confirm == 1){state->confirm=0;}
                else if(state->confirm == 0){state->confirm=1;}
            }
        }
        if(down()){
            if(state->menuType == 0){
                if(state->menu==0 && state->option==0){graphInit=false;}
                else if(state->menu==0 && state->option==1){visualInit=false;}
                state->option++;
                if(state->option == menuList->menus[state->menu]->optionCount){state->option = 0;}
            }else if(state->menuType == 1){
                if(state->confirm == 1){state->confirm=0;}
                else if(state->confirm == 0){state->confirm=1;}
            }
        }
        if(confirm()){
            if(state->menuType == 0){
                switch(state->menu){
                    case VISUAL_MENU:
                        if(state->menu==0 && state->option==0){graphInit=false;}
                        if(state->menu==0 && state->option==1){visualInit=false;}
                        state->menu=MAIN_MENU;
                        state->option=0;
                        break;
                    case MAIN_MENU:
                        switch(state->option){
                            case BACK:
                                state->menu=VISUAL_MENU;
                                state->option=0;
                                break;
                            case OVERRIDES2:
                                state->menu=OVERRIDES_MENU;
                                state->option=0;
                                break;
                            case DISONNECT:
                                state->menuType=1;
                                state->confirmMenu=2;
                                break;
                            case TURNOFF:
                                state->OnOff=0;
                                break;
                        }
                        break;
                    case OVERRIDES_MENU:
                        if(state->option==BACK){
                            state->menu=MAIN_MENU;state->option=0;
                        }
                        else if(state->option==1){
                            state->menuType=1;
                            state->confirmMenu=1;
                        }
                        else{state->menuType=1;
                            state->confirmMenu=0;
                        }
                        break;
                }
            }else if(state->menuType == 1){
                switch(state->confirmMenu){
                    case CONFIRM_OVERRIDE_MENU:
                        if(state->confirm==0){state->menuType = 0;}
                        else if(state->confirm==1){override(state->option-2);state->menuType = 0; state->confirm=0;}
                        break;
                    case CANCEL_OVERRIDE_MENU:
                        if(state->confirm==0){state->menuType = 0;}
                        else if(state->confirm==1){cancelOverride();state->menuType = 0; state->confirm=0;}
                        break;
                    case CONFIRM_WIPE_EEPROM_MENU:
                        if(state->confirm==0){state->menuType = 0;}
                        else if(state->confirm==1){wipeEEPROM();state->menuType = 0; state->confirm=0;}
                        break;
                }
            }
        }
    }else if(state->OnOff==0){
        if(confirm()){state->OnOff=1; state->option=0;}
    }
    
    // Serial.print("menu: ");
    // Serial.print(state->menu);
    // Serial.print(" option: ");
    // Serial.print(state->option);
    // Serial.print(" menuType: ");
    // Serial.print(state->menuType);
    // Serial.print(" confirmMenu: ");
    // Serial.print(state->confirmMenu);
    // Serial.print(" confirm: ");
    // Serial.print(state->confirm);
    // Serial.print(" OnOff: ");
    // Serial.println(state->OnOff);
}

//wipeEEPROM();
//cancelOverride();
//else{override(state->option-2);}

void StateHandler(STATE* state, MENULIST* menuList){
    if(state->OnOff==0){turnOffDisplay();}
    else{
        switch(state->menuType){
            case 0:
                switch(state->menu){
                    case VISUAL_MENU:
                        visualMenu(state->option);
                        break;
                    case MAIN_MENU:
                    case OVERRIDES_MENU:
                        menu(state->option, menuList->menus[state->menu]->optionCount, menuList->menus[state->menu]->options, menuList->menus[state->menu]->title);
                        break;
                }
                break;
            case 1:
                switch(state->confirmMenu){
                    case CONFIRM_OVERRIDE_MENU:
                        confirmOverrideMenu(state->confirm, menuList->menus[state->menu]->options[state->option]);
                        break;
                    case CANCEL_OVERRIDE_MENU:
                        cancelOverrideMenu(state->confirm);
                        break;
                    case CONFIRM_WIPE_EEPROM_MENU:
                        confirmWipeEeproomMenu(state->confirm);
                        break;
                }
                break;
        }
    }
}
