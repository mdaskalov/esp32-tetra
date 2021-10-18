#include <M5Core2.h>
#include "Tetra.hpp"

#define SEED_PIN 36 // analog read to initialize random generator

int background = TFT_NAVY;
int color = TFT_YELLOW;

TFT_eSprite sprite = TFT_eSprite(&M5.Lcd);

Tetra tetra(TFT_HEIGHT,TFT_WIDTH);

void setup()
{
  M5.begin(true, false, true, false);

  Serial.println("Tetra Start");

  randomSeed(analogRead(SEED_PIN));
  sprite.createSprite(TFT_HEIGHT,TFT_WIDTH);
  sprite.fillSprite(TFT_NAVY);
}

void loop()
{
  M5.update();
  if(M5.BtnA.wasPressed()) {
    Serial.println("Random Color (btn1)...");
    //color = default_4bit_palette[random(15)+1];
  }
  if(M5.BtnC.wasPressed()) {
    Serial.println("Random Tetra (btn2)...");
    tetra.randomize();
  }
  tetra.animate(sprite,color,background);
  sprite.pushSprite(0, 0);
}