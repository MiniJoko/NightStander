#include "menuVisuals.h"
#include "GFX.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "graphVisual.h"
#include "SGVandDirectionVisual.h"
#include "state.h"

void addOption(MENU* menu, String name){
    menu->options[menu->optionCount]=name;
    menu->optionCount++;
}

int calcOption(int row, int option, int optionCount){
    int toDisplay = option-1+row;
    if(row==0 && option==0 ){toDisplay = optionCount-1;}
    if(row==2 && option == optionCount-1){toDisplay = 0;}
    return toDisplay;
}

void menu(int option, int optionCount, String options[], const char* titleChr){
    ClearDisplay();
    
    //title
    String title = titleChr;
    int xTitle = (SCREEN_WIDTH/2)-(title.length())*6/2;
    displayText(xTitle, 0, title, TEXT_SIZE, WHITE);
    
    //options
    int color;
    int row;
    int xText;
    int yText;
    int rowHeight = 15;
    for(row=0; row<3; row++){
    xText=12;
    yText=15+rowHeight*row;
    if(row==1){color = 0;fillRoundRect(xText-2, yText-1, 108, 10, 2, WHITE);}else{color=1;}
    displayText(xText, yText, options[calcOption(row, option, optionCount)], TEXT_SIZE, color);
    }

    //Arrows
    DrawFastVLine(4, 15, 37, WHITE);
    DrawFastVLine(3, 15, 37, WHITE);
    drawArrowUp(3, 7, WHITE);
    drawArrowDown(3, 54, WHITE);
    

    //confirmWindow
    
    UpdateDisplay();
}

void confirmOverrideMenu(int confirm, String optionChr){
    ClearDisplay();
    int xMessage = (SCREEN_WIDTH/2)-(optionChr.length())*6/2;
    displayText(xMessage, 0, optionChr, TEXT_SIZE, WHITE);
    displayText(12, 15, "activate override?", TEXT_SIZE, WHITE);
    if(confirm==0){
        fillRoundRect(57, 43, 19, 9, 2, WHITE);
        displayText(58, 31, "yes", TEXT_SIZE, WHITE);
        displayText(58, 43, "no", TEXT_SIZE, BLACK);
    } else if(confirm==1){
        fillRoundRect(57, 31, 19, 9, 2, WHITE);
        displayText(58, 31, "yes", TEXT_SIZE, BLACK);
        displayText(58, 43, "no", TEXT_SIZE, WHITE);
    }
    UpdateDisplay();
}

void confirmWipeEeproomMenu(int confirm){
    ClearDisplay();
    displayText(14, 7, "Reset device to", TEXT_SIZE, WHITE);
    displayText(13, 16, "factory default?", TEXT_SIZE, WHITE);
    if(confirm==0){
        fillRoundRect(57, 43, 19, 9, 2, WHITE);
        displayText(58, 31, "yes", TEXT_SIZE, WHITE);
        displayText(58, 43, "no", TEXT_SIZE, BLACK);
    } else if(confirm==1){
        fillRoundRect(57, 31, 19, 9, 2, WHITE);
        displayText(58, 31, "yes", TEXT_SIZE, BLACK);
        displayText(58, 43, "no", TEXT_SIZE, WHITE);
    }
    UpdateDisplay();
}

void cancelOverrideMenu(int confirm){
    ClearDisplay();
    displayText(15, 7, "Cancel override?", TEXT_SIZE, WHITE);

    if(confirm==0){
        fillRoundRect(57, 43, 19, 9, 2, WHITE);
        displayText(58, 31, "yes", TEXT_SIZE, WHITE);
        displayText(58, 43, "no", TEXT_SIZE, BLACK);
    } else if(confirm==1){
        fillRoundRect(57, 31, 19, 9, 2, WHITE);
        displayText(58, 31, "yes", TEXT_SIZE, BLACK);
        displayText(58, 43, "no", TEXT_SIZE, WHITE);
    }
    UpdateDisplay();
}

void visualMenu(int option){
    if (option == 1){
        visualizeGraph();
    }else if (option==0){
        visualizeSGVandDirection();
    }
}

void turnOffDisplay(){
    ClearDisplay();
    UpdateDisplay();
}

