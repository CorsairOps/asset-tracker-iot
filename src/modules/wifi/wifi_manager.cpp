//
// Created by Tyler Wade on 10/12/25.
//

#include "wifi_manager.h"
#include "WiFi.h"
#include "../../config.h"

WiFiManager::WiFiManager() {
}

void WiFiManager::connectToNetwork() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);
    delay(100);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.printf("... Current Status: %d\n", WiFi.status());
        delay(2000);

        if (WiFi.status() == WL_CONNECT_FAILED) {
            Serial.println("Connection failed. Retrying...");
            WiFi.disconnect(true);
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        }
    }
    Serial.println("Connected to WiFi!");
}

void WiFiManager::disconnectFromNetwork() {
    Serial.println("Disconnecting from WiFi...");
    WiFi.disconnect(true);
    while (WiFi.status() != WL_DISCONNECTED) {
        Serial.println(".");
        delay(1000);
    }
    Serial.println("Disconnected from WiFi.");
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::reconnectToNetwork() {
    WiFi.reconnect();
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconnecting to WiFi...");
        delay(2000);

        if (WiFi.status() == WL_CONNECT_FAILED) {
            Serial.println("Connection failed. Retrying...");
            WiFi.reconnect();
        }
    }
}

void WiFiManager::validateConnected() {
    if (!isConnected()) {
        reconnectToNetwork();
    }
}
