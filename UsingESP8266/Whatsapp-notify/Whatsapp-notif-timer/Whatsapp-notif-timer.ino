#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

//wifi credentials
const char* Wifi_Name = "";
const char* Wifi_Password = ""; 

//Callmebot credentials
String phone_num = ""; // with +prefix (+420)
String API = "";

// Detects whenever the door changed state
bool doorStatus = false;

// Holds reedswitch state (1=opened, 0=close)
bool state;
bool prevState;
String doorState;
//pins
const int reedSwitch = 4;
const int LED = 2;

//check if change interval is longer than 500ms
unsigned long previousMillis = 0; 
const long interval = 2000;

// Debounce variables
const long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

// Timer variables
unsigned long timerStart = 0;
const long timerDuration = 180000; // 3 minutes in milliseconds
bool doorOpen = false;

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

  // Retry sending message if it fails
  while (httpResponseCode != 200 && retries > 0) {
    Serial.println("Error sending message, retrying...");
    httpResponseCode = http.POST(url);
    retries--;
    delay(5000); // Wait 5 seconds between retries
  }
  
  // If message was sent successfully
  if (httpResponseCode == 200){
    Serial.print("Message sent");
  }
  // If message failed to send
  else{
    Serial.println("Error");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
}

//Inital setup
void setup() {
  Serial.begin(9600); //debug
  //current door state
  pinMode(reedSwitch, INPUT_PULLUP);
  state = digitalRead(reedSwitch);
  prevState = state;

  //LED depends on the door state
  pinMode(LED, OUTPUT);
  digitalWrite(LED, state);
  
  // Set the reedswitch pin as interrupt, assign interrupt function and set CHANGE mode
  attachInterrupt(digitalPinToInterrupt(reedSwitch), changeDoorStatus, CHANGE);

  // Connect to Wi-Fi
  WiFi.begin (Wifi_Name, Wifi_Password);
  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print("."); // connecting
  }
  Serial.println("");
  Serial.println("WiFi connected!!!!");  
}
//interrupt function
ICACHE_RAM_ATTR void changeDoorStatus() {
  unsigned long currentTime = millis();
  if (currentTime - lastDebounceTime > debounceDelay) {
    doorStatus = true;
  }
  lastDebounceTime = currentTime;
}

//update void
void loop() {

  // Check if the door state has changed
  if (doorStatus){
    unsigned long currentMillis = millis();
    //this is so that updates aren't called rapidly but it waits for the interval
    if(currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; 
      // If a state has occured, invert the current door state   
      state = digitalRead(reedSwitch);
      
      if (state != prevState) {
        // Door has closed
        if(state) {
          doorState = "closed";
        }
        // Door has opened so timer starts
        else{
          doorState = "open";
          timerStart = millis(); // Start the timer
          doorOpen = true; // Set doorOpen to true
        }
        
        // Update LED and send door state
        digitalWrite(LED, state);
        doorStatus = false;
        Serial.println(state);
        Serial.println(doorState);
          
        sendMessage("door: " + doorState); // sends door status
        prevState = state;
      }
    }
  }
  
  // Check the timer if the door is open
  if (doorOpen) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - timerStart;
    unsigned long remainingTime = timerDuration - elapsedTime;

    // Door is open and timer has expired, send notification
    if (remainingTime <= 0) {
      sendMessage("Door still open!"); // send notification
      doorOpen = false; // Reset timer and doorOpen
      timerStart = 0;
    }

    // Door is closed, reset timer and doorOpen
    else if (state) {
      doorOpen = false;
      timerStart = 0;
    }
  }
}