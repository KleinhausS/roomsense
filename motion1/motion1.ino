#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NETGEAR23";
const char* password =  "rustictree335"; 
const int ledPin = 2;

WebServer server(80); // Declaring the WebServer object

void handleRoot() {
  server.send(200, "text/html", "<h1>ESP32 Web Server</h1><p><a href=\"/on\">Turn On</a></p><p><a href=\"/off\">Turn Off</a></p>");
}
void handleOn() {
  digitalWrite(ledPin, HIGH);
   Serial.println("on");

  server.send(200, "text/plain", "LED turned on");
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "LED turned off");
   Serial.println("off");

}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Make sure LED is initially OFF

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print the IP address to the Serial Monitor

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
