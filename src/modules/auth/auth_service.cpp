//
// Created by Tyler Wade on 10/12/25.
//

#include "auth_service.h"
#include <config.h>
#include <HTTPClient.h>

AuthService::AuthService() {
}

void AuthService::authenticate() {
    Serial.println("Attempting to authenticate with auth service...");
    HTTPClient http;
    http.begin(String(AUTH_SERVICE_TOKEN_ENDPOINT));
    http.setConnectTimeout(10000);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String payload = "client_id=" + String(AUTH_SERVICE_CLIENT_ID) +
                     "&client_secret=" + String(AUTH_SERVICE_CLIENT_SECRET) +
                     "&grant_type=client_credentials";
    int httpResponseCode = http.POST(payload);

    Serial.printf("Http Response Code: %d\n", httpResponseCode);
    if (httpResponseCode == HTTP_CODE_OK) {
        this->handleOKAuthResponse(http.getString());
        Serial.println("Authentication success.");
    } else {
        Serial.println("Error on sending POST: " + http.getString());
    }
    http.end();
}

void AuthService::handleOKAuthResponse(String responseBody) {
    this->accessToken = this->extractAccessToken(responseBody);
    this->expiresInSeconds = this->extractExpiresIn(responseBody);
    this->tokenReceivedAtSeconds = millis() / 1000.0f;
}


String AuthService::extractAccessToken(String responseBody) {
    int tokenStart = responseBody.indexOf("\"access_token\":\"") + 16;
    int tokenEnd = responseBody.indexOf("\"", tokenStart);
    return responseBody.substring(tokenStart, tokenEnd);
}

int AuthService::extractExpiresIn(String responseBody) {
    int expiresInStart = responseBody.indexOf("\"expires_in\":") + 13;
    int expiresInEnd = responseBody.indexOf(",", expiresInStart);
    return responseBody.substring(expiresInStart, expiresInEnd).toInt();
}

bool AuthService::isAuthenticated() {
    unsigned long now = millis() / 1000.0f;
    return accessToken != nullptr && !accessToken.isEmpty() && now - tokenReceivedAtSeconds < expiresInSeconds;
}

String AuthService::validateAndGetAccessToken() {
    if (!isAuthenticated()) {
        authenticate();
        if (!isAuthenticated()) {
            throw new std::runtime_error("Failed to authenticate with auth service.");
        }
    }
    return accessToken;
}
