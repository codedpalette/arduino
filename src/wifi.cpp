#include "Arduino.h"
#include "SoftwareSerial.h"
#include "SparkFunESP8266WiFi.h"

const char mySSID[] = "Daniel";
const char myPSK[] = "314159265358";

char destServer[] = "sparkfun.com";

void setup() {
  Serial.begin(9600);
  while (esp8266.begin() != true) {
    Serial.println("Connecting to ESP8266...");
    delay(1000);
  }
  Serial.println("ESP8266 connected");

  if (esp8266.status() <= 0) {
    while (esp8266.connect(mySSID, myPSK) < 0) {
      Serial.println("Connecting to WiFi...");
      delay(1000);
    }
  }

  Serial.print("Pinging ");
  Serial.print(destServer);
  Serial.println("...");
}

void loop() {
  Serial.println(esp8266.ping(destServer));
  tone(3, 440, 500);
  delay(1000);
}