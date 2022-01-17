#ifndef TIME_H
#define TIME_H

#include <TimeLib.h>

time_t getNTPtime();
void initArduinoTime();

bool updateTimer(unsigned long, unsigned long*);



#endif
