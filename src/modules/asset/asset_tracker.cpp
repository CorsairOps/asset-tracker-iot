//
// Created by Tyler Wade on 10/12/25.
//

#include "asset_tracker.h"
#include <HTTPClient.h>
#include "secrets.h"

AssetTracker::AssetTracker(AuthService *authService) {
    this->authService = authService;
}

void AssetTracker::sendHeartbeat() {
    HTTPClient http;

    try {
        Serial.println("Sending heartbeat to asset service.");
        const String accessToken = this->authService->validateAndGetAccessToken();
        String url = String(ASSET_API_URL) + "/" + String(ASSET_ID) + "/locations";

        http.begin(url);
        http.setConnectTimeout(10000);
        http.setTimeout(10000);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer " + accessToken);
        String payload = buildHeartbeatPayload();
        const int responseCode = http.PUT(payload);

        if (responseCode != HTTP_CODE_NO_CONTENT &&
            responseCode != HTTP_CODE_OK &&
            responseCode != HTTP_CODE_CREATED) {
            Serial.printf("Failed to send heartbeat, response code: %d. Response: %s\n",
                          responseCode, http.getString().c_str());
        } else {
            Serial.println("Heartbeat sent successfully.");
        }
    } catch (const std::exception &e) {
        Serial.println("Error sending heartbeat: " + String(e.what()));
    }

    http.end();
}

String AssetTracker::buildHeartbeatPayload() {
    const double latitude = -90.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / 180.0));
    const double longitude = -180.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / 360.0));

    return "{\"latitude\": " + String(latitude, 6) +
           ", \"longitude\": " + String(longitude, 6) + "}";
}
