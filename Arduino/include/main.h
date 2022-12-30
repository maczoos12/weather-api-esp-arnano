#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <time.h>

// Parola
const uint16_t WAIT_TIME = 1000;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// Hardware SPI connection
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int pin;
String content = "";
bool bulb_state = 0;
bool message_sent = 0;
bool message_red = 0;
bool serial_written = 0;
bool acknowledge_recieved = 0;

struct daily_weather
{
  String date_and_time;
  String sunrise;
  String sunset;
  String moonrise;
  String moonset;
  String moon_phase;
  String pressure;
  String humidity;
  String wind_speed;
  String cloud_percent;
  String probability_of_precipitation;
  String temp_day;
  String temp_day_min;
  String temp_day_max;
  String temp_night;
  String temp_feel_day;
  String temp_feel_night;
  String weath_description;
  String icon; // To będzie do ikonki, no tak xD
};