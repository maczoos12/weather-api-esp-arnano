#include <string>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <cmath>

bool httpGETRequest(String serverName);
bool computeJsonAndSendSerialData(void);
void send_weather_data_over_serial(int index, JSONVar json_object);
int wait_for_acknowledge_from_arduino(void);

// LA
const char* ssid = "*";
const char* password = "*";

String request_url = "https://api.openweathermap.org/data/2.5/onecall?lat=50.0833&lon=19.9167&exclude=hourly,minutely&units=metric&lang=PL&appid=d5a0a877502889987d2194ce18542caf";
String json_weather;
WiFiClientSecure wifiClient;
int httpsPort = 443;
int api_place_pointer = 5000;
bool request_done = 0;
bool first_call = 0;
bool done = 0;
bool ack_sent = 0;
bool sent = 0;
String json_parameters_daily[20] = {
  "dt",
  "sunrise",
  "sunset",
  "sunrise", // duplicate
  "moonrise",
  "moonset",
  "moon_phase",
  "pressure",
  "humidity",
  "wind_speed",
  "clouds",
  "pop",
  "day", // temp 12
  "min",
  "max",
  "night", 
  "day", //feels_like 16
  "night",
  "description", //weather - other object 18
  "icon"
};