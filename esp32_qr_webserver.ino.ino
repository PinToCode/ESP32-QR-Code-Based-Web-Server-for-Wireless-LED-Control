#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "qr_gen.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define LED_PIN 13

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WebServer server(80);

//Replace with your WiFi
const char* ssid = "ssid";
const char* password = "passwd";

bool ledState = false;

//Webpage HTML
String getHTML() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{text-align:center;font-family:sans-serif;} button{padding:20px;font-size:20px;}</style>";
  html += "</head><body>";
  html += "<h2>ESP32 LED Control</h2>";

  if (ledState)
    html += "<p>LED is ON</p><a href='/off'><button>Turn OFF</button></a>";
  else
    html += "<p>LED is OFF</p><a href='/on'><button>Turn ON</button></a>";

  html += "</body></html>";
  return html;
}

// Handlers
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

void handleOn() {
  digitalWrite(LED_PIN, HIGH);
  ledState = true;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  digitalWrite(LED_PIN, LOW);
  ledState = false;
  server.sendHeader("Location", "/");
  server.send(303);
}

//QR display function
void displayQR(String data) {
  display.clearDisplay();

  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, 0, data.c_str());

  int pixelSize = 2;
  int offsetX = (SCREEN_WIDTH - (qrcode.size * pixelSize)) / 2;
  int offsetY = (SCREEN_HEIGHT - (qrcode.size * pixelSize)) / 2;

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        display.fillRect(
          offsetX + x * pixelSize,
          offsetY + y * pixelSize,
          pixelSize,
          pixelSize,
          SH110X_WHITE
        );
      }
    }
  }

  display.display();
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  Wire.begin(21, 22);

  if(!display.begin(0x3C)) {
    Serial.println("OLED failed");
    while(1);
  }

  display.clearDisplay();

  // 📡 Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  //Setup server
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();

  //Generate QR with IP
  String url = "http://" + WiFi.localIP().toString();
  displayQR(url);
}

void loop() {
  server.handleClient();
}