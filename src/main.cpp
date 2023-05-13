#include <Wire.h>

#include <TimeLib.h>
#include <SimpleTimer.h>
// 导入心知天气
#include <ESP8266_Seniverse.h>
// 声明天气
WeatherNow weatherNow;


SimpleTimer timer;


#include <DHT.h>

DHT dht12(12, 11);



// 网络连接
// #include "../src/lianwang.h"
// AP连接，web配置网络
#include "../src/lianwang_Web.h"
// OLED显示内容
#include "../src/oled_xs.h"

// NTP时间同步
#include "../src/ntp.h"

// 室内温湿度
String sn_wd;
String sn_sd;

int date_year;
int date_Month;
int date_day;
int date_Hour; 
int date_Minute;
int date_Second;

// 天气
String tq;
// 温湿度(暂时伪造)
String wsd = "20℃ 75%";


int pmd_wz = 0;
// 温度
int wd;
// 天气代码
int tqdm;
// 天气图标代码
int hjtb[]= {241,124,127,259,223,187,137,138,159,254};//下雨，阴天，多云，晴天，月亮，雾霾，满月，大雾
// 图片对应的序号
int tb = 3;



void update(){
  time_t timestamp = timeClient.getEpochTime();

  // 将时间戳转换为日期
  tmElements_t time;
  breakTime(timestamp, time);

  date_year = time.Year + 1970;
  date_Month = time.Month;
  date_day = time.Day;
  date_Hour = time.Hour;
  date_Minute = time.Minute;
  date_Second = time.Second;
}
String int_week(int t){
    if (t == 0){
        return "星期日";
    }
    if (t == 1){
        return "星期一";
    }
    if (t == 2){
        return "星期二";
    }
    if (t == 3){
        return "星期三";
    }
    if (t == 4){
        return "星期四";
    }
    if (t == 5){
        return "星期五";
    }
    if (t == 6){
        return "星期六";
    }
    return "";
}
void jstb() {
  if (tqdm >= 10 && tqdm <= 25) {
    tb = 0;

  }
  if (tqdm == 4 || tqdm == 9) {
    tb = 1;

  }
  if (tqdm >= 5 && tqdm <= 8) {
    tb = 2;

  }
  if ((tqdm == 0 || tqdm == 2) || tqdm == 38) {
    tb = 3;

  }
  if (tqdm == 1 || tqdm == 3) {
    tb = 4;

  }
  if (tqdm == 31) {
    tb = 5;

  }
  if (tqdm == 30) {
    tb = 7;

  }
  if (tqdm >= 26 && tqdm <= 29) {
    tb = 8;

  }
  if (tqdm >= 32 && tqdm <= 36) {
    tb = 9;

  }

}


void updata_Weather(){

    if (weatherNow.update()) {
        // 天气
        tq = String(weatherNow.getWeatherText());
        // 天气代码
        tqdm = int(weatherNow.getWeatherCode());
        // 温度
        wd = weatherNow.getDegree();
        // 将获取到的天气代码换成对应的图标
        jstb();
  }
  
    
}

// 更新天气
void Simple_timer_1() {
    updata_Weather();
    
}
// udp同步时间
void Simple_timer_2() {
    // 如果初始化失败就再次初始化
    if (date_year == 1970){
        //配置ntp服务器,默认同步站点ntp1.aliyun.com
        ntp_update();
    }
    
// 将epochTime换算成年月日
    update();
}

void setup(){

  Serial.begin(115200);

  u8g2.setI2CAddress(0x3C*2);
  u8g2.begin();
  u8g2.enableUTF8Print();
  
  // 连接无线网络，WIFI和密码
  //lianw("ZIME","");

  //初始化提示页面
  u8g2.firstPage();
  do
  {
    oled_chushihua();
  }while(u8g2.nextPage());

  

  //使用AP,web配置网络
  lianjie();

  //配置ntp服务器,默认同步站点ntp1.aliyun.com
  ntp_update();

  u8g2.firstPage();
  do
  {
    oled_ces_1();
  }while(u8g2.nextPage());
  delay(1000);
  dht12.begin();
  // 实例化天气API
  weatherNow.config("SZWNXyZL2iXstfuew", "ip", "c", "zh-Hans");
  updata_Weather();
  timer.setInterval(60000L, Simple_timer_1);
  timer.setInterval(200L, Simple_timer_2);

}


void loop(){

  // OLED显示主题：1
  u8g2.firstPage();
  do
  {
    wsd = String(dht12.readTemperature()).substring(0,2)+"℃ "+String(dht12.readHumidity()).substring(0,2)+"%";
    oled_snwsd(wsd);
    oled_tq(tq,String(wd)+"℃");
    oled_tb(hjtb[tb]);
    oled_riqi(String(date_year)+"年"+String(date_Month)+"月"+String(date_day)+"日 "+int_week(timeClient.getDay()));
    oled_time(String(timeClient.getFormattedTime()));
  }while(u8g2.nextPage());

  // 开启定时器
  timer.run();
}

