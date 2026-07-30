/*******************************************************************************
 * touch_panel.h - Unified touch interface (GT911 or FT6236)
 ******************************************************************************/

#ifndef TOUCH_PANEL_H
#define TOUCH_PANEL_H

#include "config.h"

#if defined(ESP32_TOUCHDOWN)

#include <FT6236.h>

#define ROTATION_LEFT      (uint8_t)0
#define ROTATION_INVERTED  (uint8_t)1
#define ROTATION_RIGHT     (uint8_t)2
#define ROTATION_NORMAL    (uint8_t)3

class TP_Point {
public:
  TP_Point(void) : id(0), x(0), y(0), size(0) {}
  TP_Point(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _size)
    : id(_id), x(_x), y(_y), size(_size) {}

  uint8_t id;
  uint16_t x;
  uint16_t y;
  uint8_t size;
};

class TouchPanel {
public:
  TouchPanel(uint8_t sda, uint8_t scl, uint8_t irq, uint16_t width, uint16_t height)
    : _sda(sda), _scl(scl), _irq(irq), _width(width), _height(height) {}

  void begin() {
    pinMode(_irq, INPUT);
    _ft.begin(FT6236_DEFAULT_THRESHOLD, _sda, _scl);
  }

  void setRotation(uint8_t rot) {
    _rotation = rot;
  }

  void read() {
    isTouched = _ft.touched();

    for (uint8_t i = 0; i < 5; i++) {
      points[i] = TP_Point(0, 0, 0, 0);
    }

    if (!isTouched) {
      touches = 0;
      return;
    }

    touches = 1;
    TS_Point p = _ft.getPoint();
    uint16_t x = p.x;
    uint16_t y = p.y;
    applyRotation(x, y);
    points[0] = TP_Point(0, x, y, 1);
  }

  uint8_t touches = 0;
  bool isTouched = false;
  TP_Point points[5];

private:
  void applyRotation(uint16_t &x, uint16_t &y) {
    uint16_t temp;

    switch (_rotation) {
      case ROTATION_NORMAL:
        x = _width - x;
        y = _height - y;
        break;
      case ROTATION_LEFT:
        temp = x;
        x = _width - y;
        y = temp;
        break;
      case ROTATION_INVERTED:
        break;
      case ROTATION_RIGHT:
        temp = x;
        x = y;
        y = _height - temp;
        break;
      default:
        break;
    }
  }

  FT6236 _ft;
  uint8_t _sda;
  uint8_t _scl;
  uint8_t _irq;
  uint16_t _width;
  uint16_t _height;
  uint8_t _rotation = ROTATION_NORMAL;
};

#else

#include <TAMC_GT911.h>

class TouchPanel : public TAMC_GT911 {
public:
  TouchPanel(uint8_t sda, uint8_t scl, uint8_t irq, uint8_t rst, uint16_t width, uint16_t height)
    : TAMC_GT911(sda, scl, irq, rst, width, height) {}
};

#endif

#endif // TOUCH_PANEL_H