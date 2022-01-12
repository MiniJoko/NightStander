#define ARDUINOJSON_USE_DOUBLE 1
#define ARDUINOJSON_USE_LONG_LONG 1

#include <TimeLib.h>
#include <HTTPClient.h>
#include <Timestamps.h>
#include <EEPROM.h>

#include "time.h" //Library to handle standard "tm" time struct
#include <ArduinoJson.h> //Library to handle JSON-messages
#include "nightscoutData.h"
#include "overrides.h"
#include "WiFiManager.h"

//http://nightstander.herokuapp.com/api/v1/profile.json?count=
String prefix = "http://";
String nightscout;
String dataSuffix = ".herokuapp.com/api/v1/entries.json?count=";
String overridesSuffix = ".herokuapp.com/api/v1/profile.json?count=1";
String sendOverrideSuffix = ".herokuapp.com/api/v2/notifications/loop";
String apikey;

String JSONmsg;
Timestamps ts2(3600);

//storage variables for data
double SGV;
float maxSGV;
String direction;
float date;
StaticJsonDocument<2048> data;

JsonArray overrides;
OVERRIDE_LIST overrideList = {0};

void GetFromEEPROM(){
  nightscout = EEPROM.readString(NS_ADDR);
  apikey = EEPROM.readString(API_ADDR);
}

double getSGV(){
  return SGV;
}

float getMaxSGV(){
  return maxSGV;
}

String getDirection(){
  return direction;
}

float getDate(){
  return date;
}

StaticJsonDocument<2048> getGraphData(){
  return data;
}

OVERRIDE_LIST getOverridesList(){
  return overrideList;
}

JsonArray getOverrides(){
  return overrides;
}

String dataRequestUrl(int count){

  String dataRequestUrl = prefix + nightscout + dataSuffix + String(count);
  return dataRequestUrl;
}

String overridesRequestUrl(int count){
  String OverridesRequestUrl = prefix + nightscout + overridesSuffix;
  return OverridesRequestUrl;
}

String httpGETRequest(String serverName) {
  Serial.println(serverName);
  WiFiClient client;
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  Serial.print("payload: ");
  Serial.println(payload);

  return payload;
}

void SetOverride(int index){
  if(WiFi.status()== WL_CONNECTED){
    Serial.println(index);
    WiFiClient client;
    HTTPClient http;
    http.begin(client, prefix + nightscout + sendOverrideSuffix);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("api-secret", apikey);
    String name = overrideList.overrides[index].name;
    String symbol = overrideList.overrides[index].symbol;
    String JsonPOST = "";
    if (index == -1){
      JsonPOST = "{\"eventType\": \"Temporary Override Cancel\"}";
    }else{
      JsonPOST = "{\"eventType\": \"Temporary Override\",\"reason\":\"" + name + "\",\"reasonDisplay\":\"" + symbol + name + "\"}";
    }

    int httpResponseCode = http.POST(JsonPOST);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

String httpGetData(int count) {
  if (WiFi.status() == WL_CONNECTED) {
    JSONmsg = httpGETRequest(dataRequestUrl(count));
    return JSONmsg;
  }
  else {
    Serial.println("WiFi Disconnected");
    return "WiFi Disconnected";
  }
}

String httpGetOverrides(int count){
  if (WiFi.status() == WL_CONNECTED) {
    JSONmsg = httpGETRequest(overridesRequestUrl(count));
    return JSONmsg;
  }
  else {
    Serial.println("WiFi Disconnected");
    return "WiFi Disconnected";
  }
}

void storeOverrides(){
  Serial.println("Storing overrides");
  String JSONmsg=httpGetOverrides(1);
  StaticJsonDocument<112> filter;

  JsonObject filter_0_loopSettings_overridePresets_0 = filter[0]["loopSettings"]["overridePresets"].createNestedObject();
  filter_0_loopSettings_overridePresets_0["insulinNeedsScaleFactor"] = true;
  filter_0_loopSettings_overridePresets_0["name"] = true;
  filter_0_loopSettings_overridePresets_0["symbol"] = true;

  //JsonArray root_0_loopSettings_overridePresets = overrides[0]["loopSettings"]["overridePresets"];
  DynamicJsonDocument doc(2048);


  DeserializationError error = deserializeJson(doc, JSONmsg, DeserializationOption::Filter(filter));

  if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
  }

  overrides = doc[0]["loopSettings"]["overridePresets"];

  int i = 1;
  for (JsonObject item : overrides)
  {
    String name = item["name"];
    String symbol = item["symbol"];
    float percent = item["insulinNeedsScaleFactor"];
    String insulinPercent = String(int(percent*100));

    OVERRIDE temp = {name, symbol, insulinPercent};
    overrideList.overrides[overrideList.size] = temp;
    overrideList.size++;

    Serial.print(i++);
    Serial.print(". name: ");
    Serial.print(name);
    Serial.print(" | symbol: ");
    Serial.print(symbol);
    Serial.print(" | percent: ");
    Serial.println(percent);
  }
}

void storeGraphData(){
  String JSONmsg=httpGetData(36);

  StaticJsonDocument<48> filter;

  JsonObject filter_0 = filter.createNestedObject();
  filter_0["sgv"] = true;
  filter_0["date"] = true;

  DeserializationError error = deserializeJson(data, JSONmsg, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  //find maxSGV
  maxSGV=0;
  for (JsonObject item : data.as<JsonArray>()) {
    float sgvAmerican = item["sgv"]; // glucose value in mg/dl
    float sgv = sgvAmerican / 18;
    if(sgv>maxSGV){
      maxSGV = sgv;
    }
  }

  SGV = data[0]["sgv"];
  direction = data[0]["direction"].as<String>();
}

void storeData(){
  String JSONmsg = httpGetData(1);

  StaticJsonDocument<64> filter;

  JsonObject filter_0 = filter.createNestedObject();
  filter_0["sgv"] = true;
  filter_0["date"] = true;
  filter_0["direction"] = true;

  StaticJsonDocument<128> singleData;

  DeserializationError error = deserializeJson(singleData, JSONmsg, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  JsonObject root_0 = singleData[0];

  long long root_0_date = root_0["date"]; // 1641196228000
  date = root_0_date / 1000 + 3600;

  long long currentTimestamp = ts2.getTimestampUNIX(year(), month(), day(), hour(), minute(), 0);

  int root_0_sgv = root_0["sgv"]; // 92
  SGV = double(root_0_sgv)/18;
  if(currentTimestamp-date>300){ //if the last value is more then 5 mins old, sgv=-1.
    SGV = -1;
  }
  const char* root_0_direction = root_0["direction"]; // "Flat"
  direction = root_0_direction;
}
