```
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_RST 7
#define TFT_DC  8
#define TFT_CS  9

#define CX      160
#define TOP_Y   35
#define BOT_Y   205

#define SAND 0xfd54

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

int16_t previousWidth[240];

void drawHourglassFrame() {
  tft.drawLine(85, TOP_Y, 235, TOP_Y, ILI9341_WHITE);
  tft.drawLine(85, BOT_Y, 235, BOT_Y, ILI9341_WHITE);

  tft.drawLine(85, TOP_Y, 145, 120, ILI9341_WHITE);
  tft.drawLine(235, TOP_Y, 175, 120, ILI9341_WHITE);

  tft.drawLine(145, 120, 85, BOT_Y, ILI9341_WHITE);
  tft.drawLine(175, 120, 235, BOT_Y, ILI9341_WHITE);
}

int glassHalfWidth(int y) {
  int distance = abs(y - 120);

  return 15 + (60L * distance) / 85 - 3;
}

int sandHalfWidth(int y, int topAmount,
                  int bottomAmount, bool stream) {
  int width = -1;

  if (topAmount > 0) {
    int height = map(topAmount, 1, 100, 1, 75);
    int surface = 120 - height;

    if (y >= surface && y <= 119) {
      width = glassHalfWidth(y);
    }
  }

  int bottom = BOT_Y - 4;
  int pileTop = bottom;

  if (bottomAmount > 0) {
    int height = map(bottomAmount, 1, 100, 1, 75);

    pileTop = bottom - height + 1;

    if (y >= pileTop && y <= bottom) {
      int pileWidth = (y - pileTop) * 2;

      width = min(pileWidth, glassHalfWidth(y));
    }
  }

  if (stream && topAmount > 0 &&
      y >= 120 && y <= pileTop) {
    width = max(width, 0);
  }

  return width;
}

void updateSand(int topAmount, int bottomAmount, bool stream) {
  topAmount = constrain(topAmount, 0, 100);
  bottomAmount = constrain(bottomAmount, 0, 100);

  for (int y = TOP_Y + 1; y < BOT_Y; y++) {
    int oldWidth = previousWidth[y];
    int newWidth = sandHalfWidth(
      y, topAmount, bottomAmount, stream
    );

    if (oldWidth == newWidth) {
      continue;
    }

    if (oldWidth < 0) {
      tft.drawFastHLine(
        CX - newWidth, y, newWidth * 2 + 1, SAND
      );
    } else if (newWidth < 0) {
      tft.drawFastHLine(
        CX - oldWidth, y, oldWidth * 2 + 1,
        ILI9341_BLACK
      );
    } else if (newWidth > oldWidth) {
      int difference = newWidth - oldWidth;

      tft.drawFastHLine(
        CX - newWidth, y, difference, SAND
      );

      tft.drawFastHLine(
        CX + oldWidth + 1, y, difference, SAND
      );
    } else {
      int difference = oldWidth - newWidth;

      tft.drawFastHLine(
        CX - oldWidth, y, difference, ILI9341_BLACK
      );

      tft.drawFastHLine(
        CX + newWidth + 1, y, difference, ILI9341_BLACK
      );
    }

    previousWidth[y] = newWidth;
  }
}

void setup() {

  
  tft.begin();
  tft.setRotation(1);

  tft.fillScreen(ILI9341_BLACK);

  tft.setTextWrap(false);

  for (int y = 0; y < 240; y++) {
    previousWidth[y] = -1;
  }

  drawHourglassFrame();
}

void loop() {
  updateSand(100, 0, false);

  delay(500);

  for (int amount = 100; amount >= 0; amount--) {
    updateSand(amount, 100 - amount, amount > 0);

    delay(80);
  }

  delay(1000);

  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(112, 220);
  tft.print("FLIPPING");

  delay(800);

  tft.fillRect(0, 218, 320, 22, ILI9341_BLACK);
}
```