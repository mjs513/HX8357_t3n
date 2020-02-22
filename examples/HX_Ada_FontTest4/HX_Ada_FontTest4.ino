#include <Adafruit_GFX.h>



#include "SPI.h"
#include "HX8357_t3n.h"

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
HX8357_t3n tft = HX8357_t3n(TFT_CS, TFT_DC,8);

#include "font_Arial.h"
#include "font_ArialBold.h"
#include "font_ComicSansMS.h"
#include "font_OpenSans.h"
#include "font_DroidSans.h"
#include "font_Michroma.h"
#include "font_Crystal.h"
#include "font_ChanceryItalic.h"

#define CENTER HX8357_t3n::CENTER

// maybe a few GFX FOnts?
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

typedef struct {
  const ILI9341_t3_font_t *ili_font;
  const GFXfont       *gfx_font;
  const char          *font_name;
  uint16_t            font_fg_color;
  uint16_t            font_bg_color;
} ili_fonts_test_t;


const ili_fonts_test_t font_test_list[] = {
  {&Arial_14, nullptr,  "Arial_14", HX8357_WHITE, HX8357_WHITE},
  {&Arial_14_Bold, nullptr,  "ArialBold 14", HX8357_YELLOW, HX8357_YELLOW},
  {&ComicSansMS_14, nullptr,  "ComicSansMS 14", HX8357_GREEN, HX8357_GREEN},
  {&DroidSans_14, nullptr,  "DroidSans_14", HX8357_WHITE, HX8357_WHITE},
  {&Michroma_14, nullptr,  "Michroma_14", HX8357_YELLOW, HX8357_YELLOW},
  {&Crystal_24_Italic, nullptr,  "CRYSTAL_24", HX8357_BLACK, HX8357_YELLOW},
  {&Chancery_24_Italic, nullptr,  "Chancery_24_Italic", HX8357_GREEN, HX8357_GREEN},
  {&OpenSans24, nullptr,  "OpenSans 18", HX8357_RED, HX8357_YELLOW},
  {nullptr, &FreeMonoBoldOblique12pt7b,  "GFX FreeMonoBoldOblique12pt7b", HX8357_WHITE, HX8357_WHITE},
  {nullptr, &FreeMonoBoldOblique12pt7b,  "GFX FreeMonoBoldOblique12pt7b", HX8357_RED, HX8357_YELLOW},
  {nullptr, &FreeSerif12pt7b,  "GFX FreeSerif12pt7b", HX8357_WHITE, HX8357_WHITE},
  {nullptr, &FreeSerif12pt7b,  "GFX FreeSerif12pt7b", HX8357_RED, HX8357_YELLOW},

} ;



uint8_t test_screen_rotation = 0;


void setup() {
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("Setup");
  //  begin display: Choose from: HX8357_480x272, HX8357_800x480, HX8357_800x480ALT, Adafruit_480x272, Adafruit_800x480
  tft.begin(30000000u);

  tft.setRotation(4);
  tft.fillWindow(HX8357_BLACK);

  tft.setTextColor(HX8357_WHITE);
  tft.setFont(Arial_14);
  tft.println("Arial_14");
  displayStuff();

  tft.setTextColor(HX8357_YELLOW);
  tft.setFont(Arial_14_Bold);
  tft.println("ArialBold 14");
  displayStuff();
  nextPage();
  tft.setTextColor(HX8357_GREEN);
  tft.setFont(ComicSansMS_14);
  tft.println("ComicSansMS 14");
  displayStuff();


  tft.setTextColor(HX8357_WHITE);
  tft.setFont(DroidSans_14);
  tft.println("DroidSans_14");
  displayStuff();
  nextPage();

  tft.setTextColor(HX8357_YELLOW);
  tft.setFont(Michroma_14);
  tft.println("Michroma_14");
  displayStuff();

  tft.setTextColor(HX8357_BLACK, HX8357_YELLOW);
  tft.setFont(Crystal_24_Italic);
  tft.println("CRYSTAL_24");
  displayStuff();

  nextPage();

  tft.setTextColor(HX8357_GREEN);
  tft.setFont(Chancery_24_Italic);
  tft.println("Chancery_24_Italic");
  displayStuff();

  //anti-alias font OpenSans
  tft.setTextColor(HX8357_RED, HX8357_YELLOW);
  tft.setFont(OpenSans24);
  tft.println("OpenSans 18");
  displayStuff();

  Serial.println("Basic Font Display Complete");
  Serial.println("Loop test for alt colors + font");
}

void loop()
{
  tft.setFont(Arial_12);
  Serial.printf("\nRotation: %d\n", test_screen_rotation);
  tft.setRotation(test_screen_rotation);
  tft.fillWindow(HX8357_RED);
  tft.setCursor(CENTER, CENTER);
  tft.printf("Rotation: %d", test_screen_rotation);
  test_screen_rotation = (test_screen_rotation + 1) & 0x3;
  /*  tft.setCursor(200, 300);
    Serial.printf("  Set cursor(200, 300), retrieved(%d %d)",
                  tft.getCursorX(), tft.getCursorY());
  */
  tft.setCursor(25, 25);
  tft.write('0');
  tft.setCursor(tft.width() - 25, 25);
  tft.write('1');
  tft.setCursor(25, tft.height() - 25);
  tft.write('2');
  tft.setCursor(tft.width() - 25, tft.height() - 25);
  tft.write('3');

  for (uint8_t font_index = 0; font_index < (sizeof(font_test_list) / sizeof(font_test_list[0])); font_index++) {
    nextPage();
    if (font_test_list[font_index].font_fg_color != font_test_list[font_index].font_bg_color)
      tft.setTextColor(font_test_list[font_index].font_fg_color, font_test_list[font_index].font_bg_color);
    else
      tft.setTextColor(font_test_list[font_index].font_fg_color);
    if (font_test_list[font_index].ili_font) tft.setFont(*font_test_list[font_index].ili_font);
    else tft.setFont(font_test_list[font_index].gfx_font);
    tft.println(font_test_list[font_index].font_name);
    displayStuff1();
  }
  nextPage();
}

uint32_t displayStuff()
{
  elapsedMillis elapsed_time = 0;
  tft.println("ABCDEFGHIJKLM");
  tft.println("nopqrstuvwxyz");
  tft.println("0123456789");
  tft.println("!@#$%^ &*()-");
  tft.println(); tft.println();
  return (uint32_t) elapsed_time;
}

uint32_t displayStuff1()
{
  elapsedMillis elapsed_time = 0;
  tft.println("ABCDEFGHIJKLM");
  tft.println("nopqrstuvwxyz");
  tft.println("0123456789");
  tft.println("!@#$%^ &*()-");

  int16_t cursorX = tft.getCursorX();
  int16_t cursorY = tft.getCursorY();

  uint16_t width = tft.width();
  uint16_t height = tft.height();
  Serial.printf("DS1 (%d,%d) %d %d\n", cursorX, cursorY, width, height);
  uint16_t rect_x = width / 2 - 50;
  uint16_t rect_y = height - 50;
  tft.drawRect(rect_x, rect_y, 100, 40, HX8357_WHITE);
  for (uint16_t y = rect_y + 5; y < rect_y + 40; y += 5)
    tft.drawFastHLine(rect_x + 1, y, 98, HX8357_PINK);
  for (uint16_t x = rect_x + 5; x < rect_x + 100; x += 5)
    tft.drawFastVLine(x, rect_y + 1, 38, HX8357_PINK);
  tft.setCursor(width / 2, height - 30, true);
  tft.print("Center");

  // Lets try again with CENTER X keyword.
  rect_y -= 60;
  tft.drawRect(rect_x, rect_y, 100, 40, HX8357_PINK);
  for (uint16_t y = rect_y + 5; y < rect_y + 40; y += 5)
    tft.drawFastHLine(rect_x + 1, y, 98, HX8357_CYAN);
  for (uint16_t x = rect_x + 5; x < rect_x + 100; x += 5)
    tft.drawFastVLine(x, rect_y + 1, 38, HX8357_CYAN);
  tft.setCursor(CENTER, rect_y);
  tft.print("XCENTR");

  // Lets try again with CENTER Y keyword.
  rect_x = 50;
  rect_y = tft.height() / 2 - 25;
  tft.drawRect(rect_x, rect_y, 100, 50, HX8357_CYAN);
  for (uint16_t y = rect_y + 5; y < rect_y + 50; y += 5)
    tft.drawFastHLine(rect_x + 1, y, 98, HX8357_PINK);
  for (uint16_t x = rect_x + 5; x < rect_x + 100; x += 5)
    tft.setCursor(50, CENTER);
  tft.print("YCENTR");



  tft.setCursor(cursorX, cursorY);
  static const char alternating_text[] = "AbCdEfGhIjKlM\rNoPqRsTuVwXyZ";

  for (uint8_t i = 0; i < (sizeof(alternating_text) - 1); i++) {
    if (i & 1) tft.setTextColor(HX8357_WHITE, HX8357_RED);
    else tft.setTextColor(HX8357_YELLOW, HX8357_BLUE);
    tft.write(alternating_text[i]);
  }

  tft.println(); tft.println();



  return (uint32_t) elapsed_time;
}

void nextPage()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;

  tft.fillWindow(HX8357_BLACK);
  tft.setCursor(0, 0);
}
