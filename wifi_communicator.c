#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = ;
const char* password = ;
const char* apiKey = ; // Replace with your WeatherAPI key
const char* location = ;  // Replace with your desired location

WiFiClient wifiClient;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://api.weatherapi.com/v1/current.json?key=" + String(apiKey) + "&q=" + String(location) + "&aqi=no";
    http.begin(wifiClient, url);
    
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      // Serial.println("Response:");
      // Serial.println(payload);
      
      // Parse the JSON response
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        float temp_f = doc["current"]["temp_f"]; // Extract temperature in Fahrenheit

        String condition = doc["current"]["condition"]["text"]; // Weather condition text
        String name  = doc["location"]["name"];
        String date = doc["location"]["localtime"];
        Serial.print("City Name;");
        Serial.println(name);
        Serial.print("Date'");
        Serial.println(date);
        Serial.print("Weather condition:::");
        Serial.println(condition);  // Print the condition text, e.g., "Partly cloudy"
        Serial.print("Temperature in Fahrenheit::");
        Serial.println(temp_f);


      } else {
        Serial.print("JSON deserialization failed: ");
        Serial.println(error.c_str());
      }
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(http.errorToString(httpCode).c_str());
    }
    
    http.end();
  } else {
    Serial.println("WiFi not connected.");
  }
  delay(3600000); // Wait 60 seconds before making another request
}
