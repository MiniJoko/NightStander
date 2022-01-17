#ifndef OLED_H
#define OLED_H
#include <Arduino.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define TEXT_SIZE 1

void InitDisplay();
void UpdateDisplay();
void ClearDisplay();
void drawPixel(int, int, uint16_t);
void DrawFastHLine(int16_t  x, int16_t  y, int16_t  length, uint16_t color);
void DrawFastVLine(int16_t x, int16_t y, int16_t length, uint16_t color);
void fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
void drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color);

void drawPoint(int, int, uint16_t);
void drawArrowUp(int x, int y, uint16_t color);
void drawArrowDown(int x, int y, uint16_t color);
void displayText(int x, int y, String text, int size, uint16_t color);
void drawWifi(int, int, int, uint16_t);
void drawSGV(int, int, int, uint16_t);
void drawDirection(int, int, int, uint16_t);
void drawTime(int , int , int , uint16_t );

#endif
