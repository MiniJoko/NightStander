#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>
#include <EEPROM.h>
#include <TimeLib.h>
#include <ArduinoJson.h>

#include "GFX.h"
#include "config.h"
#include "bitmaps.h"
#include "WiFi.h"
#include "nightscoutData.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void InitDisplay(){
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  String text = "Hello World!";
  ClearDisplay();
  drawBitmap(0, 0, nightstander, 128, 64, WHITE);
  //displayText(30, 28, text, TEXT_SIZE, WHITE);
  UpdateDisplay();
}

void UpdateDisplay(){
  display.display();
}

void ClearDisplay(){
  display.clearDisplay();
}

void drawPixel(int x, int y, uint16_t color){
  display.drawPixel(x,y,color);
}

void DrawFastHLine(int16_t  x, int16_t  y, int16_t  length, uint16_t color){
  display.drawFastHLine(x, y, length, color);
}

void DrawFastVLine(int16_t x, int16_t y, int16_t length, uint16_t color){
  display.drawFastVLine(x, y, length, color);
}

void fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color){
display.fillRoundRect( x0,  y0,  w,  h,  radius,  color);
}

void drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color){
display.drawRoundRect( x0,  y0,  w,  h,  radius,  color);
}

void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color){
  display.drawBitmap( x,  y,  bitmap,  w,  h, color);
}

void drawPoint(int x, int y, uint16_t color){
  display.drawPixel(x, y, color);
  display.drawPixel(x + 1, y + 1, color);
  display.drawPixel(x - 1, y + 1, color);
  display.drawPixel(x - 1, y - 1, color);
  display.drawPixel(x + 1, y - 1, color);
  display.drawPixel(x + 1, y, color);
  display.drawPixel(x, y + 1, color);
  display.drawPixel(x - 1, y, color);
  display.drawPixel(x, y - 1, color);
}

void drawArrowUp(int x, int y, uint16_t color){
  DrawFastHLine(x,y,2,color);
  DrawFastHLine(x,y+1,2,color);
  DrawFastHLine(x-1,y+2,4,color);
  DrawFastHLine(x-1,y+3,4,color);
  DrawFastHLine(x-2,y+4,6,color);
  DrawFastHLine(x-2,y+5,6,color);

}

void drawArrowDown(int x, int y, uint16_t color){
  DrawFastHLine(x-2,y,6,color);
  DrawFastHLine(x-2,y+1,6,color);
  DrawFastHLine(x-1,y+2,4,color);
  DrawFastHLine(x-1,y+3,4,color);
  DrawFastHLine(x,y+4,2,color);
  DrawFastHLine(x,y+5,2,color);

}

void displayText(int x, int y, String text, int size, uint16_t color){
    display.setTextSize(size);
    display.setTextColor(color);
    display.setCursor(x, y);
    display.println(text);
}

void drawWifi(int x, int y, int size, uint16_t color){
  if(size==0){
    if(WiFi.status() != WL_CONNECTED){
      drawBitmap(x, y, notconnectedSmall, 16, 16, color);
    }
    else{
      if (WiFi.RSSI() > -50) {
        drawBitmap(x, y, connected3Small, 16, 16, color);
      }
      else if (WiFi.RSSI() > -80) {
        drawBitmap(x, y, connected2Small, 16, 16, color);
      }
      else {
        drawBitmap(x, y, connected1Small, 16, 16, color);
      }
    }
  }else if(size==1){
    if(WiFi.status() != WL_CONNECTED){
      drawBitmap(x, y, notconnected, 16, 16, color);
    }
    else{
      if (WiFi.RSSI() > -50) {
        drawBitmap(x, y, connected3, 16, 16, color);
      }
      else if (WiFi.RSSI() > -80) {
        drawBitmap(x, y, connected2, 16, 16, color);
      }
      else {
        drawBitmap(x, y, connected1, 16, 16, color);
      }
    }
  }
}

void drawSGV(int x, int y, int size, uint16_t color){
  double SGV = getSGV();
  displayText(x , y, String(SGV), size, color);
}

void drawDirection(int x, int y, int size, uint16_t color){
  String direction = getDirection();
  if(size==1){
    if(direction=="DoubleUp"){
      drawBitmap( x-4, y, arrow8x8_SingleUp, 8, 8, color);
      drawBitmap( x+4, y, arrow8x8_SingleUp, 8, 8, color);
    }
    else if(direction=="SingleUp"){
      drawBitmap( x, y, arrow8x8_SingleUp, 8, 8, color);
    }
    else if(direction=="FortyFiveUp"){
      drawBitmap( x, y, arrow8x8_FortyFiveUp, 8, 8, color);
    }
    else if(direction=="Flat"){
      drawBitmap( x, y, arrow8x8_flat, 8, 8, color);
    }
    else if(direction=="FortyFiveDown"){
      drawBitmap( x, y, arrow8x8_FortyFiveDown, 8, 8, color);
    }
    else if(direction=="SingleDown"){
      drawBitmap( x, y, arrow8x8_SingleDown, 8, 8, color);
    }
    else if(direction=="DoubleDown"){
      drawBitmap( x-4, y, arrow8x8_SingleDown, 8, 8, color);
      drawBitmap( x+4, y, arrow8x8_SingleDown, 8, 8, color);
    }else if(direction=="NOT COMPUTABLE"){
      drawBitmap( x, y, arrow8x8_NOT_COMPUTABLE, 8, 8, color);
    }
  }else if(size==2){
    if(direction=="DoubleUp"){
      drawBitmap( x, y, arrow16x16_SingleUp, 16, 16, color);
    }
    else if(direction=="SingleUp"){
      drawBitmap( x, y, arrow16x16_SingleUp, 16, 16, color);
    }
    else if(direction=="FortyFiveUp"){
      drawBitmap( x, y, arrow16x16_FortyFiveUp, 16, 16, color);
    }
    else if(direction=="Flat"){
      drawBitmap( x, y, arrow16x16_flat, 16, 16, color);
    }
    else if(direction=="FortyFiveDown"){
      drawBitmap( x, y, arrow16x16_FortyFiveDown, 16, 16, color);
    }
    else if(direction=="SingleDown"){
      drawBitmap( x, y, arrow16x16_SingleDown, 16, 16, color);
    }
    else if(direction=="DoubleDown"){
      drawBitmap( x-8, y, arrow16x16_SingleDown, 16, 16, color);
      drawBitmap( x+8, y, arrow16x16_SingleDown, 16, 16, color);
    }else if(direction=="NOT COMPUTABLE"){
      drawBitmap( x, y, arrow16x16_NOT_COMPUTABLE, 16, 16, color);
    }
  }else if(size==3){
    if(direction=="DoubleUp"){
      drawBitmap( x, y, arrow32x32_DoubleUp, 32, 32, color);
    }
    else if(direction=="SingleUp"){
      drawBitmap( x, y, arrow32x32_SingleUp, 32, 32, color);
    }
    else if(direction=="FortyFiveUp"){
      drawBitmap( x, y, arrow32x32_FortyFiveUp, 32, 32, color);
    }
    else if(direction=="Flat"){
      drawBitmap( x, y, arrow32x32_flat, 32, 32, color);
    }
    else if(direction=="FortyFiveDown"){
      drawBitmap( x, y, arrow32x32_FortyFiveDown, 32, 32, color);
    }
    else if(direction=="SingleDown"){
      drawBitmap( x, y, arrow32x32_SingleDown, 32, 32, color);
    }
    else if(direction=="DoubleDown"){
      drawBitmap( x, y, arrow32x32_DoubleDown, 32, 32, color);
    }else if(direction=="NOT COMPUTABLE"){
      drawBitmap( x, y, arrow32x32_NOT_COMPUTABLE, 32, 32, color);
    }
  }
}

void drawTime(int x, int y, int size, uint16_t color){
  String timeStr;
  if(hour()<10 && minute()<10){
    timeStr = "0"+String(hour())+":0"+String(minute());
  }
  else if(hour()>=10 && minute()<10){
    timeStr = String(hour())+":0"+String(minute());
  }
  else if(hour()<10 && minute()>=10){
    timeStr = "0"+String(hour())+":"+String(minute());
  }
  else if(hour()>=10 && minute()>=10){
    timeStr = String(hour())+":"+String(minute());
  }
  displayText(x, y, timeStr, size, WHITE);
}

void drawLoading(){
  ClearDisplay();
  displayText(10, 12, "Loading", TEXT_SIZE, WHITE);
  for (int i = 20; i < 30; i+=5){
    displayText(10, i, ".", TEXT_SIZE, WHITE);
    UpdateDisplay();
  }
}
