#include <M5Core2.h>
#include "Tetra.hpp"

#define SEED_PIN 36 // analog read to initialize random generator

Tetra tetra(TFT_HEIGHT,TFT_WIDTH);
int color = TFT_YELLOW;

void setup()
{
  Serial.begin(115200);
  Serial.println("Tetra Start");
  M5.begin();
  randomSeed(analogRead(SEED_PIN));
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
  tetra.animate(color);
}