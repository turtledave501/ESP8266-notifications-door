#include <ESP8266WiFi.h>

const int reedSwitch = 4;
const int led = 2; //optional

// Detects whenever the door changed state
bool doorStatus = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

//check if change interval is longer than 1500ms
unsigned long previousMillis = 0; 
const long interval = 1500;

//Looking for config.txt file, then looking for ssid, pws, api and inputing them as chars
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("config.txt");
    std::string line;
    std::string ssid, password, apiKey;

    while (std::getline(inputFile, line)) {
        if (line.find("ssid") != std::string::npos) {
            ssid = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
        }
        else if (line.find("password") != std::string::npos) {
            password = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
        }
        else if (line.find("apiKey") != std::string::npos) {
            apiKey = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
        }
    }

    //Using the extracted values and defined host
    const char* ssid = ssid.c_str();
    const char* password = password.c_str();
    const char* apiKey = apiKey.c_str();
    const char* host = "maker.ifttt.com";

}
//store bool in RAM
RAM_ATTR void changeDoorStatus() {
  Serial.println("Door status changed");
  doorStatus = true;
}

//setup and conencting to wifi
void setup() {
  Serial.begin(115200); //debug

  //current door state
  pinMode(reedSwitch, INPUT_PULLUP);
  state = digitalRead(reedSwitch);

  //LED depends on the door state
  pinMode(led, OUTPUT);
  digitalWrite(led, state);
  
  // Set the reedswitch pin as interrupt, assign interrupt function and set CHANGE mode
  attachInterrupt(digitalPinToInterrupt(reedSwitch), changeDoorStatus, CHANGE);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // connecting
  }
  Serial.println("");
  Serial.println("WiFi connected, YEEEEEES");  
}

//update void
void loop() {
  
  if (doorStatus){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) { //this is so that updates aren't called rapidly but it waits 1500ms
      previousMillis = currentMillis; 
      // If a state has occured, invert the current door state   
      state = !state; // Invert door state
      if(state) {
        doorState = "closed";
      }
      else{
        doorState = "open";
      //prints door state
      digitalWrite(led, state);
      doorStatus = false;
      Serial.println(state);
      Serial.println(doorState);