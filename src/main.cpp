#include "Tetra.hpp"

#ifdef CORE2
#include <M5Core2.h>
TFT_eSprite sprite = TFT_eSprite(&M5.Lcd);
#else
#include <Button2.h>
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI    tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
Button2     btn1(BUTTON_1);
Button2     btn2(BUTTON_2);
#endif

Tetra<TFT_eSprite> tetra(sprite, TFT_HEIGHT, TFT_WIDTH);

int color = TFT_YELLOW;
int background = TFT_NAVY;

void setup()
{
  Serial.begin(115200);
  Serial.println("Tetra Start");
  randomSeed(analogRead(SEED_PIN));

#ifdef CORE2
  M5.begin();
  M5.Axp.SetLcdVoltage(3300);
  M5.BtnA.addHandler([](Event &e) {
    if (e == E_TAP) {
      Serial.println("Random Color (btn1)...");
      // color = default_4bit_palette[random(15) + 1];
    }
  });
  M5.BtnC.addHandler([](Event &e) {
    if (e == E_TAP) {
      Serial.println("Random Tetra (btn2)...");
      tetra.randomize();
    }
  });
#else
  tft.init();
  tft.setRotation(1);
  btn1.setTapHandler([](Button2 &b) {
    Serial.println("Random Color (btn1)...");
    color = default_4bit_palette[random(15) + 1];
  });
  btn2.setTapHandler([](Button2 &b) {
    Serial.println("Random Tetra (btn2)...");
    tetra.randomize();
  });
#endif
}

void loop()
{
#ifdef CORE2
  M5.update();
#else
  btn1.loop();
  btn2.loop();
#endif
  tetra.animate(color, background);
}