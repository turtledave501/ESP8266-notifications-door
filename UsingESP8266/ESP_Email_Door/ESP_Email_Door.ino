#include <ESP8266WiFi.h>

const int reedSwitch = 4;
const int LED = 2;

// Detects whenever the door changed state
bool doorStatus = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;

//check if change interval is longer than 500ms
unsigned long previousMillis = 0; 
const long interval = 1000;

//wifi credentials
const char* WiFi_Name = "";
const char* Wifi_Password = ""; 
const char* IFTTT_API_key = "";
const char* host = "maker.ifttt.com";

//setup and conencting to wifi
void setup() {

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
    delay(1000);
    Serial.print("."); // connecting
  }
  Serial.println("");
  Serial.println("WiFi connected!!!!"); // connected to wifi 
}

//interrupt function
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

      // POST request
      Serial.print("Requesting URL: ");
      Serial.println(url);
      // Send the request to IFTTT
      client.print(String("POST ") + url + " HTTP/1.1\r\n" + 
                          "Host: " + host + "\r\n" + 
                          "Content-Type: application/x-www-form-urlencoded\r\n" + 
                          "Content-Length: 13\r\n\r\n" +
                          "value1=" + doorState + "\r\n"); // email subject if door is "closed" or "open"
    }  
  }
}

