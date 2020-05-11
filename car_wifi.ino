#include <Servo.h>
#include "wifi_server.h"
#include "display.h"
#include <stdio.h>
Servo servo1;
#define MAXMUN_LEFT 60
#define MAXMUN_RIGHT 0
#define MIDDLE 30
char* last_turn_direction;
extern Connect_Status wifi_status;
int angle = MIDDLE;
Wifi_server wifi_server;
Display display_oled;
void wifi_status_show(int status){
  //char *ssid = wifi_server.ssid;
  //char *wifi_info; 
  switch (status){
    case 1:
      display_oled.show_wifi_status("wifi timeout:");
      break;
    case 2:
      display_oled.show_wifi_status("wifi disconnected");
      break;
    case 3:
      display_oled.show_wifi_status("wifi connected");
      break;      
    }
}

void wifi_connect(){
  display_oled.show_wifi_status("connecting wifi...");
  wifi_server.wifi_init();
  if(wifi_status == wifi_connect_connected){
    display_oled.show_ip(wifi_server.ip_addr);  //show the ip address
    display_oled.show_wifi_ssid(wifi_server.wifi_ssid);
   }
    
}

void setup() {
  Serial.begin(115200);
  servo1.attach(12);
  servo1.write(angle); //turn to straight at initial state
  display_oled.display_init();
  wifi_connect(); 
}
void loop() {
    wifi_server.wifi_server();
    wifi_status_show(wifi_status);   
    char *turn_direction;  
    if(wifi_status != wifi_connect_connected){
      delay(2000);
      servo1.write(MIDDLE);
      wifi_connect();
    }
    angle = wifi_server.data_recived;
    turn_direction = "straight"; 
    if(angle<30){
        turn_direction = "left";
    }
    if(angle>30){
        turn_direction = "right"; 
    }  
    //Serial.println(angle);   
    servo1.write(angle);
    
    if(turn_direction != last_turn_direction){
      display_oled.show_string(turn_direction);
    }         
    last_turn_direction = turn_direction;
}

void blink(){
   //digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
   //delay(1000);
}
