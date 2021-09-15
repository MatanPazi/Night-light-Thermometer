#include <TM1637Display.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 3
#define ONE_WIRE_BUS 2

const uint8_t SEG_ERR[] = {
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, // E
  SEG_E | SEG_G,                         // r
  SEG_E | SEG_G,                         // r
  0,                                     // space
};

// Create degree celsius symbol
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Degree symbol
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

TM1637Display display(CLK, DIO);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  display.setBrightness(0x02);
  sensors.begin();
  delay(200);
  if (sensors.getDS18Count() == 0)
    display.setSegments(SEG_ERR);
  else
    sensors.setResolution(12);
}

void loop() {
  if (sensors.getDS18Count() != 0) {
    sensors.requestTemperatures();
    int temp = sensors.getTempCByIndex(0);
    display.showNumberDec(temp, false, 2, 0);
    display.setSegments(celsius, 2, 2);
  }
  delay(10000);
}
