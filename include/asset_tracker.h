//
// Created by Tyler Wade on 10/12/25.
//

#ifndef ASSET_TRACKER_H
#define ASSET_TRACKER_H
#include "auth_service.h"
#include "location_service.h"


class AssetTracker {
public:
    AssetTracker(AuthService* authService);
    void sendHeartbeat();

private:
    AuthService* authService;
    LocationService* locationService;
    Location lastSuccessLocation;
    String buildHeartbeatPayload(Location loc);
};



#endif //ASSET_TRACKER_H
