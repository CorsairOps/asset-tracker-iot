//
// Created by Tyler Wade on 10/12/25.
//

#ifndef ASSET_TRACKER_H
#define ASSET_TRACKER_H
#include <HTTPClient.h>

#include "modules/auth/auth_service.h"


class AssetTracker {
public:
    AssetTracker(AuthService* authService);
    void sendHeartbeat();

private:
    AuthService* authService;
    String buildHeartbeatPayload();
};



#endif //ASSET_TRACKER_H
