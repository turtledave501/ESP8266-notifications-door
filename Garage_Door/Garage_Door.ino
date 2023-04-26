#include <ESP8266WiFi.h>

const int reedSwitch = 4;
const int led = 2; //optional

// Detects whenever the door changed state
bool changeState = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

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
  doorState = true;
}

