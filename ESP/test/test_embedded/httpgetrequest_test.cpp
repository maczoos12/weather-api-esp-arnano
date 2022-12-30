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

    String request_url = "*";
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

    String request_url = "*";
    bool expected = 0;
    bool actual = httpGETRequest(request_url);

    ASSERT_EQ(expected, actual);
}