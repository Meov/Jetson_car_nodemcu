#include <Servo.h>
#include "wifi_server.h"
#include "display.h"
#include <stdio.h>
#include "Homekit_client.h"
#define MAXMUN_LEFT 60
#define MAXMUN_RIGHT 0
#define MIDDLE 30
Servo servo1;
char* last_turn_direction;
extern Connect_Status wifi_status;
int angle = MIDDLE;
int last_angle;
char angle_Str[4];
Wifi_server wifi_server;
Display display_oled;
Homekit_client homekit_client;
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
  wifi_server.wifi_init ();
  if(wifi_status == wifi_connect_connected){
    display_oled.show_ip(wifi_server.ip_addr);  //show the ip address
    display_oled.show_wifi_ssid(wifi_server.wifi_ssid);
    display_oled.show_string("straight");
   }
}
void setup() {
  Serial.begin(115200);
  servo1.attach(12);  //servo motor pin   pin12===>D6 in nodemcu
  servo1.write(angle); //turn to straight at initial state
  display_oled.display_init();
  display_oled.show_string("reset");  
  delay(2000); 
  wifi_connect(); 
  homekit_client.homekit_setup();
}

void loop() {
    wifi_server.wifi_server();
    wifi_status_show(wifi_status); 
    homekit_client.homekit_loop();
    char *turn_direction;  
    if(wifi_status != wifi_connect_connected){ //check wifi status
      servo1.write(MIDDLE);
      delay(2000);
      wifi_connect();
    }
    //angle = wifi_server.data_recived;
    turn_direction = "straight"; 
    if(angle<30){
        turn_direction = "left";
    }
    if(angle>30){
        turn_direction = "right"; 
    }
    if(angle != last_angle){
      servo1.write(angle);
      itoa(angle,angle_Str,10);
      display_oled.show_led_pwm(angle_Str);
      //Serial.println(angle_Str);   
    }
    if(turn_direction != last_turn_direction){
      display_oled.show_string(turn_direction);
    }         
    last_turn_direction = turn_direction;
    last_angle = angle;
}
