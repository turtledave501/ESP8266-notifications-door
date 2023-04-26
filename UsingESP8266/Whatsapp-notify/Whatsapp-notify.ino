#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* Wifi_Name = "";
const char* Wifi_Password = "";

String phone_num = "";
String API = "";

//pins
const int reedSwitch = 4;
const int LED = 2;

//check if change interval is longer than 500ms
unsigned long previousMillis = 0; 
const long interval = 500;

void setup() {
  Serial.begin(9600);

   WiFi.begin (WiFi_Name, Wifi_Password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // connecting
  }
  Serial.println("");
  Serial.println("WiFi connected!!!!");  
  }

}
