/*
Copyright (c) 2018 FackThatShit.  All right reserved.
Modified by FackThatShit, February 2018
*/

//Include Libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

//Define GPIO's
#define Red D0
#define Green D1
#define Blue D2

//Set Pulse Wide Modulation
#define PWMRANGE 255

//Declared Functions
void setup();
void loop();
void handleGenericArgs();
void handleSpecificArg();

//Set WiFi Variables
const char* ssid = "YOUR_WIFI_SSID";
const char* pass = "YOUR_WIFI_PASS";

//set ESP-Web-Server at port 80
ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect...");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Set DNS-Type
  if (!MDNS.begin("esp.app")) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("MDNS responder started");

  server.on("/genericArgs", handleGenericArgs);
  server.on("/specificArgs", handleSpecificArg);

  server.begin();
  Serial.println("Server listening on:");
  Serial.println("http://esp.app/");
}

void loop() {
  server.handleClient();
}

void handleGenericArgs() {
  String message = "Number of args received: ";
  message += server.args();
  message += "\n";

  for (int i = 0; i < server.args(); i++) {
    message += "Arg nº" + (String)i + " –> ";
    message += server.argName(i) + ": ";
    message += server.arg(i) + "\n";
  }

  String red = server.arg(2);
  String blue = server.arg(0);
  String green = server.arg(1);
  analogWrite(D0, red.toInt());
  analogWrite(D1, green.toInt());
  analogWrite(D2, blue.toInt());

  server.send(200, "text/plain", message);
}

void handleSpecificArg() {

  String message = "";

  if (server.arg("specific")== "") {

      message = "specific not found";

    }else{

      message = "Specific Argument = ";
      message += server.arg("specific");

}

  server.send(200, "text/plain", message);
}
