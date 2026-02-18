#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* ssid = "";
const char* password = "";

// Set up web server on port 80
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Set built-in LED as output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // OFF initially (inverted logic)

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/on", []() {
    digitalWrite(LED_BUILTIN, LOW); // ON (active low)
    server.send(200, "text/plain", "LED is ON");
  });

  server.on("/off", []() {
    digitalWrite(LED_BUILTIN, HIGH); // OFF
    server.send(200, "text/plain", "LED is OFF");
  });

  // Start server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
