#pragma once
#include <Adafruit_ssd1306syp.h>
#define SDA_PIN 4
#define SCL_PIN 5
  
class Display
{ 
    private:      
    public:      
    Display();
    void display_init();
    void show_data(int s);
    void show_ip(int s);
    void show_string(String s);
    void show_wifi_status(String s);
    void show_wifi_ssid(String s);
    void show_led_pwm(String s);
};
