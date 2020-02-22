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

uint8_t test_screen_rotation = 0;


void setup() {
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("Setup");
  tft.begin();

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

  tft.setTextColor(HX8357_GREEN);
  tft.setFont(ComicSansMS_14);
  tft.println("ComicSansMS 14");
  displayStuff(); 

  nextPage();
  
  tft.setTextColor(HX8357_WHITE);
  tft.setFont(DroidSans_14);
  tft.println("DroidSans_14");
  displayStuff();

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
  Serial.printf("\nRotation: %d\n", test_screen_rotation);
  tft.setRotation(test_screen_rotation);
  test_screen_rotation = (test_screen_rotation + 1) & 0x3;
  
  nextPage();

  tft.setTextColor(HX8357_WHITE);
  tft.setFont(Arial_14);
  tft.println("Arial_14");
  displayStuff1();

  tft.setTextColor(HX8357_YELLOW);
  tft.setFont(Arial_14_Bold);
  tft.println("ArialBold 14");
  displayStuff1();

  nextPage();

  tft.setTextColor(HX8357_GREEN);
  tft.setFont(ComicSansMS_14);
  tft.println("ComicSansMS 14");
  displayStuff1(); 

  tft.setTextColor(HX8357_WHITE);
  tft.setFont(DroidSans_14);
  tft.println("DroidSans_14");
  displayStuff1();

  nextPage();

  tft.setTextColor(HX8357_YELLOW);
  tft.setFont(Michroma_14);
  tft.println("Michroma_14");
  displayStuff1();

  nextPage();
  
  tft.setTextColor(HX8357_BLACK, HX8357_YELLOW);
  tft.setFont(Crystal_24_Italic);
  tft.println("CRYSTAL_24");
  displayStuff1();

  tft.setTextColor(HX8357_GREEN);
  tft.setFont(Chancery_24_Italic);
  tft.println("Chancery_24_Italic");
  displayStuff1();
  
  nextPage();

  //anti-alias font OpenSans
  tft.setTextColor(HX8357_RED, HX8357_YELLOW);
  tft.setFont(OpenSans24);
  tft.println("OpenSans 18");
  displayStuff1(); 

  nextPage();
}

uint32_t displayStuff()
{
  elapsedMillis elapsed_time = 0;
  tft.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  tft.println("abcdefghijklmnopqrstuvwxyz");
  tft.println("0123456789");
  tft.println("!@#$%^ &*()-");
  tft.println(); tft.println();
  return (uint32_t) elapsed_time;
}

uint32_t displayStuff1()
{
  elapsedMillis elapsed_time = 0;
  tft.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  tft.println("abcdefghijklmnopqrstuvwxyz");
  tft.println("0123456789");
  tft.println("!@#$%^ &*()-");
  static const char alternating_text[] = "AbCdEfGhIjKlMnOpQrStUvWxYz\raBcDeFgHiJkLmNoPqRsTuVwXyZ";
 
  for (uint8_t i = 0; i < sizeof(alternating_text); i++) {
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
