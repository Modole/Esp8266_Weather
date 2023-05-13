#include <WiFiManager.h>
WiFiServer server(80);

void lianjie(){
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res = wm.autoConnect();
}