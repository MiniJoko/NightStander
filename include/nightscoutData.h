#ifndef NIGHTSCOUTDATA
#define NIGHTSCOUTDATA
#include <Arduino.h>
#include <ArduinoJson.h>
#include "overrides.h"

// const char* urlRequest(uint8_t amount) ;
void GetFromEEPROM();
double getSGV();
float getMaxSGV();
String getDirection();
float getDate();
StaticJsonDocument<2048> getGraphData();
JsonArray getOverrides();
OVERRIDE_LIST getOverridesList();

String dataRequestUrl(int count);
String overridesRequestUrl(int count);
String httpGETRequest(const char* serverName);
void httpPostRequest(/*String serverName*/);
String httpGetData(int) ;

String httpGetOverrides(int);
void storeOverrides();
void SetOverride(int index);

void storeGraphData();
void storeData();

#endif // NIGHTSCOUTDATA
