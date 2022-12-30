#include <gtest/gtest.h>
#include "main.h"

TEST(computeJsonAndSendSerialData, test_correct_data_from_API) {
    json_weather = '{"lat":50.0833,"lon":19.9167,"timezone":"Europe/Warsaw","timezone_offset":3600,"current":{"dt":1672404391,"sunrise":1672382352,"sunset":1672411559,"temp":8.23,"feels_like":6.03,"pressure":1017,"humidity":71,"dew_point":3.29,"uvi":0.23,"clouds":75,"visibility":10000,"wind_speed":3.6,"wind_deg":220,"weather":[{"id":803,"main":"Clouds","description":"zachmurzenie umiarkowane","icon":"04d"}]},"daily":[{"dt":1672394400,"sunrise":1672382352,"sunset":1672411559,"moonrise":1672397100,"moonset":0,"moon_phase":0.25,"temp":{"day":7.31,"min":3.65,"max":8.23,"night":3.76,"eve":6.21,"morn":4.13},"feels_like":{"day":6.14,"night":1.99,"eve":6.21,"morn":2.1},"pressure":1018,"humidity":78,"dew_point":3.73,"wind_speed":3.24,"wind_deg":266,"wind_gust":7.08,"weather":[{"id":500,"main":"Rain","description":"słabe opady deszczu","icon":"10d"}],"clouds":90,"pop":0.56,"rain":0.4,"uvi":0.47},{"dt":1672480800,"sunrise":1672468754,"sunset":1672498014,"moonrise":1672484340,"moonset":1672444320,"moon_phase":0.3,"temp":{"day":8.8,"min":3.71,"max":9.9,"night":8.94,"eve":9.33,"morn":4.6},"feels_like":{"day":6.51,"night":6.89,"eve":7.37,"morn":2.46},"pressure":1021,"humidity":80,"dew_point":5.28,"wind_speed":4.76,"wind_deg":233,"wind_gust":11.88,"weather":[{"id":804,"main":"Clouds","description":"zachmurzenie duże","icon":"04d"}],"clouds":100,"pop":0.05,"uvi":0.28},{"dt":1672567200,"sunrise":1672555152,"sunset":1672584471,"moonrise":1672571700,"moonset":1672535220,"moon_phase":0.33,"temp":{"day":11.07,"min":7.09,"max":12.22,"night":7.09,"eve":9.3,"morn":8.36},"feels_like":{"day":9.96,"night":5.22,"eve":8.87,"morn":6.38},"pressure":1024,"humidity":66,"dew_point":4.71,"wind_speed":3.29,"wind_deg":235,"wind_gust":7.25,"weather":[{"id":803,"main":"Clouds","description":"zachmurzenie umiarkowane","icon":"04d"}],"clouds":74,"pop":0,"uvi":0.62},{"dt":1672653600,"sunrise":1672641548,"sunset":1672670930,"moonrise":1672659180,"moonset":1672626120,"moon_phase":0.36,"temp":{"day":8.09,"min":6.52,"max":10.69,"night":6.52,"eve":8.58,"morn":6.75},"feels_like":{"day":8.09,"night":4.56,"eve":8.11,"morn":5.42},"pressure":1024,"humidity":84,"dew_point":5.22,"wind_speed":2.68,"wind_deg":246,"wind_gust":4.81,"weather":[{"id":804,"main":"Clouds","description":"zachmurzenie duże","icon":"04d"}],"clouds":100,"pop":0,"uvi":0.62},{"dt":1672740000,"sunrise":1672727940,"sunset":1672757393,"moonrise":1672747020,"moonset":1672716900,"moon_phase":0.39,"temp":{"day":7.3,"min":5.54,"max":7.3,"night":5.72,"eve":6.01,"morn":5.83},"feels_like":{"day":4.54,"night":4.19,"eve":3.66,"morn":3.47},"pressure":1025,"humidity":85,"dew_point":4.62,"wind_speed":4.58,"wind_deg":296,"wind_gust":11.24,"weather":[{"id":500,"main":"Rain","description":"słabe opady deszczu","icon":"10d"}],"clouds":100,"pop":0.35,"rain":0.58,"uvi":0.62},{"dt":1672826400,"sunrise":1672814330,"sunset":1672843857,"moonrise":1672835280,"moonset":1672807560,"moon_phase":0.42,"temp":{"day":4.03,"min":2.33,"max":6.13,"night":5.96,"eve":6.13,"morn":3.25},"feels_like":{"day":2.71,"night":0.94,"eve":2.97,"morn":3.25},"pressure":1027,"humidity":72,"dew_point":-0.82,"wind_speed":9.71,"wind_deg":240,"wind_gust":17.43,"weather":[{"id":500,"main":"Rain","description":"słabe opady deszczu","icon":"10d"}],"clouds":30,"pop":0.98,"rain":2.78,"uvi":1},{"dt":1672912800,"sunrise":1672900716,"sunset":1672930324,"moonrise":1672924080,"moonset":1672897860,"moon_phase":0.45,"temp":{"day":9.2,"min":7.16,"max":9.2,"night":7.78,"eve":8.7,"morn":8.07},"feels_like":{"day":5.1,"night":4.21,"eve":5.17,"morn":3.96},"pressure":1008,"humidity":82,"dew_point":6.04,"wind_speed":10.22,"wind_deg":259,"wind_gust":17.12,"weather":[{"id":500,"main":"Rain","description":"słabe opady deszczu","icon":"10d"}],"clouds":100,"pop":1,"rain":7.54,"uvi":1},{"dt":1672999200,"sunrise":1672987099,"sunset":1673016793,"moonrise":1673013540,"moonset":1672987620,"moon_phase":0.48,"temp":{"day":7.82,"min":0.34,"max":7.82,"night":0.34,"eve":1.13,"morn":5.9},"feels_like":{"day":4.06,"night":-3.83,"eve":-3.8,"morn":4.5},"pressure":1002,"humidity":81,"dew_point":4.48,"wind_speed":7.24,"wind_deg":241,"wind_gust":14.86,"weather":[{"id":616,"main":"Snow","description":"śnieg z deszczem","icon":"13d"}],"clouds":100,"pop":1,"rain":14.38,"snow":3.22,"uvi":1}]}';
    delay(2000);
    WiFi.begin(ssid, password);
    for (int attempts = 0; attempts < 10; attempts++){
        if (WiFi.status() == WL_CONNECTED)
            break;
    }
    ASSERT_EQ(WL_CONNECTED, WiFi.status());

    String data_received;
    if(Serial.available() > 0 && ack_sent == 0) {
        data_received = Serial.readStringUntil('\n');
        if (data_received.startsWith("StartApiProcedure")){
            Serial.println("Ack. StartApiProcedure....");
            first_call = 1;
            ack_sent = 1;

            delay(2);
            if(Serial.available())
                Serial.readStringUntil('\n');
        }
    }
    ASSERT_EQ(1, ack_sent);

    int expected = 1;
    int actual = computeJsonAndSendSerialData();

    ASSERT_EQ(expected, actual);
}

TEST(computeJsonAndSendSerialData, test_corrupted_data_from_API) {
    json_weather = 'daily..{..uvi..}..[..]';
    delay(2000);
    WiFi.begin(ssid, password);
    for (int attempts = 0; attempts < 10; attempts++){
        if (WiFi.status() == WL_CONNECTED)
            break;
    }
    ASSERT_EQ(WL_CONNECTED, WiFi.status());

    String data_received;
    if(Serial.available() > 0 && ack_sent == 0) {
        data_received = Serial.readStringUntil('\n');
        if (data_received.startsWith("StartApiProcedure")){
            Serial.println("Ack. StartApiProcedure....");
            first_call = 1;
            ack_sent = 1;

            delay(2);
            if(Serial.available())
                Serial.readStringUntil('\n');
        }
    }
    ASSERT_EQ(1, ack_sent);

    int expected = 0;
    int actual = computeJsonAndSendSerialData();
    
    ASSERT_EQ(expected, actual);
}