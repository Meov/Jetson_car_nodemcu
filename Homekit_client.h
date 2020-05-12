#pragma once
#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <ESP8266WiFi.h>
class Homekit_client
{
private:
    /* data */
public:
    Homekit_client(/* args */);

    void homekit_setup();
    void homekit_loop();

    ~Homekit_client();
};

