#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Waveshare_ILI9486.h>

Waveshare_ILI9486 Waveshield;

#define WIDTH 480
#define HEIGHT 320

#define BUTTON_PIN 2
#define PIN_RED A3
#define PIN_GREEN A4
#define PIN_BLUE A5

#define MAX_POTENTIOMETER_VALUE 906

void setup() {
  Serial.begin(9600);
  SPI.begin();

  Waveshield.begin();
  Waveshield.setRotation(1);

  pinMode(BUTTON_PIN, INPUT);
}

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue);
void debugColor(uint8_t red, uint8_t green, uint8_t blue);
void debugTsConfigData(TSConfigData data);

void loop() {
  uint8_t red =
      uint8_t(map(analogRead(PIN_RED), 0, MAX_POTENTIOMETER_VALUE, 0, 255));
  uint8_t green =
      uint8_t(map(analogRead(PIN_GREEN), 0, MAX_POTENTIOMETER_VALUE, 0, 255));
  uint8_t blue =
      uint8_t(map(analogRead(PIN_BLUE), 0, MAX_POTENTIOMETER_VALUE, 0, 255));
  uint16_t color = getColor(red, green, blue);
  // debugColor(red, green, blue);

  TSConfigData data = Waveshield.getTsConfigData();
  debugTsConfigData(data);

  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    Waveshield.fillScreen(0x0000);
  } else {
    TSPoint p = Waveshield.getPoint();
    Waveshield.normalizeTsPoint(p);
    Waveshield.fillCircle(p.x, p.y, 3, color);
  }
}

void debugTsConfigData(TSConfigData data) {
  Serial.print("Xmin: ");
  Serial.print(data.xMin);
  Serial.print(", Xmax: ");
  Serial.print(data.xMax);
  Serial.print(", Ymin: ");
  Serial.print(data.yMin);
  Serial.print(", Ymax: ");
  Serial.println(data.yMax);
}

void debugColor(uint8_t red, uint8_t green, uint8_t blue) {
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(", Green: ");
  Serial.print(green);
  Serial.print(", Blue: ");
  Serial.println(blue);
}

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  return (red << 11) | (green << 5) | blue;
}