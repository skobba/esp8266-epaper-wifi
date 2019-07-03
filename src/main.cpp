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


// *.entur.io - use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "C1 E1 33 B9 35 53 CF C3 22 B4 21 9C 6D 97 59 43 1B 78 C4 08";
const char* host = "api.entur.io";
const int httpsPort = 443;


// const char* wifiName = "Telenor7901rak";
// const char* wifiPass = "ixmlvfkyfegyo";

const char* wifiName = "Skobbis2";
const char* wifiPass = "r3plikant";


char input[] = "{\"name\":\"ArduinoJson\",\"stargazers\":{";

// char graphqlQuery[] = "{\r\n  \"trip\":(\r\n    \"from\": {\r\n        \"place\": \"NSR:StopPlace:6035\"\r\n        \"name\":\"Sinsen, Oslo\"\r\n    }\r\n    to: {\r\n        place:\"NSR:StopPlace:58366\"\r\n        name:\"Oslo, Oslo\"\r\n    }\r\n    numTripPatterns: 3\r\n    \"minimumTransferTime\": 180\r\n    \"arriveBy\": false\r\n  )\r\n\r\n  {\r\n    \"tripPatterns\" {\r\n      \"startTime\"\r\n      \"duration\"\r\n      \"legs\" {\r\n        \"line\" {\r\n          \"name\"\r\n        }\r\n      }\r\n    }\r\n  }\r\n}";


//Unexpected character ('t' (code 116)): was expecting double-quote to start field name
//char graphqlQuery[] = "{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo,Oslo\"}numTripPatterns:3minimumTransferTime:180arriveBy:false){tripPatterns{startTimedurationlegs{line{name}}}}}";

// char graphqlQuery[] = "{\r\n\"trip\"(\"from\":{\"place\":\"NSR:StopPlace:6035\" \"name\":\"Sinsen,Oslo\"}\"to\":{\"place\":\"NSR:StopPlace:58366\" \"name\":\"Oslo,Oslo\"}\"numTripPatterns\":3 \"minimumTransferTime\":180 \"arriveBy\":false){\"tripPatterns\"{\"startTimeduration\" \"legs\"{\"line\"{\"name\"}}}}}";

// Unexpected character ('t' (code 116)): was expecting double-quote to start field name
//char graphqlQuery[] = "{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen, Oslo\"}\nto:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"}numTripPatterns: 3\nminimumTransferTime: 180 arriveBy:false){tripPatterns {\nstartTime\nduration\nlegs {line {name}}}}}";

//No query found in body
char graphqlQuery[] = "{}";

//Can not construct instance of java.util.HashMap: no String-argument constructor/factory method to deserialize from String value ('{trip(from:{place:')
//char graphqlQuery[] = "\"{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen, Oslo\"}\nto:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"}numTripPatterns: 3\nminimumTransferTime: 180arriveBy:false){tripPatterns {\nstartTime\nduration\nlegs {line {name}}}}}\"";

// char graphqlQuery[] = "\"{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen, Oslo\"}\nto:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"}numTripPatterns: 3\nminimumTransferTime: 180arriveBy:false){tripPatterns {\nstartTime\nduration\nlegs {line {name}}}}}\"";


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
    String url = "/journey-planner/v2/graphql"
  
   */


  String url = "/journey-planner/v2/graphql";
  Serial.print("requesting URL: ");
  Serial.println(url);
  Serial.print("Content-Length: ");
  Serial.println(sizeof(graphqlQuery));
  Serial.println("Content:");
  Serial.println(graphqlQuery);

  // Make a HTTP request (1)
  // client.print(String("POST ") + url + " HTTP/1.1\r\n" +
  //              "Host: " + host + "\r\n" +
  //              "User-Agent: BuildFailureDetectorESP8266\r\n" +
  //              "Connection: close\r\n\r\n");

  client.println("POST /journey-planner/v2/graphql HTTP/1.1");
  client.println("Host: api.entur.io");
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(sizeof(graphqlQuery));
  client.println();
  client.println(graphqlQuery);
  client.println();

  // // Make a HTTP request (2)
  // client.println("GET " + url + " HTTP/1.1");
  // client.println("GET " + url + " HTTP/1.1");
  // client.println("Host: " + " ");
  // client.println("Connection: close\r\n\r\n");
  // client.println();


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