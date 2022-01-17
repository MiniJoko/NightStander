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

int state1;
int option;
int state2;
int OnOff;

bool graphInit = false;
bool visualInit = false;
bool valuesInit = false;

bool getValuesInit(){
    return valuesInit;
}

void setValuesInit(bool boolean){
    valuesInit = boolean;
}

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
    switch(state->OnOff){
        case ON:
            if(up()){
                switch(state->menu){
                    case VISUAL_MENU:
                        if(state->option==GRAPH_SCREEN){setGraphInit(false);}
                        else if(state->option==VALUE_SCREEN){setVisualInit(false);}
                        else if(state->option==VALUE_SCREEN_2){setValuesInit(false);}
                        state->option--;
                        if(state->option == -1){state->option = menuList->menus[0]->optionCount-1;} //get visualmenu optioncount
                        //Serial.print("up: VISUAL_MENU "); checkStates(state);
                        break;
                    case MAIN_MENU: case OVERRIDE_MENU:
                        state->option--;
                        if(state->option == -1){state->option = menuList->menus[state->menu]->optionCount-1;} //get current menu optioncount
                        //Serial.print("up: MAIN_MENU/OVERRIDE_MENU"); checkStates(state);
                        break;
                    case CONFIRM_WIPE_MENU: case CONFIRM_OVERRIDE_MENU: case CANCEL_OVERRIDE_MENU:
                        if(state->confirm == YES){state->confirm=0;}
                        else if(state->confirm == NO){state->confirm=1;}
                        //Serial.print("up: CONFIRM MENU"); checkStates(state);
                        break;
                }

            }
            else if(down()){
                switch(state->menu){
                    case VISUAL_MENU:
                        if(state->option==GRAPH_SCREEN){setGraphInit(false);}
                        else if(state->option==VALUE_SCREEN){setVisualInit(false);}
                        else if(state->option==VALUE_SCREEN_2){setValuesInit(false);}
                        state->option++;
                        if(state->option == menuList->menus[0]->optionCount){state->option = 0;}
                        //Serial.print("down: VISUAL_MENU"); checkStates(state);
                        break;
                    case MAIN_MENU: case OVERRIDE_MENU:
                        state->option++;
                        if(state->option == menuList->menus[state->menu]->optionCount){state->option = 0;}
                        //Serial.print("down: MAIN_MENU/OVERRIDE_MENU"); checkStates(state);
                        break;
                    case CONFIRM_WIPE_MENU: case CONFIRM_OVERRIDE_MENU: case CANCEL_OVERRIDE_MENU:
                        if(state->confirm == YES){state->confirm=NO;}
                        else if(state->confirm == NO){state->confirm=YES;}
                        //Serial.print("down: CONFIRM_MENU"); checkStates(state);
                        break;
                }
            }
            else if(confirm()){
                switch(state->menu){
                    case VISUAL_MENU:
                        setVisualInit(false);
                        setGraphInit(false);
                        setValuesInit(false);
                        state->menu=MAIN_MENU;
                        state->option=BACK;
                        //Serial.print("confirm: VISUAL_MENU"); checkStates(state);
                        break;
                    case MAIN_MENU:
                        switch(state->option){
                            case BACK:
                                state->menu=VISUAL_MENU;
                                //Serial.print("confirm: MAINMENU-BACK"); checkStates(state);
                                break;
                            case OVERRIDES_OPTION:
                                state->menu=OVERRIDE_MENU;
                                state->option=BACK;
                                //Serial.print("confirm: MAINMENU-OVERRIDES_OPTION"); checkStates(state);
                                break;
                            case RESET_DEVICE_OPTION:
                                state->menu=CONFIRM_WIPE_MENU;
                                state->option=BACK;
                                //Serial.print("confirm: MAIN_MENU-RESET_DEVICE_OPTION"); checkStates(state);
                                break;
                            case TURN_OFF_DISPLAY_OPTION:
                                state->OnOff=OFF;
                                state->option=BACK;
                                //Serial.print("confirm: MAIN_MENU-TURNOFF_DISPLAY_OPTION"); checkStates(state);
                                break;
                        }
                        break;
                    case OVERRIDE_MENU:
                        switch(state->option){
                            case BACK:
                                state->menu=MAIN_MENU;
                                //Serial.print("confirm: OVERRIDE_MENU-BACK"); checkStates(state);
                                break;
                            case CANCEL_OVERRIDE_OPTION:
                                state->menu=CANCEL_OVERRIDE_MENU;
                                //Serial.print("confirm: OVERRIDE_MENU-CANCEL_OVERRIDE_OPTION"); checkStates(state);
                                break;
                            default: //activate override options
                                state->menu=CONFIRM_OVERRIDE_MENU;
                                //Serial.print("confirm: OVERRIDE_MENU-OVERRIDE"); checkStates(state);
                                break;
                        }
                        break;
                    case CONFIRM_WIPE_MENU:
                        if(state->confirm==NO){state->menu = MAIN_MENU;}
                        else if(state->confirm==YES){
                            wipeEEPROM();
                            }
                        //Serial.print("confirm: CONFIRM_WIPE_MENU"); checkStates(state);
                        break;
                    case CONFIRM_OVERRIDE_MENU:
                        if(state->confirm==NO){state->menu = OVERRIDE_MENU;}
                        else if(state->confirm==YES){
                            override(state->option-2);
                            state->menu = OVERRIDE_MENU;
                            state->confirm=NO;}
                        //Serial.print("confirm: CONFIRM_OVERRIDE_MENU"); checkStates(state);
                        break;
                    case CANCEL_OVERRIDE_MENU:
                        if(state->confirm==NO){state->menu = OVERRIDE_MENU;}
                        else if(state->confirm==YES){
                            cancelOverride();
                            state->menu = OVERRIDE_MENU;
                            state->confirm=NO;}
                        //Serial.print("confirm: CANCEL_OVERRIDE_MENU"); checkStates(state);
                        break;
                }
            }
            break;
        case OFF:
            if(confirm()){state->OnOff=ON; state->option=BACK;}
            //Serial.print("confirm: OFF"); checkStates(state);
            break;
    }
    //checkStates(state);
}

void StateHandler(STATE* state, MENULIST* menuList){
    switch(state->OnOff){
        case ON:
            switch(state->menu){
                case VISUAL_MENU:
                    visualMenu(state->option);
                    break;
                case MAIN_MENU: case OVERRIDE_MENU:
                    menu(state->option, menuList->menus[state->menu]->optionCount, menuList->menus[state->menu]->options, menuList->menus[state->menu]->title);
                    break;
                case CONFIRM_WIPE_MENU:
                    confirmWipeEeproomMenu(state->confirm);
                    break;
                case CONFIRM_OVERRIDE_MENU:
                    confirmOverrideMenu(state->confirm, menuList->menus[2]->options[state->option]);
                    break;
                case CANCEL_OVERRIDE_MENU:
                    cancelOverrideMenu(state->confirm);
                    break;
            }
            break;
        case OFF:
            turnOffDisplay();
            break;
    }
}

void checkStates(STATE* state){
    if(state1!=state->menu||option!=state->option||state2!=state->confirm||OnOff!=state->OnOff){
        state1 = state->menu;
        option = state->option;
        state2 = state->confirm;
        OnOff = state->OnOff;
        Serial.print(" menu: ");
        Serial.print(state->menu);
        Serial.print(" option: ");
        Serial.print(state->option);
        Serial.print(" confirm: ");
        Serial.print(state->confirm);
        Serial.print(" OnOff: ");
        Serial.print(state->OnOff);
        Serial.print(" GraphInit: ");
        Serial.print(getGraphInit());
        Serial.print(" VisualInit: ");
        Serial.println(getVisualInit());
    }
}
