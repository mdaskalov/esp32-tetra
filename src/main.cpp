#include <TFT_eSPI.h>
#include <SPI.h>
#include <Ticker.h>
#include <Button2.h>
#include "Tetra.hpp"

#define BUTTON_1 35
#define BUTTON_2 0
#define SEED_PIN 36 // analog read to initialize random generator

TFT_eSPI tft = TFT_eSPI();
Ticker animationTicker;
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
Tetra tetra(tft,TFT_WIDTH,TFT_HEIGHT);
int color = TFT_YELLOW;

void setup()
{
  Serial.begin(115200);
  Serial.println("Tetra Start");
  randomSeed(analogRead(SEED_PIN));
  tft.init();
  btn1.setTapHandler([](Button2 & b) {
    Serial.println("Random Color (btn1)...");
    color = default_4bit_palette[random(15)+1];
  });
  btn2.setTapHandler([](Button2 & b) {
    Serial.println("Random Tetra (btn2)...");
    tetra.randomize();
  });
  animationTicker.attach_ms(33,[] {
    tetra.animate(color);
  });
}

void loop()
{
  btn1.loop();
  btn2.loop();
}