#pragma once
#include <ESP8266WiFi.h>
#define TIMEOUT 20000
enum Connect_Status{
    wifi_connect_timeout = 1,
    wifi_connect_disconnect,
    wifi_connect_connected
};

class Wifi_server
{
  public:
    String wifi_ssid;
    u32_t ip_addr = 0;
    //int data_recived=30;
    Wifi_server();
    void wifi_init();
    void wifi_server();
};
