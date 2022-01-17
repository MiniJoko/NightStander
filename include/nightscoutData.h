#ifndef NIGHTSCOUTDATA
#define NIGHTSCOUTDATA
#include <Arduino.h>
#include <ArduinoJson.h>
#include "overrides.h"

void GetFromEEPROM();
double getSGV();
float getMaxSGV();
String getDirection();
float getDate();
StaticJsonDocument<2048> getGraphData();
JsonArray getOverrides();
OVERRIDE_LIST getOverridesList();
String getSAGE();
String getCAGE();
double getCOB();
double getIOB();

String dataRequestUrl(int count);
String overridesRequestUrl(int count);
String valuesRequestUrl();
String httpGETRequest(const char* serverName);
void httpPostRequest(/*String serverName*/);
String httpGetData(int) ;

String httpGetOverrides(int);
String httpGetValues();
void storeOverrides();
void SetOverride(int index);

void storeGraphData();
void storeData();
void storeValues();
#endif // NIGHTSCOUTDATA