#include <Arduino.h>

#include "config.h"
#include "modules/asset/asset_tracker.h"
#include "modules/auth/auth_service.h"
#include "modules/wifi/wifi_manager.h"

WiFiManager wifiManager;
AuthService authService;
AssetTracker assetTracker(&authService);

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 Initialization completed.");

    delay(3000); // Wait for serial to initialize
    wifiManager.connectToNetwork();
}

void loop() {
    Serial.printf("Running time : %.1f s\n", millis() / 1000.0f);
    wifiManager.validateConnected();
    assetTracker.sendHeartbeat();
    delay(HEARTBEAT_RATE);
}
