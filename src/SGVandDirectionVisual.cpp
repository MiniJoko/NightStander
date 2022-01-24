#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ArduinoJson.h>

#include "GFX.h"
#include "nightscoutData.h"
#include "deviceTime.h"
#include "state.h"
#include "graphVisual.h"

unsigned long getDataTimer2 = 0;
unsigned long updateDisplayTimer2 = 0;

unsigned long getDataTimer3 = 0;
unsigned long updateDisplayTimer3 = 0;

void drawSGVandUnit(int x, int y, uint16_t color){
  double SGV = getSGV();
  if(SGV==-1){
    displayText(x , y, "...", 2, color);
    displayText(x+23, y+20, "mmol/l", 1, color);
  }else{
    displayText(x , y, String(SGV,1), 2, color);
    displayText(x+23, y+20, "mmol/l", 1, color);
  }
}

void drawFrame(){
  DrawFastHLine(0,21,128,WHITE);
  DrawFastHLine(0,22,128,WHITE);
  DrawFastHLine(0,23,128,WHITE);
  DrawFastHLine(0,23,72,WHITE);
  DrawFastHLine(74,23,55,WHITE);
  DrawFastVLine(71,24,41,WHITE);
  DrawFastVLine(72,24,41,WHITE);
  DrawFastVLine(73,24,41,WHITE);
  DrawFastVLine(74,24,41,WHITE);
}

void displaySGVandDirection(){
  ClearDisplay();
  drawFrame();
  drawSGVandUnit(6, 34, WHITE);
  drawDirection(85, 28, 3, WHITE);
  drawTime(30, 3, 2, WHITE);
  drawWifi(95, 0, 1, WHITE);
  UpdateDisplay();
}

void visualizeSGVandDirection() {
  if(!getVisualInit()){
    storeData();
    displaySGVandDirection();
    setVisualInit(true);
  }
  if (updateTimer(300000, &getDataTimer2)){
    storeData();
  }
  if(updateTimer(60000, &updateDisplayTimer2)) { //60 000 ms = 1 min
    displaySGVandDirection();
  }
}

//3rd value screen

void drawFrame2(){
  DrawFastHLine(0,9,128,WHITE);
  // DrawFastHLine(0,10,128,WHITE);
  // DrawFastHLine(0,11,128,WHITE);
  // DrawFastHLine(0,12,128,WHITE);
}

void drawValueText(){
  double IOB = getIOB();
  String IOBstr = String(IOB)+"U";
  double COB = getCOB();
  String COBstr = String(COB,1)+"g";
  String SAGEstr = getSAGE();
  String CAGEstr = getCAGE();
  drawInfoBar(0,0);

  fillRoundRect(15,15,105,11,2,WHITE);
  fillRoundRect(72,16,47,9,2,BLACK);
  fillRoundRect(15,27,105,11,2,WHITE);
  fillRoundRect(72,28,47,9,2,BLACK);
  fillRoundRect(15,39,105,11,2,WHITE);
  fillRoundRect(72,40,47,9,2,BLACK);
  fillRoundRect(15,51,105,11,2,WHITE);
  fillRoundRect(72,52,47,9,2,BLACK);

  displayText(17, 17, "IOB ", 1, BLACK);
  displayText(77, 17, IOBstr, 1, WHITE);
  displayText(17, 29, "COB ", 1, BLACK);
  displayText(77, 29, COBstr, 1, WHITE);
  displayText(17, 41, "SAGE ", 1, BLACK);
  displayText(77, 41, SAGEstr, 1, WHITE);
  displayText(17, 53, "CAGE ", 1, BLACK);
  displayText(77, 53, CAGEstr, 1, WHITE);
}

void displayValues(){
  ClearDisplay();
  drawFrame2();
  drawTime(93, 0, 1, WHITE);
  drawValueText();
  UpdateDisplay();
}

void visualizeValues() {
  if(!getValuesInit()){
    storeValues();
    displayValues();
    setValuesInit(true);
  }
  if (updateTimer(300000, &getDataTimer3)){
    storeValues();
  }
  if(updateTimer(60000, &updateDisplayTimer3)) { //60 000 ms = 1 min
    displayValues();
  }
}
