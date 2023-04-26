#include <ESP8266WiFi.h>

const int reedSwitch = 4;
const int LED = 2; //optional

// Detects whenever the door changed state
bool doorStatus = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

//check if change interval is longer than 1500ms
unsigned long previousMillis = 0; 
const long interval = 500;

/*
//Looking for config.txt file, then looking for WiFi_Name, pws, api and inputing them as chars
#include <iostream>
#include <fstream>
#include <string>

std::string WiFi_Name_str, Wifi_Password
_str, IFTTT_API_key_str;

int main() {
      std::ifstream inputFile("privconfig.txt");
      std::string line;
     

      while (std::getline(inputFile, line)) {
          if (line.find( WiFi_Name") != std::string::npos) {
             WiFi_Name_str = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
          }
          else if (line.find("Wifi_Password
          ") != std::string::npos) {
              Wifi_Password
              _str = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
          }
          else if (line.find("IFTTT_API_key") != std::string::npos) {
              IFTTT_API_key_str = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
          }
      }
} 
    
*/

//store bool in RAM 


//input data here
const char* WiFi_Name = "";
const char* Wifi_Password
 = ""; 
const char* IFTTT_API_key = "";
const char* host = "maker.ifttt.com";

//setup and conencting to wifi
void setup() {

    /*
    //Using the extracted values and defined host
      const char* WiFi_Name = WiFi_Name_str.c_str();
      const char* Wifi_Password
       = Wifi_Password
      _str.c_str();
      const char* IFTTT_API_key = IFTTT_API_key_str.c_str();
      const char* host = "maker.ifttt.com";
    */

  
  
  Serial.begin(9600); //debug

  //current door state
  pinMode(reedSwitch, INPUT_PULLUP);
  state = digitalRead(reedSwitch);

  //LED depends on the door state
  pinMode(LED, OUTPUT);
  digitalWrite(LED, state);
  
  // Set the reedswitch pin as interrupt, assign interrupt function and set CHANGE mode
  attachInterrupt(digitalPinToInterrupt(reedSwitch), changeDoorStatus, CHANGE);

  // Connect to Wi-Fi
  WiFi.begin (WiFi_Name, Wifi_Password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // connecting
  }
  Serial.println("");
  Serial.println("WiFi connected!!!!");  
}

ICACHE_RAM_ATTR void changeDoorStatus() {
  Serial.println("Door status changed");
  doorStatus = true;
}
//update void
void loop() {
  
  if (doorStatus){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) { //this is so that updates aren't calLED rapidly but it waits 1500ms
      previousMillis = currentMillis; 
      // If a state has occured, invert the current door state   
      state = !state; // Invert door state
      if(state) {
        doorState = "closed";
      }
      else{
        doorState = "open";
      }  
      //prints door state
      digitalWrite(LED, state);
      doorStatus = false;
      Serial.println(state);
      Serial.println(doorState);

      //Email part
      Serial.print("connecting to ");
      Serial.println(host);
      WiFiClient client;
      const int httpPort = 80;
      if (!client.connect(host, httpPort)) {
        Serial.println("connection unsuccesful");
        return;
      }
    
      String url = "/trigger/door_status/with/key/"; 
      url += IFTTT_API_key;

      //POST payload    
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                          "Host: " + host + "\r\n" + 
                          "Content-Type: application/x-www-form-urlencoded\r\n" + 
                          "Content-Length: 13\r\n\r\n" +
                          "value1=" + doorState + "\r\n"); // email subject if door is "closed" or "open"
    }  
  }
}

