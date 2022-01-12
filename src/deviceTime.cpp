
#include <TimeLib.h>
#include <WiFi.h>
#include "deviceTime.h"



const char* ntpServer1 = "pool.ntp.org"; //NTPserver: 500 getrequests allowed/day
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600; //timezone adjustment
const int   daylightOffset_sec = 3600; //daylightsavingtime adjustment

bool timeSynced;
unsigned long currentTime;

//get time from NTPserver.
time_t getNTPtime() {
  timeSynced = true;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    timeSynced = false;
    Serial.println(WiFi.status());
    delay(1000);
  }
  if (timeSynced) {
    Serial.println("Time synchronization complete.");
  } else {
    Serial.println("Time synchronization failed.");
  }
  return mktime(&timeinfo) + gmtOffset_sec;
}

void initArduinoTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer1);
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    Serial.println("Could not reach NTPserver. Retrying...");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer1);
    delay(1000);
  }
  Serial.println("Connected to NTPserver.");
  setSyncProvider(getNTPtime); //timesynchronizer initialized
  setSyncInterval(3600); //Set timesync-intervall in seconds (3600 sec = 1 hr)
}

bool updateTimer(unsigned long milliseconds, unsigned long* timer){
  currentTime = millis();
  if (currentTime - *timer > milliseconds) {
    *timer = currentTime;
    return true;
  }
  return false;
}

