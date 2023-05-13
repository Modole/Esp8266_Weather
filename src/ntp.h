#include <NTPClient.h>

#include <WiFiUdp.h>



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);

void ntp_update(){

  timeClient.begin();

  timeClient.update();
}
