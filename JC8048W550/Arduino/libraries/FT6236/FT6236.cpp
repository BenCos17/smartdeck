#include "Arduino.h"
#include "FT6236.h"
#include <Wire.h>

FT6236::FT6236() { touches = 0; }

boolean FT6236::begin(uint8_t thresh, int8_t sda, int8_t scl)
{
  if (sda != -1 && scl != -1) {
    Wire.begin(sda, scl);
  } else {
    Wire.begin();
  }

  writeRegister8(FT6236_REG_THRESHHOLD, thresh);

  if (readRegister8(FT6236_REG_VENDID) != FT6236_VENDID) {
    return false;
  }

  uint8_t id = readRegister8(FT6236_REG_CHIPID);
  if ((id != FT6236_CHIPID) && (id != FT6236U_CHIPID) && (id != FT6206_CHIPID)) {
    return false;
  }

  return true;
}

uint8_t FT6236::touched(void)
{
  uint8_t n = readRegister8(FT6236_REG_NUMTOUCHES);
  if (n > 2) {
    n = 0;
  }
  return n;
}

TS_Point FT6236::getPoint(uint8_t n)
{
  readData();
  if ((touches == 0) || (n > 1)) {
    return TS_Point(0, 0, 0);
  }
  return TS_Point(touchX[n], touchY[n], 1);
}

void FT6236::readData(void)
{
  uint8_t i2cdat[16];
  Wire.beginTransmission(FT6236_ADDR);
  Wire.write((byte)0);
  Wire.endTransmission();

  Wire.requestFrom((byte)FT6236_ADDR, (byte)16);
  for (uint8_t i = 0; i < 16; i++) {
    i2cdat[i] = Wire.read();
  }

  touches = i2cdat[0x02];
  if ((touches > 2) || (touches == 0)) {
    touches = 0;
  }

  for (uint8_t i = 0; i < 2; i++) {
    touchX[i] = i2cdat[0x03 + i * 6] & 0x0F;
    touchX[i] <<= 8;
    touchX[i] |= i2cdat[0x04 + i * 6];
    touchY[i] = i2cdat[0x05 + i * 6] & 0x0F;
    touchY[i] <<= 8;
    touchY[i] |= i2cdat[0x06 + i * 6];
    touchID[i] = i2cdat[0x05 + i * 6] >> 4;
  }
}

uint8_t FT6236::readRegister8(uint8_t reg)
{
  Wire.beginTransmission(FT6236_ADDR);
  Wire.write((byte)reg);
  Wire.endTransmission();

  Wire.requestFrom((byte)FT6236_ADDR, (byte)1);
  return Wire.read();
}

void FT6236::writeRegister8(uint8_t reg, uint8_t val)
{
  Wire.beginTransmission(FT6236_ADDR);
  Wire.write((byte)reg);
  Wire.write((byte)val);
  Wire.endTransmission();
}

void FT6236::debug(void)
{
  Serial.print("Vend ID: 0x");
  Serial.println(readRegister8(FT6236_REG_VENDID), HEX);
  Serial.print("Chip ID: 0x");
  Serial.println(readRegister8(FT6236_REG_CHIPID), HEX);
  Serial.print("Firm V: ");
  Serial.println(readRegister8(FT6236_REG_FIRMVERS));
  Serial.print("Point Rate Hz: ");
  Serial.println(readRegister8(FT6236_REG_POINTRATE));
  Serial.print("Thresh: ");
  Serial.println(readRegister8(FT6236_REG_THRESHHOLD));
}

TS_Point::TS_Point(void) { x = y = z = 0; }

TS_Point::TS_Point(int16_t _x, int16_t _y, int16_t _z)
{
  x = _x;
  y = _y;
  z = _z;
}

bool TS_Point::operator==(TS_Point p1)
{
  return ((p1.x == x) && (p1.y == y) && (p1.z == z));
}

bool TS_Point::operator!=(TS_Point p1)
{
  return ((p1.x != x) || (p1.y != y) || (p1.z != z));
}
