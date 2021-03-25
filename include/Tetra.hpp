#pragma once

#include <Arduino.h>

class Axis {
  private:
    int maxPosition;
    int position;
    int direction;
    int velocity;

  public:
    int pos() const { return position; }
    void randomize() {
      randomPosition();
      randomDirection();
      randomVelocity();
    }
    void randomPosition() { position = random(maxPosition+1); }
    void randomDirection() { direction = random(2) ? -1 : 1; }
    void randomVelocity() { velocity = random(3)+1;}
    bool move() {
      position += direction * velocity;
      if (position < 0) {
        position = 0;
        direction = -direction;
        return true;
      }
      if (position > maxPosition) {
        position = maxPosition;
        direction = -direction;
        return true;
      }
      return false;
    }

    Axis(int max) {
      maxPosition = max;
      randomize();
    }
};

class TetraPoint {
  private:
    Axis x,y;

  public:
    int xPos() const { return x.pos(); }
    int yPos() const { return y.pos(); }
    void randomize() {
      x.randomize();
      y.randomize();
    }
    void move() {
      if (x.move()) {
        x.randomVelocity();
        y.randomVelocity();
      }
      if (y.move()) {
        x.randomVelocity();
        y.randomVelocity();
      }
    }

    TetraPoint(int xMax, int yMax): x(xMax), y(yMax) {}
};

class Tetra {
  private:
    TetraPoint a,b,c,d;

  public:
    void randomize() {
      a.randomize();
      b.randomize();
      c.randomize();
      d.randomize();
    }
    void move() {
      a.move();
      b.move();
      c.move();
      d.move();
    }
    void drawLine(TetraPoint &p1, TetraPoint &p2, uint32_t color) {
      M5.lcd.drawLine(p1.xPos(),p1.yPos(),p2.xPos(),p2.yPos(),color);
    }
    void drawTriangle(TetraPoint &a, TetraPoint &b, TetraPoint &c, uint32_t color)
    {
      M5.lcd.drawTriangle(a.xPos(),a.yPos(),b.xPos(),b.yPos(),c.xPos(),c.yPos(),color);
    }
    void draw(uint32_t color) {
      drawTriangle(a,b,c,color);
      drawLine(a,d,color);
      drawLine(b,d,color);
      drawLine(c,d,color);
    }
    void animate(uint32_t color) {
      //img.pushSprite(0, 0);
      //img.fillSprite(TFT_NAVY);
      M5.lcd.fillScreen(TFT_BLACK);
      move();
      draw(color);
    }

    Tetra(int xMax, int yMax) : a(xMax,yMax),b(xMax,yMax),c(xMax,yMax),d(xMax,yMax) {


      //img.createSprite(xMax, yMax);
    }
};
