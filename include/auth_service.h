//
// Created by Tyler Wade on 10/12/25.
//

#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H
#include <WString.h>

class AuthService {
public:
    AuthService();
    void authenticate();
    bool isAuthenticated();
    String validateAndGetAccessToken();

private:
    String accessToken;
    unsigned long tokenReceivedAtSeconds;
    unsigned long expiresInSeconds;

    void handleOKAuthResponse(String responseBody);
    String extractAccessToken(String responseBody);
    int extractExpiresIn(String responseBody);

};



#endif //AUTH_SERVICE_H
