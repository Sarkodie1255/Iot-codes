#include <WiFi.h>
#include <WebServer.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Sarkodie";
const char* password = "iamCa1255";

// Create a web server on port 80
WebServer server(80);

// Define LED pins
const int led1 = 2;   // Built-in LED or external LED
const int led2 = 4;   // Second LED

// HTML page
String htmlPage() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:Arial;text-align:center;margin-top:50px;}";
  html += ".btn{padding:15px 30px;margin:10px;font-size:20px;cursor:pointer;border:none;border-radius:10px;}";
  html += ".on{background-color:#4CAF50;color:white;}";
  html += ".off{background-color:#f44336;color:white;}</style></head>";
  html += "<body><h2>ESP32 Web Server</h2>";
  html += "<p><a href='/led1on'><button class='btn on'>LED 1 ON</button></a>";
  html += "<a href='/led1off'><button class='btn off'>LED 1 OFF</button></a></p>";
  html += "<p><a href='/led2on'><button class='btn on'>LED 2 ON</button></a>";
  html += "<a href='/led2off'><button class='btn off'>LED 2 OFF</button></a></p>";
  html += "</body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);

  // Set LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Connect to Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Route handlers
  server.on("/", []() {
    server.send(200, "text/html", htmlPage());
  });

  server.on("/led1on", []() {
    digitalWrite(led1, HIGH);
    server.send(200, "text/html", htmlPage());
  });

  server.on("/led1off", []() {
    digitalWrite(led1, LOW);
    server.send(200, "text/html", htmlPage());
  });

  server.on("/led2on", []() {
    digitalWrite(led2, HIGH);
    server.send(200, "text/html", htmlPage());
  });

  server.on("/led2off", []() {
    digitalWrite(led2, LOW);
    server.send(200, "text/html", htmlPage());
  });

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
