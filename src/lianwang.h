#include <ESP8266WiFi.h>

void lianw(String ssid,String pass){
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Local IP:");
  Serial.print(WiFi.localIP());
  
}