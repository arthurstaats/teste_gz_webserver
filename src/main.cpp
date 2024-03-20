// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "POCO F5";
const char* password = "oioioioi";

// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("index.html");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/gz", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("index2.html");
    request->send(SPIFFS, "/index2.html", String(), false);
  });
  
  // Route to load style.css file
  server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("bootstrap.min.css");
    request->send(SPIFFS, "/bootstrap.min.css", "text/css");
  });

  // Route to load style.css file
  server.on("/bootstrap.min.css.gz", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("bootstrap.min.css.gz");
    
    AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/bootstrap.min.css.gz", "text/css");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}