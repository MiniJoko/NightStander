#include "EEPROM.h"
#include <WebServer.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

#include "GFX.h"
#include "WiFiManager.h"

String html_first ="<!DOCTYPE HTML> <html> <head> <title>Nightstander Configuration</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <link rel=\"icon\" href=\"data:,\"> <style> html { font-family: Arial; display: inline-block; text-align: center; } h2 { font-size: 2.0rem; } p {font-size: 2.0rem;} body { width: 375px; margin:0px auto; padding-bottom: 25px; background-color: #0c3b6d; color: aliceblue; } table{ margin-left: auto; margin-right: auto; } tbody{ display: inline-block; width:375px; } td:first-child{ width:60px; text-align: right; } td:last-child{ text-align: left; } td.save{ text-align: center; } .button{ height: 50px; width: 90px; color: aliceblue; background-color: rgb(40, 129, 184); } </style> </head> <body> <h2>Nightstander Configuration</h2> <form action=\"/\" method=\"post\"> <table> <tr> <td> <label for=\"wifi_ssid\">Choose Wifi</label> </td> <td> <select id=\"wifi_ssid\" name=\"wifi_ssid\">";

String html_last ="</select> </td> </tr> <tr> <td> <label>Password: </label> </td> <td> <input maxlength=\"30\" name=\"password\"> </td> </tr> <tr> <td> <label>Nightscout: </label> </td> <td> <input maxlength=\"100\" name=\"nightscout\"> </td> </tr><tr><td colspan=\"2\">You need to hash your api-key before you type it in here. Turn off wifi and visit this link. Type your api-key in the box and copy the results. Then turn wifi back on and make sure you are connected to Nightstander WiFi and paste the result here. <a href=\"http://www.sha1-online.com\" target=\"_blank\" style=\"color:yellow\">http://www.sha1-online.com/</td></tr> <tr> <td> <label>Api-Key: </label> </td> <td> <input maxlength=\"100\" name=\"apikey\"> </td> </tr> <tr><td class=\"save\" colspan=\"2\"> <input type=\"submit\" value=\"Save\" class=\"button\"> </td> </tr> </table> </form> </body> </html>";


int numberOfSSID = 0;
String ssidList[15];

WebServer server(80);

/*
 * Function to handle unknown URLs
 */
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

/*
 * Function for writing WiFi creds to EEPROM
 * Returns: true if save successful, false if unsuccessful
 */
bool writeToMemory(String ssid, String pass, String ns, String api){
  char buff1[30];
  char buff2[30];
  char buff3[100];
  char buff4[100];
  ssid.toCharArray(buff1,30);
  pass.toCharArray(buff2,30);
  ns.toCharArray(buff3,100);
  api.toCharArray(buff4,100);
  EEPROM.writeString(SSID_ADDR,buff1);
  EEPROM.writeString(PSK_ADDR,buff2);
  EEPROM.writeString(NS_ADDR,buff3);
  EEPROM.writeString(API_ADDR,buff4);//->164
  delay(100);
  String s = EEPROM.readString(SSID_ADDR);
  String p = EEPROM.readString(PSK_ADDR);
  String n = EEPROM.readString(NS_ADDR);
  String a = EEPROM.readString(API_ADDR);
  //#if DEBUG
  Serial.print("Stored SSID, password, are: ");
  Serial.print(s);
  Serial.print(" / ");
  Serial.print(p);
  Serial.print("  Nightscout:  ");
  Serial.print(n);
  //#endif
  if(ssid == s && pass == p && ns == n){
    return true;
  }else{
    return false;
  }
}

/*
 * Function for handling form
 */
void handleSubmit(){
  String response_success="<h1>Success</h1>";
  response_success +="<h2>Device will restart in 3 seconds</h2>";

  String response_error="<h1>Error</h1>";
  response_error +="<h2><a href='/'>Go back</a>to try again";

  if(writeToMemory(String(server.arg("wifi_ssid")),String(server.arg("password")),String(server.arg("nightscout")),String(server.arg("apikey")))){
     server.send(200, "text/html", response_success);
     EEPROM.commit();
     delay(3000);
     ESP.restart();
  }else{
     server.send(200, "text/html", response_error);
  }
}

void wipeEEPROM(){
  ClearDisplay();
  displayText(10, 2, String("Reseting Device. Please wait"), TEXT_SIZE, WHITE);
  UpdateDisplay();
  for(int i=0;i<512;i++){
    EEPROM.write(i,0);
    displayText(i-1, 32, ".", TEXT_SIZE, WHITE);
    UpdateDisplay();
  }
  ClearDisplay();
  EEPROM.commit();
  delay(3000);
  ESP.restart();
}

void GetWifi(){
   numberOfSSID = WiFi.scanNetworks();
   for (int i = 0; i < numberOfSSID; i++) {
      // Print SSID and RSSI for each network found
      Serial.println(WiFi.SSID(i));
      ssidList[i]=String(WiFi.SSID(i));
  }
  WiFi.disconnect();
}

String AddWifiList(){
    String wifiselectlist = "";
    for(int i = 0; i< numberOfSSID; i++){
      wifiselectlist += "<option value=\""+ ssidList[i] + "\">" + ssidList[i] +"</option>";
    }
    return wifiselectlist;
}

void handleRoot() {
  if (server.hasArg("wifi_ssid")&& server.hasArg("password")&& server.hasArg("nightscout")) {
    handleSubmit();
  }
  else {
    String html = html_first + AddWifiList() + html_last;
    server.send(200, "text/html", html);
  }
}

/*
 * Function for loading form
 * Returns: false if no WiFi creds in EEPROM
 */
bool loadWIFICredsForm(){
  String s = EEPROM.readString(SSID_ADDR);
  String p = EEPROM.readString(PSK_ADDR);

  const char* ssid     = "Nightstander WiFi";
  const char* password = "12345678";

  Serial.println("Setting Access Point...");

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  Serial.print("AP IP address: ");
  Serial.println(IP);
  ClearDisplay();
  displayText(10, 2, String("Connect to:"), TEXT_SIZE, WHITE);
  displayText(15, 12, String(ssid), TEXT_SIZE, WHITE);
  displayText(10, 22, String("use password: "), TEXT_SIZE, WHITE);
  displayText(15, 32, password, TEXT_SIZE, WHITE);
  displayText(10, 42, String("and visit:"), TEXT_SIZE, WHITE);
  displayText(15, 52, IP.toString(), TEXT_SIZE, WHITE);
  UpdateDisplay();
  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.println("HTTP server started");

  while(s.length() <= 0 && p.length() <= 0){
    server.handleClient();
    delay(100);
  }

  return false;
}

/*
 * Function checking WiFi creds in memory
 * Returns: true if not empty, false if empty
 */
bool CheckWIFICreds(){
  Serial.println("Checking WIFI credentials");
  String s = EEPROM.readString(SSID_ADDR);
  String p = EEPROM.readString(PSK_ADDR);
  //#if DEBUG
  Serial.print("Found credentials: ");
  Serial.print(s);
  Serial.print("/");
  Serial.print(p);
  delay(5000);
  //#endif
  if(s.length() > 0 && p.length() > 0){
    return true;
  }else{
    return false;
  }
}

void initWifiCred(){

  if(!CheckWIFICreds()){
    Serial.println("No WIFI credentials stored in memory. Loading form...");
    while(loadWIFICredsForm());
  }
}

bool initWIFI(){
    String s = EEPROM.readString(SSID_ADDR);
    String p = EEPROM.readString(PSK_ADDR);
    const char* ssid = s.c_str();
    const char* password = p.c_str();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    ClearDisplay();
    displayText(10, 5, String("Connecting to WIFI:"), TEXT_SIZE, WHITE);
    displayText(15, 20, String(s), TEXT_SIZE, WHITE);
    UpdateDisplay();
    int i = 10;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      displayText(i, 35, String("."), TEXT_SIZE, WHITE);
      UpdateDisplay();
      i+=3;
      delay(500);
      if (i > 55){
        return false;
      }
    }

    Serial.println(WiFi.localIP());
    ClearDisplay();
    displayText(10, 5, String("Now Connected to:"), TEXT_SIZE, WHITE);
    displayText(15, 20, String(s), TEXT_SIZE, WHITE);
    UpdateDisplay();
    delay(1000);
    return true;
  }
