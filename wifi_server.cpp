/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>
#include"Display.h"
#include "wifi_server.h"
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>  

WiFiServer server(80);
int time1;

Connect_Status  wifi_status;


// Create an instance of the server
// specify the port to listen on as an argument
Wifi_server::Wifi_server(){
  //do nothing!
}
void connect_timeout(){
  Serial.println("Connct err!");
  wifi_status = wifi_connect_timeout;
}

void Wifi_server::wifi_init() {
  boolean init_esp = false;  //enable this to remove all the network saved
  time1  = millis(); 
  // prepare LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  int led_satus = 0;
  if(init_esp)
  {
    SPIFFS.format();
    WiFi.disconnect();
  }
  WiFiManager wifiManager;
  wifiManager.setTimeout(180);
  if(!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  Serial.println(WiFi.SSID());
  wifi_ssid = WiFi.SSID();
  
  wifi_status = wifi_connect_connected;
  Serial.println();
  Serial.println(F("WiFi connected"));
  digitalWrite(LED_BUILTIN, 1);
  //Start the server
  server.begin();
  Serial.println(F("Server started"));
  // Print the IP address
  Serial.println(WiFi.localIP());
  ip_addr = WiFi.localIP();
}


void Wifi_server::wifi_server() {

  if(WiFi.status() != WL_CONNECTED){
      wifi_status = wifi_connect_disconnect;
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    data_recived += 5;
    if(data_recived>=60) data_recived = 60;
    val = 0;
  } else if (req.indexOf(F("/gpio/1")) != -1) {
    data_recived -= 5;
    if(data_recived<=0) data_recived = 0;
    val = 1;
  } else {
    Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }

  // Set LED according to the request
  digitalWrite(LED_BUILTIN, val);

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }

  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now "));
  client.print((val) ? F("high") : F("low"));
  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'>here</a> to switch LED GPIO on, or <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'>here</a> to switch LED GPIO off.</html>"));

  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));
}
