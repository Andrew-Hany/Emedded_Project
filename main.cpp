
#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "seifseif"

String HOST_NAME = "http://10.40.32.213";
String PATH_NAME   = "/authenticate.php";
String queryString = "?id=900183874";


void setup() {

  Serial.begin(921600);

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("starting");

  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + queryString);
  int httpCode = http.GET();

  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
}

bool isConnected = false;

void loop() {

  if (WiFi.status() == WL_CONNECTED && !isConnected) {

    Serial.println("Connected");

    digitalWrite(LED_BUILTIN, HIGH);

    isConnected = true;

  }

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println(".");

    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    delay(1000);

    isConnected = false;

  }

}
