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


const char* wifiName = "Telenor7901rak";
const char* wifiPass = "ixmlvfkyfegyo";

// const char* wifiName = "Skobbis2";
// const char* wifiPass = "r3plikant";


char input[] = "{\"name\":\"ArduinoJson\",\"stargazers\":{";

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


// Frode versjon (no newline, "query", double esc)
const char* graphqlQuery = "{\"query\":\"{bikeRentalStationsByBbox(minimumLatitude:59.9\\nmaximumLatitude:60\\nminimumLongitude:10.7\\nmaximumLongitude:10.8\\n)\\n{id\\nname\\nbikesAvailable\\nspacesAvailable}}\",\"variables\":null}";



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
//sizeof(char) = 1

  String url = "/journey-planner/v2/graphql";
  String content = String("POST /journey-planner/v2/graphql HTTP/1.1\n");
  content += "Host: api.entur.io\n";
  content += "Cache-Control: no-cache\n";
  content += "Content-Type: application/json\n";
  content += "Content-Length: " + String(strlen(graphqlQuery)) + String("\n");
  content += "\n";
  content += graphqlQuery;

  Serial.println(String("Dette sendes: ") + content);

  client.print(content);

  // // Request
  // client.println("POST /journey-planner/v2/graphql HTTP/1.1");
  // client.println("Host: api.entur.io");
  // client.println("Cache-Control: no-cache");
  // client.println("Content-Type: application/json");
  // client.print("Content-Length: ");
  // client.println(strlen(graphqlQuery));
  // client.println();
  // client.println(graphqlQuery);
  // client.println();




/*
I am not sure if this is still relevant for you but I faced the same situation and I believe I found a solution. If it is not relevant to you, perhaps it will help some other, especially given that the default WiFiClientSecure library will soon be switched to BearSSL and no support is currently being given for the existing implementation.
Although I did not manage to speed up readString function, I used the WiFiClientSecure::read(uint8_t *buf, size_t size) function to get the data from the server:

 */
/*
  // Buffer size, 128 bytes in this case
  #define RESP_BUFFER_LENGTH 128
  // Pointer to actual buffer
  uint8_t * _buffer = new uint8_t[RESP_BUFFER_LENGTH];
  // String to hold the final response
  String _responseString = "";
  // If info is still available
  while (client.available())
  {
      // Fill the buffer and make a note of the total read length 
      int actualLength = client.readBytes(_buffer, RESP_BUFFER_LENGTH);
      // If it fails for whatever reason
      if(actualLength <= 0)
      {

      }
      // Concatenate the buffer content to the final response string
      // I used an arduino String for convenience
      // but you can use strcat or whatever you see fit
      _responseString += String((char*)_buffer).substring(0, actualLength);  
      
      Serial.print(_responseString);

  }
  // Clear buffer memory
  delete[] _buffer;
*/




  // JsonObject& root = jsonBuffer.parseObject(response.substring(bodypos));

  // String device_token = root[String("user_code")];

  // return device_token;



    // show("Entur API");
    // display.update();


  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readString();
    Serial.println(line);


    Serial.println("reply was:");
    Serial.println("==========");
    Serial.println(line);
    Serial.println("==========");
    Serial.println("closing connection");


    show(line);
    display.update();
  }

  // while (client.connected()) {
  //   String line = client.readStringUntil('\n');
  //   Serial.println(line);
  //   // if (line == "\r") {
  //   //   Serial.println("headers received");
  //   //   break;
  //   // }
  // }






  delay(15000);  //GET Data at every 5 seconds


  // String line = client.readStringUntil('\n');
  // if (line.startsWith("{\"state\":\"success\"")) {
  //   Serial.println("esp8266/Arduino CI successfull!");
  // } else {
  //   Serial.println("esp8266/Arduino CI has failed");
  //   //show("esp8266/Arduino CI has failed");
  // }
  
}