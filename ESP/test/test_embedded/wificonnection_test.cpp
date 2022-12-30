#include <gtest/gtest.h>
#include "main.h"

TEST(httpGETRequest, test_wifi_connection_with_proper_login_items_after_5_attempts) {
    delay(2000);
    WiFi.begin(ssid, password);
    for (int attempts = 0; attempts < 5; attempts++){
        if (WiFi.status() == WL_CONNECTED)
            break;
    }

    int expected = WL_CONNECTED;
    bool actual = httpGETRequest(request_url);

    ASSERT_EQ(expected, actual);
}

TEST(httpGETRequest, test_wifi_connection_with_proper_login_items_after_10_attempts) {
    delay(2000);
    WiFi.begin(ssid, password);
    for (int attempts = 0; attempts < 10; attempts++){
        if (WiFi.status() == WL_CONNECTED)
            break;
    }

    int expected = WL_CONNECTED;
    bool actual = WiFi.status();

    ASSERT_EQ(expected, actual);
}


TEST(httpGETRequest, test_wifi_connection_with_wrong_login_items_after_15_attempts) {
    delay(2000);
    ssid = "wrong";
    password = "wrong";
    WiFi.begin(ssid, password);
    for (int attempts = 0; attempts < 15; attempts++){
        if (WiFi.status() == WL_CONNECTED)
            break;
    }

    int not_expected = WL_CONNECTED;
    bool actual = WiFi.status();
    ASSERT_NE(not_expected, actual);
}