#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Waveshare_ILI9486.h>

Waveshare_ILI9486 Waveshield;

#define WIDTH 480
#define HEIGHT 320

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

void setup() {
  SPI.begin();
  Waveshield.begin();
}

void loop() {
  Waveshield.setRotation(1);
  // Waveshield.fillScreen(RED);
  // Waveshield.fillCircle(WIDTH / 2, HEIGHT / 2, HEIGHT / 2, BLUE);
  // delay(1000);

  // Get raw touchscreen values.
  TSPoint p = Waveshield.getPoint();

  // Remaps raw touchscreen values to screen co-ordinates.  Automatically
  // handles rotation!
  Waveshield.normalizeTsPoint(p);

  Waveshield.fillCircle(p.x, p.y, 3, BLUE);
}