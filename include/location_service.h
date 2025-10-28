//
// Created by Tyler Wade on 10/13/25.
//

#ifndef LOCATION_SERVICE_H
#define LOCATION_SERVICE_H
#include <HardwareSerial.h>
#include "TinyGPS++.h"

#define RXD2 16
#define TXD2 17
#define GPS_BAUD 9600

struct Location {
    float latitude;
    float longitude;
    unsigned long timestamp;
};

class LocationService {
public:
    LocationService();
    Location calculateCurrentLocation();

private:
    Location lastLocation;
    HardwareSerial gpsSerial;
    TinyGPSPlus gps;

    bool hasMoved(Location& loc);
};



#endif //LOCATION_SERVICE_H
