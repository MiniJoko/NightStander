#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#define SSID_ADDR 0
#define PSK_ADDR  32
#define NS_ADDR 64
#define API_ADDR 165

#include <Arduino.h>


void GetWifi();
void handleNotFound();
bool writeToMemory(String ssid, String pass);
void handleSubmit();
void handleRoot();

bool loadWIFICredsForm();
bool CheckWIFICreds();

void initWifiCred();
bool initWIFI();

void wipeEEPROM();

#endif
