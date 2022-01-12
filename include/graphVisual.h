#ifndef GRAPH
#define GRAPH
#include <Arduino.h>
#include "state.h"

void setOrigoValue(int*, int*);
int hourCalc(int hr, int hrsToRemove);

String origoTimeLabelParser(int, int);

void drawGraph(bool);

void drawSGVwithUnit(int, int, uint16_t);

void drawInfoBar(int, int);

void displayGraph();
void visualizeGraph();



#endif // GRAPH
