#ifndef MENUVISUALS
#define MENUVISUALS
#include <Arduino.h>
#include "menuVisuals.h"

typedef struct{
    int optionCount=0;
    const char* title;
    String options[30];
}MENU;

typedef struct{
    MENU* menus[5];
}MENULIST;

void addOption(MENU* menu, String name);
int calcOption(int row, int option, int optionCount);
void menu(int option, int optionCount, String options[], const char* titleChr);
void confirmOverrideMenu(int, String);
void confirmWipeEeproomMenu(int);
void cancelOverrideMenu(int);
void visualMenu(int option);
void turnOffDisplay();
#endif // MENUVISUALS
