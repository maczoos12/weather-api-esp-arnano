#include <gtest/gtest.h>
#include "main.h"

TEST(httpGETRequest, test_correct_page) {
    delay(2000);
    WiFi.begin(ssid, password);
    for (int attempts = 0; attempts < 10; attempts++){
        if (WiFi.status() == WL_CONNECTED)
            break;
    }
    ASSERT_EQ(WL_CONNECTED, WiFi.status());

    String request_url = "https://api.openweathermap.org/data/2.5/onecall?lat=50.0833&lon=19.9167&exclude=hourly,minutely&units=metric&lang=PL&appid=d5a0a877502889987d2194ce18542caf";
    bool expected = 1;
    bool actual = httpGETRequest(request_url);

    ASSERT_EQ(expected, actual);
}

TEST(httpGETRequest, test_wrong_page) {
    delay(2000);
    WiFi.begin(ssid, password);
    for (int attempts = 0; attempts < 10; attempts++){
        if (WiFi.status() == WL_CONNECTED)
            break;
    }
    ASSERT_EQ(WL_CONNECTED, WiFi.status());

    String request_url = "https://api.openweathermap/data/necall?lat=50.ude=hourly,minutely&units=metric&lang=PL&appid=d5a0a877502889987d2194ce18542caf";
    bool expected = 0;
    bool actual = httpGETRequest(request_url);

    ASSERT_EQ(expected, actual);
}