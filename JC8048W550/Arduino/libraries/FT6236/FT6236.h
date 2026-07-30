/*!
 * FT6236.h - FocalTech capacitive touch controller
 * https://github.com/DustinWatts/FT6236
 */

#ifndef FT6236_H
#define FT6236_H

#include "Arduino.h"
#include <Wire.h>

#define FT6236_ADDR 0x38
#define FT6236_G_FT5201ID 0xA8
#define FT6236_REG_NUMTOUCHES 0x02

#define FT6236_NUM_X 0x33
#define FT6236_NUM_Y 0x34

#define FT6236_REG_MODE 0x00
#define FT6236_REG_CALIBRATE 0x02
#define FT6236_REG_WORKMODE 0x00
#define FT6236_REG_FACTORYMODE 0x40
#define FT6236_REG_THRESHHOLD 0x80
#define FT6236_REG_POINTRATE 0x88
#define FT6236_REG_FIRMVERS 0xA6
#define FT6236_REG_CHIPID 0xA3
#define FT6236_REG_VENDID 0xA8

#define FT6236_VENDID 0x11
#define FT6206_CHIPID 0x06
#define FT6236_CHIPID 0x36
#define FT6236U_CHIPID 0x64

#define FT6236_DEFAULT_THRESHOLD 128

class TS_Point
{
public:
  TS_Point(void);
  TS_Point(int16_t x, int16_t y, int16_t z);

  bool operator==(TS_Point);
  bool operator!=(TS_Point);

  int16_t x;
  int16_t y;
  int16_t z;
};

class FT6236
{
public:
  FT6236(void);
  void debug(void);
  boolean begin(uint8_t thresh = FT6236_DEFAULT_THRESHOLD, int8_t sda = -1, int8_t scl = -1);
  uint8_t touched(void);
  TS_Point getPoint(uint8_t n = 0);
  void readData(void);
  uint8_t touches;
  uint16_t touchX[2], touchY[2], touchID[2];

private:
  void writeRegister8(uint8_t reg, uint8_t val);
  uint8_t readRegister8(uint8_t reg);
};

#endif
