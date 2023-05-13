# Esp8266_Weather
 Esp8266_0.96OLED_天气时钟
天气时钟 v0.1


采用AP配网，其他设备连接AP后方可进入网络配置界面，配置完点击保存即可保存网络，保存后即可自动连接，连接成功后即可运行系统

通过知心天气获取天气信息，并在OLED上显示图案
通过NTP同步世界时间、年月日、星期几，并在OLED上显示
通过DH11 温湿度传感器采集当前室内温度，并显示到OLED上

-----------------------------------------------
使用Arduion or platformio 打开src/main.cpp文件下载文件即可
-----------------------------------------------

因为是v0.1版，OLED布局上还是有点不足，但功能都是有的
采用的是U8G2图形库，这也导致了文件有点大


