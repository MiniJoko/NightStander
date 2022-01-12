#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ArduinoJson.h>

#include "GFX.h"
#include "nightscoutData.h"
#include "deviceTime.h"
#include "state.h"

unsigned long getDataTimer2 = 0;
unsigned long updateDisplayTimer2 = 0;

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
