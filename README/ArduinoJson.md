#Ref
https://www.youtube.com/watch?v=nfr6wddRRxo

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
  