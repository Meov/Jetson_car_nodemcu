#pragma once
#include"Display.h"
#include <stdio.h>
Adafruit_ssd1306syp display(SDA_PIN, SCL_PIN);
Display::Display(){
  //构造函数
}
void Display::display_init(){
    display.initialize(); 
    delay(1000);
    Serial.println("initia_display");
}

void Display::show_wifi_status(String s){
  
  if(s!="wifi connected") 
    display.clear();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.fillRect(0,0,150,10,0);
  display.println(s);
  display.update();
}

void Display::show_ip(int s){
  //display.clear();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);  //show it on the left uopn
  display.fillRect(0,10,120,10,0);
  unsigned char *ip = (unsigned char*)&s;
  char ip_str[20];
  sprintf(ip_str,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
  Serial.println(ip_str);
  display.print("IP:");display.println(ip_str);
  display.update();
}

void Display::show_wifi_ssid(String s){   
  //display.clear();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.fillRect(0,20,150,20,0);
  display.print("SSID:");display.println(s);
  display.update();
} 

void Display::show_string(String s){   
  //display.clear();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
  display.fillRect(0,30,60,30,0);
  display.println(s);
  display.update();
} 


void Display::show_led_pwm(String s){
  //display.clear();
  char str_s[20];
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(65,30);
  display.fillRect(65,30,120,30,0);
  string pwm_str = "pwm: ";
  
  sprintf(str_s,"%s%s",pwm_str.c_str(),s.c_str());

  display.println(str_s);
  display.update();
}
/*
void loop()
{
 unsigned char i;
  
  display.drawLine(0, 0, 127, 63,WHITE);
  display.update();
  delay(1000);
  display.clear();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.update();
  for(i=0;i<5;i++)
  {
    lucky.ShowCN(i*16,6,i);//Show Chinese
  }
  delay(2000);
  display.clear();
}
*/
