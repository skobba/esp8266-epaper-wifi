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

#include <WiFiClientSecure.h>

#define ONE_WIRE_BUS D4

// Web Server address to read/write from 
const char *hostSample = "http://arduinojson.org/example.json";
//const char *hostEntur = "https://api.entur.io/journey-planner/v2/graphql";
const char *hostEntur = "https://reisapi.ruter.no/Place/GetPlaces/grefsen";

// HTTPS
const char* host = "reisapi.ruter.no";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "55 80 FF 07 52 F1 64 1C 6A B6 08 F8 40 A3 F1 ED BF 2B 6B 5F";





const char* wifiName = "Telenor7901rak";
const char* wifiPass = "ixmlvfkyfegyo";

//char graphqlQuery[] = '{\"query\":\"{\ntrip(from:{place:\\"NSR:StopPlace:6035\\"name:\\"Sinsen,Oslo\\"}to:{place:\\"NSR:StopPlace:58366\\"name:\\"Oslo,Oslo\\"}¨numTripPatterns:3\nminimumTransferTime:180\narriveBy:false\n)\n\n{\ntripPatterns{\nstartTime\nduration\nlegs{\nline{\nname\n}\n}\n}\n}\n}\n\",\"variables\":null}';

//char input[] = "{\"name\":\"ArduinoJson\",\"stargazers\":{";

char input[] = "{\"name\":\"ArduinoJson\",\"stargazers\":{";

char graphqlQuery[] = "\"{\"query\":\"{\ntrip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo,Oslo\"}¨numTripPatterns:3\nminimumTransferTime:180\narriveBy:false\n)\n\n{\ntripPatterns{\nstartTime\nduration\nlegs{\nline{\nname\n}\n}\n}\n}\n}\n\",\"variables\":null}\"";


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


  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

    /*
    String url = "/Place/GetPlaces/grefsen";
    String url = "/line/GetLinesByStopID/3012120";
  
   */


  String url = "/line/GetLinesByStopID/3012120";
  Serial.print("requesting URL: ");
  Serial.println(url);

  // Make a HTTP request (1)
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  // Make a HTTP request (2)
  client.println("GET " + url + " HTTP/1.1");
  client.println("GET " + url + " HTTP/1.1");
  client.println("Host: " + " ");
  client.println("Connection: close\r\n\r\n");
  client.println();


  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
    //show("esp8266/Arduino CI has failed");
    //display.update();
  }
  
  show(line);
  display.update();

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");





  
  delay(15000);  //GET Data at every 5 seconds

}