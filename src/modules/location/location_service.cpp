//
// Created by Tyler Wade on 10/13/25.
//

#include "location_service.h"
#include <cmath>

LocationService::LocationService(): gpsSerial(2), gps() {
    this->gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
    Serial.println("GPS Serial started in LocationService.");
    lastLocation = {1000, 1000, 0}; // Invalid initial location
}

Location LocationService::calculateCurrentLocation() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    if (gps.location.isUpdated() && gps.location.isValid()) {
        Serial.println("Location has updated: " + String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6));
        Location loc;
        loc.latitude = gps.location.lat();
        loc.longitude = gps.location.lng();
        loc.timestamp = millis();
        if (hasMoved(loc)) {
            Serial.println("Location has changed.");
            lastLocation = loc;
        }
    } else {
        Serial.println("Location has not updated or is not valid.");
    }

    if (lastLocation.latitude == 1000 && lastLocation.longitude == 1000) {
        throw std::runtime_error("No valid location fix yet.");
    }

    return lastLocation;
}

bool LocationService::hasMoved(Location &loc) {
    const double threshold = 1e-3; // ~111 meters difference
    bool latDiff = std::fabs(loc.latitude - lastLocation.latitude) > threshold;
    bool lonDiff = std::fabs(loc.longitude - lastLocation.longitude) > threshold;
    return latDiff || lonDiff;
}
