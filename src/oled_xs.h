#include <U8g2lib.h>
#include <WiFiManager.h>
// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,  5, 4, U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE);



void oled_chushihua() {
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(0,1);
  u8g2.print("请连接“ESP”开头的");
  u8g2.setCursor(0,17);
  u8g2.print("WiFi网络");
  u8g2.setCursor(0,33);
  u8g2.print("连接成功后即可");
  u8g2.setCursor(0,48);
  u8g2.print("进入系统");
}
void oled_ces_1() {
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(0,17);
  u8g2.print("成功进入系统!!!");
  u8g2.setCursor(0,37);
  u8g2.print("IP:");
  u8g2.setCursor(20,37);
  u8g2.print(WiFi.localIP());
  
}
void oled_time(String time) {
  String h = time.substring(0,2);
  String m = time.substring(3,5);
  String s = time.substring(6,8);
  u8g2.setFont(u8g2_font_timB24_tf);
  u8g2.setFontPosTop();
  u8g2.setCursor(33,18);
  u8g2.print(h+":"+m);
  u8g2.setFont(u8g2_font_timR08_tf);
  u8g2.setFontPosTop();
  u8g2.setCursor(108,34);
  u8g2.print(" "+s);
}
void oled_riqi(String rq) {
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(0,1);
  u8g2.print(rq);
}

void oled_tb(int tb) {
  u8g2.setFont(u8g2_font_open_iconic_all_4x_t);
  // 判断网络是否断开
  if (WiFi.status()){
    u8g2.drawGlyph(0,(-21)+4*8,tb);
  }else{
    u8g2.drawGlyph(0,(-21)+4*8,197);
  }
  
}

void oled_tq(String rq,String wd) {
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(0,50);
  if (WiFi.status()){
    u8g2.print(rq+wd);
  }else{
    u8g2.print("网络已断开");
  }
  
}

void oled_snwsd(String rq) {
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(65,51);
  u8g2.print(rq);
}



