#include <Arduino.h>
//#include <OneWire.h>
#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI, /*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2); // arbitrary selection of D3(=0), D4(=2), selected for default of GxEPD_Class
GxEPD_Class display(io, /*RST=D4*/ 2, /*BUSY=D2*/ 4); // default selection of D4(=2), D2(=4)

void setup() {
  Serial.begin(9600);
  Serial.println();
  display.init();
}

void showStuff()
{
  const char* name = "FreeMonoBold12pt7b";
  const GFXfont* f = &FreeMonoBold12pt7b;
  uint16_t box_x = 0;
  uint16_t box_y = 0;
  uint16_t box_w = 400;
  uint16_t box_h = 300;
  uint16_t cursor_y = box_y + 16;
  display.setRotation(2);
  display.setFont(f);
  display.setTextColor(GxEPD_WHITE);
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
  display.setCursor(box_x+15, box_y + 16);
  display.print("LOV & ORDEN");

  display.updateWindow(box_x, box_y, box_w, box_h, true);
}

void loop() {
  showStuff();
  display.update();
  delay(5000);
}
