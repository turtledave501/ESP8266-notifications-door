#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* Wifi_Name = "";
const char* Wifi_Password = ""; 

String phone_num = "";
String API = "";

// Detects whenever the door changed state
bool doorStatus = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
String doorState;
//pins
const int reedSwitch = 4;
const int LED = 2;

//check if change interval is longer than 500ms
unsigned long previousMillis = 0; 
const long interval = 2000;

//message part
  void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phone_num + "&apikey=" + API + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  int retries = 3; // Maximum number of retries
  while (httpResponseCode != 200 && retries > 0) {
    Serial.println("Error sending message, retrying...");
    httpResponseCode = http.POST(url);
    retries--;
    delay(5000); // Wait 5 seconds between retries
  }
  
  if (httpResponseCode == 200){
    Serial.print("Message sent");
  }
  else{
    Serial.println("Error");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

}

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
  WiFi.begin (Wifi_Name, Wifi_Password);
  
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
    if(currentMillis - previousMillis >= interval) { //this is so that updates aren't called rapidly but it waits 500ms
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
      
      sendMessage("door: " + doorState); // sends door status
  }
}
}

