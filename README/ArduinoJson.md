#Ref
https://www.youtube.com/watch?v=nfr6wddRRxo

# Prettyprint
StaticJsonDocument<200> doc;
doc["hello"] = "world";
serializeJsonPretty(doc, Serial);

# Help
  JsonObject& seriesArray = ooo[0] ["series"]; // results[0] is a structure with 1 member
  JsonObject& series      = seriesArray[0]; // the first array element is a structure with 3 members
  JsonObject& valuesArray = series["values"]; // an array of value arrays
  JsonObject& values      = valuesArray[0]; // a nested array of values [char * and float]
  
# Sample
  // Reading JSON
  const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 30;
  DynamicJsonDocument doc(capacity);

  const char* json = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.75608,2.302038]}";

  deserializeJson(doc, json);

  const char* sensor = doc["sensor"]; // "gps"
  long time = doc["time"]; // 1351824120

  float data_0 = doc["data"][0]; // 48.75608
  float data_1 = doc["data"][1]; // 2.302038
  