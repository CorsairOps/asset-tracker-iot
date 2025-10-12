//
// Created by Tyler Wade on 10/12/25.
//

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H



class WiFiManager {
public:
    WiFiManager();
    void connectToNetwork();
    void disconnectFromNetwork();
    bool isConnected();
    void reconnectToNetwork();
    void validateConnected();
};



#endif //WIFI_MANAGER_H
