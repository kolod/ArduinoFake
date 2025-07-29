#include "ArduinoFake.h"
#include "SPIFake.h"

void SPIClass::begin() { ArduinoFakeInstance(SPI)->begin(); };

void SPIClass::end() { ArduinoFakeInstance(SPI)->end(); };

void SPIClass::beginTransaction(SPISettings settings) {
  ArduinoFakeInstance(SPI)->beginTransaction(settings);
};

void SPIClass::endTransaction(void) {
  ArduinoFakeInstance(SPI)->endTransaction();
};

uint8_t SPIClass::transfer(uint8_t data) {
  return ArduinoFakeInstance(SPI)->transfer(data);
};

uint16_t SPIClass::transfer16(uint16_t data) {
  return ArduinoFakeInstance(SPI)->transfer16(data);
};

void SPIClass::transfer(void *buf, size_t count) {
  return ArduinoFakeInstance(SPI)->transfer(buf, count);
};

SPIClass SPI = SPIFakeProxy(ArduinoFakeInstance(SPI));
