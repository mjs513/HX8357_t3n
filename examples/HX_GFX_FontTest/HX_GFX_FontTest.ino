#include <Adafruit_GFX.h>

#include "SPI.h"
#include "HX8357_t3n.h"

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
HX8357_t3n tft = HX8357_t3n(TFT_CS, TFT_DC,8);


#include <ILI9341_t3n_font_ComicSansMS.h>
#include "Fonts/FreeSansOblique12pt7b.h"

void setup() {
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("Setup");
  tft.begin();

  tft.setRotation(1);
  tft.fillScreen(HX8357_BLACK);

  tft.setTextColor(HX8357_WHITE);
  tft.println("Test of the default font");
  tft.println();

  tft.setTextColor(HX8357_WHITE, HX8357_BLUE);
  tft.setFont(ComicSansMS_12);
  tft.println("Opaque ILI font ComicSansMS_12");
  tft.println();

  tft.setTextColor(HX8357_GREEN);
  tft.println("Transparent ILIComicSansMS_12");
  tft.println();

  tft.setTextColor(HX8357_WHITE, HX8357_RED);
  tft.setFont(&FreeSansOblique12pt7b);
  tft.println("Opaque GFX FreeSansOblique12pt");
  int cursor_x = tft.getCursorX();
  int cursor_y = tft.getCursorY();
  tft.fillRect(cursor_x, cursor_y, tft.width(), 20, HX8357_YELLOW);
  tft.setTextColor(HX8357_BLUE);
  tft.println("Transparent GFX");

  tft.setFont();
  tft.setTextColor(HX8357_GREEN);
  tft.setTextSize(3);
  tft.println("This is default font:");
  //tft.setFontSpacing(1);//now give 5 pix extra spacing between chars
  tft.println("ABCDEF 1 2 3 4 5 6 7");

}

void loop()
{  }
