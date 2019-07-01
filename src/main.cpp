#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#define ONE_WIRE_BUS D4

float tempC = 0;

GxIO_Class io(SPI, 15, 4, 5);
GxEPD_Class display(io,  5,  16);

void setup() {
  Serial.begin(9600);
  Serial.println();
  display.init();
}



void show()
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
  //display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
  display.fillRect(0, 0, 380, 280, GxEPD_BLACK);

  display.setCursor(box_x+15, cursor_y+88);
  display.print("dette er en test");
  display.updateWindow(box_x, box_y, box_w, box_h, true);
}

void loop() {
  show();
  display.update();
  delay(5000);
}