//
// Created by Tyler Wade on 10/12/25.
//

#include "asset_tracker.h"
#include <HTTPClient.h>
#include "secrets.h"
#include "../location/location_service.h"

AssetTracker::AssetTracker(AuthService *authService) {
    this->authService = authService;
    this->locationService = new LocationService();
}

void AssetTracker::sendHeartbeat() {
    HTTPClient http;

    try {
        const String accessToken = this->authService->validateAndGetAccessToken();
        const Location location = this->locationService->calculateCurrentLocation();

        if (location.latitude == lastSuccessLocation.latitude && location.longitude == lastSuccessLocation.longitude) {
            throw std::runtime_error("Location has not changed since last successful heartbeat.");
        }

        http.begin(String(EVENT_PUBLISH_URL));
        http.setConnectTimeout(10000);
        http.setTimeout(10000);
        http.addHeader("Content-Type", "text/plain");
        http.addHeader("Authorization", "Bearer " + accessToken);
        String payload = buildHeartbeatPayload(location);
        Serial.println("Sending payload: " + payload);
        const int responseCode = http.POST(payload);

        if (responseCode != HTTP_CODE_NO_CONTENT &&
            responseCode != HTTP_CODE_OK &&
            responseCode != HTTP_CODE_CREATED) {
            Serial.printf("Failed to send heartbeat, response code: %d. Response: %s\n",
                          responseCode, http.getString().c_str());
        } else {
            Serial.println("Heartbeat sent successfully.");
            lastSuccessLocation = location;
        }
    } catch (const std::exception &e) {
        Serial.println("Error sending heartbeat: " + String(e.what()));
    }

    http.end();
}

String AssetTracker::buildHeartbeatPayload(Location loc) {
    const String assetId = String(ASSET_ID);
    const double latitude = loc.latitude;
    const double longitude = loc.longitude;
    return "{\"assetId\": \"" + assetId + "\", \"latitude\": " + String(latitude, 3) + ", \"longitude\": " +
           String(longitude, 3) + "}";
}
