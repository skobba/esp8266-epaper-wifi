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
/*
Expires: Wednesday, 11 March 2020 at 13:00:00 Central European Standard Time
C1 E1 33 B9 35 53 CF C3 22 B4 21 9C 6D 97 59 43 1B 78 C4 08

!!!!!!!!!!!!!!!!!! 
USE INLINE CERT - https://www.youtube.com/watch?v=Wm1xKj4bKsY


 */
const char fingerprint[] PROGMEM = "C1 E1 33 B9 35 53 CF C3 22 B4 21 9C 6D 97 59 43 1B 78 C4 08";
const char* host = "api.entur.io";
const int httpsPort = 443;

const char* wifiName = "Telenor7901rak";
const char* wifiPass = "ixmlvfkyfegyo";



// const char* wifiName = "ssid";
// const char* wifiPass = "paw";


// char input[] = "{\"name\":\"ArduinoJson\",\"stargazers\":{";




// char graphqlQuery[] = "{\r\n  \"trip\":(\r\n    \"from\": {\r\n        \"place\": \"NSR:StopPlace:6035\"\r\n        \"name\":\"Sinsen, Oslo\"\r\n    }\r\n    to: {\r\n        place:\"NSR:StopPlace:58366\"\r\n        name:\"Oslo, Oslo\"\r\n    }\r\n    numTripPatterns: 3\r\n    \"minimumTransferTime\": 180\r\n    \"arriveBy\": false\r\n  )\r\n\r\n  {\r\n    \"tripPatterns\" {\r\n      \"startTime\"\r\n      \"duration\"\r\n      \"legs\" {\r\n        \"line\" {\r\n          \"name\"\r\n        }\r\n      }\r\n    }\r\n  }\r\n}";


//Unexpected character ('t' (code 116)): was expecting double-quote to start field name
//char graphqlQuery[] = "{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen,Oslo\"}to:{place:\"NSR:StopPlace:58366\"name:\"Oslo,Oslo\"}numTripPatterns:3minimumTransferTime:180arriveBy:false){tripPatterns{startTimedurationlegs{line{name}}}}}";

// char graphqlQuery[] = "{\r\n\"trip\"(\"from\":{\"place\":\"NSR:StopPlace:6035\" \"name\":\"Sinsen,Oslo\"}\"to\":{\"place\":\"NSR:StopPlace:58366\" \"name\":\"Oslo,Oslo\"}\"numTripPatterns\":3 \"minimumTransferTime\":180 \"arriveBy\":false){\"tripPatterns\"{\"startTimeduration\" \"legs\"{\"line\"{\"name\"}}}}}";

// Unexpected character ('t' (code 116)): was expecting double-quote to start field name
//char graphqlQuery[] = "{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen, Oslo\"}\nto:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"}numTripPatterns: 3\nminimumTransferTime: 180 arriveBy:false){tripPatterns {\nstartTime\nduration\nlegs {line {name}}}}}";

//No query found in body
//const char* graphqlQuery = "{\"query\":\"{bikeRentalStationsByBbox(minimumLatitude:59.9\\nmaximumLatitude:60\\nminimumLongitude:10.7\\nmaximumLongitude:10.8\\n)\\n{id\\nname\\nbikesAvailable\\nspacesAvailable}}\",\"variables\":null}";

//Can not construct instance of java.util.HashMap: no String-argument constructor/factory method to deserialize from String value ('{trip(from:{place:')
//char graphqlQuery[] = "\"{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen, Oslo\"}\nto:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"}numTripPatterns: 3\nminimumTransferTime: 180arriveBy:false){tripPatterns {\nstartTime\nduration\nlegs {line {name}}}}}\"";

// char graphqlQuery[] = "\"{trip(from:{place:\"NSR:StopPlace:6035\"name:\"Sinsen, Oslo\"}\nto:{place:\"NSR:StopPlace:58366\"name:\"Oslo, Oslo\"}numTripPatterns: 3\nminimumTransferTime: 180arriveBy:false){tripPatterns {\nstartTime\nduration\nlegs {line {name}}}}}\"";
//





// SinsenT
// const char* graphqlQuery = "{\"query\":\"{trip(from:{place:\\n\"GNSR:StopPlace:6035\"\\nname:\\n\"Sinsen,Oslo\"\\n}to:{place:\\n\"NSR:StopPlace:58366\"\\nname:\\n\"Oslo,Oslo\"\\n}numTripPatterns:3\\nminimumTransferTime:180\\narriveBy:false){tripPatterns{startTime\\nduration\\nlegs{line{name}}}}}\",\"variables\":null}";
/*
Unexpected character ('G' (code 71)): was expecting comma to separate Object entries
 at [Source: org.glassfish.jersey.message.internal.ReaderInterceptorExecutor$UnCloseableInputStream@632d23bb; line: 1, column: 33] */
 

// Frode 1 (virker) (no newline, "query", double esc)
//const char* graphqlQuery = "{\"query\":\"{bikeRentalStationsByBbox(minimumLatitude:59.9\\nmaximumLatitude:60\\nminimumLongitude:10.7\\nmaximumLongitude:10.8\\n)\\n{id\\nname\\nbikesAvailable\\nspacesAvailable}}\",\"variables\":null}";


//Frode 2
//char graphqlQuery[] = "{\"query\":\"{\\ntrip(from:{place:\\\"NSR:StopPlace:6035\\\"name:\\\"Sinsen,Oslo\\\"}to:{place:\\\"NSR:StopPlace:58366\\\"name:\\\"Oslo,Oslo\\\"}\nnumTripPatterns:3\\nminimumTransferTime:180\\narriveBy:false\\n)\\n\\n{\\ntripPatterns{\\nstartTime\\nduration\\nlegs{\\nline{\\nname\\n}\\n}\\n}\\n}\\n}\\n\",\"variables\":null}";
// Res: Illegal unquoted character ((CTRL-CHAR, code 10)): has to be escaped using backslash to be included in string value

//Frode 3
//char graphqlQuery[] = "{\"query\":\"{\\ntrip(from:{place:\\\"NSR:StopPlace:6035\\\"name:\\\"Sinsen,Oslo\\\"}to:{place:\\\"NSR:StopPlace:58366\\\"name:\\\"Oslo,Oslo\\\"}numTripPatterns:3\\nminimumTransferTime:180\\narriveBy:false\\n)\\n\\n{\\ntripPatterns{\\nstartTime\\nduration\\nlegs{\\nline{\\nname\\n}\\n}\\n}\\n}\\n}\\n\",\"variables\":null}"; 
// Res: Illegal unquoted character ((CTRL-CHAR, code 10)): has to be escaped using backslash to be included in string value

//FromSinsen-Tiny (with start time)
//char graphqlQuery[] = "{\"query\":\"{\\nstopPlace(id:\\\"NSR:StopPlace:6035\\\"){id\\nname\\nestimatedCalls(startTime:\\\"2019-07-13T09:00:00+0200\\\"numberOfDepartures:2){expectedDepartureTime\\ndestinationDisplay{frontText}quay{id}}}}\\n\",\"variables\":null}"; 

//FromSinsen-Tiny (withOUT!!!start time)
char graphqlQuery[] = "{\"query\":\"{\\nstopPlace(id:\\\"NSR:StopPlace:6035\\\"){id\\nname\\nestimatedCalls(numberOfDepartures:5){expectedDepartureTime\\ndestinationDisplay{frontText}quay{id}}}}\\n\",\"variables\":null}"; 

/*
HVORFOR ER DET KUN 5 LINJER MED DENNE SPØRRINGEN!?!?!?!?!!??!

{
	lines(
    transportModes:metro
  ) {
    name
  }
}


 */

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

  String url = "/journey-planner/v2/graphql";
  String content = String("POST /journey-planner/v2/graphql HTTP/1.1\n");
  content += "Host: api.entur.io\n";
  content += "Cache-Control: no-cache\n";
  content += "Content-Type: application/json\n";
  content += "Content-Length: " + String(strlen(graphqlQuery)) + String("\n");
  content += "\n";
  content += graphqlQuery;

  //Serial.println(String("Dette sendes: ") + content);
  client.print(content);


  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  String chunk = "";
  int limit = 1;
  String response="";

Serial.println(response);
 // String line = client.readStringUntil('z');
    do {
    if (client.connected()) {
      client.setTimeout(2000);
      chunk = client.readStringUntil('\n');
      response += chunk;
      Serial.println(chunk);
    }
  } while (chunk.length() > 0 && ++limit < 100);


  // Reading JSON
  const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 30;
  DynamicJsonDocument doc(capacity);

  //const char* json = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.75608,2.302038]}";
/*
#### RAW ####
  "data": {
    "stopPlace": {
      "id": "NSR:StopPlace:6035",
      "name": "Sinsen",


{"data":{"stopPlace":{"id":"NSR:StopPlace:6035","name":"Sinsen","estimatedCalls":[{"expectedDepartureTime":"2019-07-13T09:02:00+0200","destinationDisplay":{"frontText":"Vestli"},"quay":{"id":"NSR:Quay:11078"}},{"expectedDepartureTime":"2019-07-13T09:09:00+0200","destinationDisplay":{"frontText":"Bergkrystallen via Storo"},"quay":{"id":"NSR:Quay:11077"}}]}}}

#### ECSAPED ####
{\"data\":{\"stopPlace\":{\"id\":\"NSR:StopPlace:6035\",\"name\":\"Sinsen\",\"estimatedCalls\":[{\"expectedDepartureTime\":\"2019-07-13T09:02:00+0200\",\"destinationDisplay\":{\"frontText\":\"Vestli\"},\"quay\":{\"id\":\"NSR:Quay:11078\"}},{\"expectedDepartureTime\":\"2019-07-13T09:09:00+0200\",\"destinationDisplay\":{\"frontText\":\"Bergkrystallen via Storo\"},\"quay\":{\"id\":\"NSR:Quay:11077\"}}]}}}

*/
  const char* jsonFromEntur = "{\"data\":{\"stopPlace\":{\"id\":\"NSR:StopPlace:6035\",\"name\":\"Sinsen\",\"estimatedCalls\":[{\"expectedDepartureTime\":\"2019-07-13T09:02:00+0200\",\"destinationDisplay\":{\"frontText\":\"Vestli\"},\"quay\":{\"id\":\"NSR:Quay:11078\"}},{\"expectedDepartureTime\":\"2019-07-13T09:09:00+0200\",\"destinationDisplay\":{\"frontText\":\"Bergkrystallen via Storo\"},\"quay\":{\"id\":\"NSR:Quay:11077\"}}]}}}";

  Serial.print("*** Reuslt: "); 
  Serial.print(response);

  Serial.println("*** JSON STUFF: "); 

  deserializeJson(doc, response);

  serializeJsonPretty(doc, Serial);
  /*
    PROBLEM IS NOT PARSING THE WHOLE SHIT!!!!:
    *** JSON STUFF: 
{
  "data": {
    "stopPlace": {
      "id": "NSR:StopPlace:6035",
      "name": null
    }
  }
}

   */
  
  //doc["data"]["stopPlace"]["estimatedCalls"].prettyPrintTo(Serial);

  const char* nameAvgang01 = doc["data"]["stopPlace"]["id"];
  const char* call01expectedDepartureTime = doc["data"]["stopPlace"]["estimatedCalls"][0]["expectedDepartureTime"];

  JsonArray estimatedCallsArray = doc["data"]["stopPlace"]["estimatedCalls"];
  for(JsonVariant v : estimatedCallsArray) 
  {
    String value = v.as<String>();
    Serial.println(value);
  }


  int myVal = estimatedCallsArray[0]["expectedDepartureTime"]; // 41
  
  // long time = doc["time"]; // 1351824120


  // float data_0 = doc["data"][0]; // 48.75608
  // float data_1 = doc["data"][1]; // 2.302038


  //  DynamicJsonBuffer jsonBuffer(10833);
  // JsonObject& root = jsonBuffer.parseObject(response);
  //  Serial.print("JsonObject: ");
  //  JsonObject&  thermoStat = root["data"]["stopPlace"];
  // const char* stopName = thermoStat["name"]; // "heating"

  //const char* avganger = doc["data"]; // "gps"

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println("nameAvgang01:");
  Serial.println(nameAvgang01);
  Serial.println("myVal:");
  Serial.println(myVal);
  Serial.println("call01expectedDepartureTime:");
  Serial.println(call01expectedDepartureTime);
  Serial.println("==========");

  show(response);
  display.update();

  //////////////////////////////// TEST ////////////////////////////////
  //  Serial.println("Receiving response");

  // while (client.connected()) {
  //   /*
  //   String line = client.readStringUntil('\n');
  //   Serial.println(line);
  //   if (line == "\r") {
  //     Serial.println("headers received");
  //     break;
  //   }
  //   */
  //   Serial.write(client.read());
  //   delay(5);
  // }

  // Serial.println("2");
  // String line = client.readStringUntil('\n');
  // Serial.println(line);
  // Serial.println("closing connection");
  //show(graphqlQuery);
  //display.update();
  

  //////////////////////////////// TEST - END ////////////////////////////

  // Serial.println("Connecting to Entur...");

  // String header = client.readStringUntil('\r');
  // String alt = client.readString();
  // Serial.println("************************** HEADER **************************");
  // Serial.println(header);
  // Serial.println("*************************** BODY ***************************");
  //Serial.println(alt);
  // if (line == "\r") {
  //   Serial.println("headers received");
  // }
  // Serial.println();

  //while (client.connected()) {
//    String line = client.readString();
    // Serial.println(line);



    //show(graphqlQuery);
    //display.update();

    
  //}

  delay(5000);  //GET Data at every 5 seconds


}