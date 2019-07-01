#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>
//#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


#define ONE_WIRE_BUS D4

//Web Server address to read/write from 
const char *host = "http://arduinojson.org/example.json";

const char* wifiName = "ssid";
const char* wifiPass = "pwd";

char graphqlQuery[] = "{\r\n  trip(\r\n    from: {\r\n        place: \"NSR:StopPlace:6035\"\r\n        name:\"Sinsen, Oslo\"\r\n    }\r\n    to: {\r\n        place:\"NSR:StopPlace:58366\"\r\n        name:\"Oslo, Oslo\"\r\n    }\r\n    numTripPatterns: 3\r\n    minimumTransferTime: 180\r\n    arriveBy: false\r\n  )\r\n\r\n  {\r\n    tripPatterns {\r\n      startTime\r\n      duration\r\n      legs {\r\n        line {\r\n          name\r\n        }\r\n      }\r\n    }\r\n  }\r\n}\r\n";


float tempC = 0;

GxIO_Class io(SPI, 15, 4, 5);
GxEPD_Class display(io,  5,  16);

void setup() {
  // Setup serial
  Serial.begin(9600);
  Serial.println();

  // Setup wifi
  delay(10);
  Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(wifiName);
 
  WiFi.begin(wifiName, wifiPass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP


  // Setup display
  display.init();

}



void show(String msg)
{
  const char* name = "FreeSansBold9pt7b";
  const GFXfont* f = &FreeSansBold9pt7b;
  uint16_t box_x = 0;
  uint16_t box_y = 0;
  uint16_t box_w = 400;
  uint16_t box_h = 300;
  uint16_t cursor_y = box_y + 16;
  display.setRotation(2);
  display.setFont(f);
  display.setTextColor(GxEPD_WHITE);
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
  //display.fillRect(0, 0, 380, 280, GxEPD_BLACK);

  display.setCursor(box_x+15, cursor_y+15);
  display.print(msg);
  display.updateWindow(box_x, box_y, box_w, box_h, true);
  //display.updateWindow(box_x, 200, box_w, 200, true);
}

void loop() {
  // show(WiFi.localIP().toString());
  // display.update();
  // delay(5000);


  HTTPClient http;    //Declare object of class HTTPClient
 
  Serial.print("Request Link:");
  Serial.println(host);
  
  http.begin(host);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload from server
 
  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code
 
  Serial.print("Returned data from Server:");
  Serial.println(payload);    //Print request response payload
  
  if(httpCode == 200)
  {
    /* 
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonBuffer jsonBuffer(capacity);
  
   // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(payload);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
  
  */

    // Decode JSON/Extract values
    Serial.println(F("Response:"));
    show("payload: " + payload);
    display.update();
    // Serial.println(root["sensor"].as<char*>());
    // Serial.println(root["time"].as<char*>());
    // Serial.println(root["data"][0].as<char*>());
    // Serial.println(root["data"][1].as<char*>());
  }
  else
  {
    Serial.println("Error in response");
  }
 
  http.end();  //Close connection
  
  delay(15000);  //GET Data at every 5 seconds

}