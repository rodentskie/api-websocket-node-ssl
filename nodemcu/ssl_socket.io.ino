#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <SocketIoClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}

bool oneTime = true;
char toEmit[24];

void setup() {
  USE_SERIAL.begin(115200);

  USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFiMulti.addAP("Wee", "84753620A");

  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  webSocket.on("congrats", event);
  webSocket.begin("api-websocket-node-ssl.herokuapp.com");
}

void loop() {
  webSocket.loop();
  if (oneTime) {
    oneTime = false;

    DynamicJsonDocument doc(1024);

    doc["msg"] = "Thank you!";
    serializeJson(doc, toEmit);
    webSocket.emit("ok", toEmit);
  }
}