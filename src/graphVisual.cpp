#define ARDUINOJSON_USE_DOUBLE 1
#define ARDUINOJSON_USE_LONG_LONG 1

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>
#include <Timestamps.h>
#include <ArduinoJson.h> //Library to handle JSON-messages
#include <WiFi.h>

#include "bitmaps.h"
#include "graphVisual.h"
#include "GFX.h"
#include "nightscoutData.h"
#include "deviceTime.h"
#include "state.h"

unsigned long getDataTimer1 = 0;
unsigned long updateDisplayTimer1 = 0;

Timestamps ts1(3600);

void setOrigoValue(int* origoMin, int* origoHour) {
  int currentMinute = minute();
  *origoMin = 5 * ((currentMinute / 5) + 1);
  *origoHour = hour();
  if (*origoMin == 60) {
    *origoMin = 0;
    *origoHour=*origoHour+1;
  }
}

int hourCalc(int hr, int hrsToRemove) {
  for (int n = 0; n < hrsToRemove; n++) {
    hr--;
    if (hr == -1) {
      hr = 23;
    }
  }
  return hr;
}

String origoTimeLabelParser(int origoMin, int origoHour){
  String origoTimeLabel;
  if (origoMin<10){
    if(origoHour<10){
      origoTimeLabel = "0" + String(origoHour) + ":0" + String(origoMin);
    }else{
      origoTimeLabel = String(origoHour) + ":0" + String(origoMin);
    }
  }else{
    if(origoHour<10){
      origoTimeLabel = "0" + String(origoHour) + ":" + String(origoMin);
    }else{
      origoTimeLabel = String(origoHour) + ":" + String(origoMin);
    }
  }
  return origoTimeLabel;
}

void drawGraph(bool dataOn) {

  StaticJsonDocument<2048> graphData = getGraphData();

  int visual_width = 128;
  int visual_height = 64;

  int xOrigo = visual_width - 21;
  int yOrigo = visual_height - 12;

  int xAxisLength = visual_width - 20;
  int yAxisLength = visual_height - 11;

  int xUnitLength = 36;
  int yUnitLength = 12;

  int yUnitValue = (getMaxSGV()+5)/4;

  int xAxisSeparators = xAxisLength / xUnitLength;
  int yAxisSeparators = yAxisLength / yUnitLength;

  int origoMin;
  int origoHour;

  setOrigoValue(&origoMin, &origoHour);

  int timeLabel;
  String glucoseLabel;

  int xSeparator;
  int ySeparator;

  int xAxisSeparatorLength = 4;
  int yAxisSeparatorLength = 4;

  int xAxisSeparatorAdjustment = (origoMin / 5) * (xUnitLength / 12);

  //draw xAxis
  DrawFastHLine(0, yOrigo, xAxisLength, WHITE);
  String origoTimeLabel = origoTimeLabelParser(origoMin, origoHour);
  fillRoundRect(xOrigo-16, yOrigo+2, 31, 9, 2, WHITE);
  displayText(xOrigo-15, yOrigo+3, origoTimeLabel, 1, BLACK);
  for (int i = 0; i < xAxisSeparators; i++) {
    timeLabel = hourCalc(origoHour, i);
    xSeparator = xOrigo - xAxisSeparatorAdjustment - i * xUnitLength;
    DrawFastVLine(xSeparator, yOrigo - xAxisSeparatorLength, xAxisSeparatorLength, WHITE);
    if(xSeparator>5 && xSeparator<xOrigo-22){
      if (timeLabel < 10) {
        displayText(xSeparator - 3, yOrigo + 3, String(timeLabel), 1, WHITE);
      } else if (timeLabel >= 10) {
        displayText(xSeparator - 6, yOrigo + 3, String(timeLabel), 1, WHITE);
      }
    }
  }

  //draw yAxis
  DrawFastVLine(xOrigo, 0, yAxisLength, WHITE);
  for (int j = 1; j <= yAxisSeparators; j++) {
    glucoseLabel = String(yUnitValue * j);
    ySeparator = yOrigo - j * yUnitLength;
    DrawFastHLine(xOrigo-yAxisSeparatorLength, ySeparator, yAxisSeparatorLength, WHITE);
    if(ySeparator > 3){
    displayText(xOrigo + 3, ySeparator - 3, glucoseLabel, 1, WHITE);
    }
  }

  //draw data
  if(dataOn){
    long long origoTimestamp = ts1.getTimestampUNIX(year(), month(), day(), origoHour, origoMin, 0);

    for (JsonObject item : graphData.as<JsonArray>()) {

      long long rawTimeStamp = item["date"]; // timestamp in milliseconds
      float dataTimeStamp = (float(rawTimeStamp) / 1000) + 3600; //convert rawdate to seconds and add 1 hour for timezone adjustment

      // Serial.print("origoTimestamp: ");
      // Serial.println(origoTimestamp);

      // Serial.print("dataTimeStamp: ");
      // Serial.println(dataTimeStamp);

      int sgvAmerican = item["sgv"]; // glucose value in mg/dl
      float sgv = float(sgvAmerican) / 18; //convert to mmol/l. SGV = sensor glucose value

      float posXRatio = (float(origoTimestamp) - dataTimeStamp) / 10800;
      float posXfloat = float(xOrigo) - (float(xAxisLength)*posXRatio);
      int posX = round(posXfloat);

      // Serial.print("posXRatio: ");
      // Serial.println(posXRatio);

      float yAxisLengthValue = (float(yAxisLength)/float(yUnitLength))*float(yUnitValue);
      float posYRatio = sgv / float(yAxisLengthValue);
      float posYfloat = yOrigo - (float(yAxisLength)*posYRatio);
      int posY = round(posYfloat);

      //drawPixel(posX,posY,WHITE);
      drawPoint(posX, posY, WHITE);
    }
  }
}

void drawSGVwithUnit(int x, int y, uint16_t color){
  double SGV = getSGV();
  if(SGV==-1){
    String displayedStr = "... mmol/l";
    displayText(x , y, displayedStr, 1, color);
  }else{
    String displayedStr = String(SGV,1) + " mmol/l";
    displayText(x , y, displayedStr, 1, color);
  }
}

void drawInfoBar(int x, int y){
     fillRoundRect(0,0,95,11,2,WHITE);
     drawSGVwithUnit(x+2, y+2,BLACK);
     drawDirection(x+74, y+2, 1, BLACK);
     drawWifi(77,2, 0, BLACK);
}

void displayGraph(){
  ClearDisplay();
  drawGraph(1);
  drawInfoBar(0,0);
  UpdateDisplay();
}

void displayGraphNoData(){
  ClearDisplay();
  drawGraph(0);
  UpdateDisplay();
}

void visualizeGraph() {
  if(!getGraphInit()){
    displayGraphNoData();
    storeGraphData();
    storeData();
    displayGraph();
    setGraphInit(true);
  }

  if (updateTimer(300000, &getDataTimer1)) { //300 000 ms = 5 min
    storeGraphData();
    storeData();
  }
  if(updateTimer(10000, &updateDisplayTimer1)){
    displayGraph();
  }
}
