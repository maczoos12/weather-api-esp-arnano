#include "main.h"

void setup() {
  // delay for devices to turn on and send data via Serial
  delay(10000);
  Serial.begin(9600);

  // Wifi connection establishment
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  String data_received;
  // Check for availability of StartApiProcedure on Serial port
  // and send acknowledge message to Arduino Nano
  if(Serial.available() > 0 && ack_sent == 0) {
    data_received = Serial.readStringUntil('\n');
      if (data_received.startsWith("StartApiProcedure")){
        Serial.println("Ack. StartApiProcedure....");
        first_call = 1;
        ack_sent = 1;

        //clear Serial port from not valid data
        delay(2);
        if(Serial.available())
          Serial.readStringUntil('\n');
      }
  }
  
  if(request_done == 0){
    if(first_call == 1){
      if(WiFi.status()== WL_CONNECTED){
        if(!httpGETRequest(request_url.c_str())) {
          sent = 1;
          done = 1;
          Serial.println("Something went wrong.");
        }
        delay(2000);
      } else
          Serial.println("WiFi Disconnected");
    } else if (json_weather.length()>300 && sent == 0){
      if(computeJsonAndSendSerialData() == 1){
        Serial.println("Sending json parameters completed.");
        request_done = 1;
        } else{
          Serial.println("Something went wrong.");
          done = 1;
        }
    }
  } else if (done == 0){
      Serial.println("Done.");
      done = 1;
  }
}

bool httpGETRequest(String serverName) {
  // Get daily weather data from openweathermap API
  // Save data to json_weather

  HTTPClient http;
  wifiClient.setInsecure();
  wifiClient.connect(serverName, httpsPort);
  http.begin(wifiClient, serverName);
  
  // Send HTTP POST request for Weather data
  int httpResponseCode = http.GET();
  
  String payload; 
  
  if (httpResponseCode > 0) {
    first_call = 0;
    json_weather = http.getString().substring(0, http.getSize());
  }else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    http.end();
    return 0;
  }

  // Free resources
  http.end();
  return 1;
}

bool computeJsonAndSendSerialData(void){
  // Ekstract specific weather data to send iver Serial
  // Unable to send whole API response to Arduino (bugs in Serial communication)

  // Split string into peaces to parse json data
  int index1 = json_weather.indexOf("daily");
  int index2 = json_weather.indexOf("{", index1);
  int idnex3 = json_weather.indexOf("uvi", index2);
  int index4 = json_weather.indexOf("}", idnex3);
  String weather_info = json_weather.substring(index2, index4 + 1);
  int index5 = weather_info.indexOf("[");
  int index6 = weather_info.indexOf("]", index5);
  String icon_info = weather_info.substring(index5 + 1, index5);
  sent = 1;

  // free resources
  json_weather = "";

  JSONVar myObject = JSON.parse(weather_info);
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("1. Parsing input failed!");
    return 0;
  }

  JSONVar myObject2 = JSON.parse(icon_info);
  if (JSON.typeof(myObject2) == "undefined") {
    Serial.println("2. Parsing input failed!");
    return 0;
  }

  //Send collected weather data over Serial port
  for(int i = 0; i<18; i++){
    send_weather_data_over_serial(i, myObject);
    if (wait_for_acknowledge_from_arduino() == 1){
      break;
    } else
      return 0;
  }
  for(int i = 18; i<20; i++){
    send_weather_data_over_serial(i, myObject2);
    if (wait_for_acknowledge_from_arduino() == 1){
      break;
    }
    else
      return 0;
  }

  return 1;
}

void send_weather_data_over_serial(int index, JSONVar json_object) {
  // Unpack values from json_object via json_parameters_daily[index]

  Serial.print("Object");
  Serial.print(index + 1);
  Serial.println("Send");
  if(index >= 12 && index < 16 ){
  Serial.print(json_object["temp"][json_parameters_daily[index]]);
  } else if (index >= 16 && index < 18){
  Serial.print(json_object["feels_like"][json_parameters_daily[index]]);
  } else
  Serial.print(json_object[json_parameters_daily[index]]);
  Serial.println("|");
}

int wait_for_acknowledge_from_arduino(void){
  // Checking Serial port for acknowledge from Arduino

  String data;
  bool acknowledge = 0;
  do{
      int char_len = 0;
      while (char_len<3)
      {
        while (!Serial.available()){}
        char one_char = Serial.read();
        data += one_char;
        char_len++;
      }
      delay(2);
      if(Serial.available())
        Serial.readStringUntil('\n');
      if(data.startsWith("Ack")){
        acknowledge = 1;
        return 1;
      }
      else
        return 0;
    }while (acknowledge == 0);
}
