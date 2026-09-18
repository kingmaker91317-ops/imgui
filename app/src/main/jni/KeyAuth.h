#pragma once

#include <string>
#include <curl/curl.h>
#include "LAZ/Tools/curl/json.hpp"

using json = nlohmann::json;

// UPDATE THIS WITH YOUR DEPLOYED RENDER SERVER URL
#define SERVER_VERIFY_URL "https://lion-key-auth-server.onrender.com/api/verify"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

struct KeyVerifyResult {
    bool success;
    std::string message;
    std::string expiresAt;
    int daysLeft;
};

inline KeyVerifyResult VerifyUserKey(const std::string& userKey, const std::string& hwid) {
    KeyVerifyResult result{ false, "Network Error", "", 0 };

    CURL* curl = curl_easy_init();
    if (!curl) return result;

    std::string response_string;
    
    json payload;
    payload["key"] = userKey;
    payload["hwid"] = hwid;
    std::string jsonStr = payload.dump();

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, SERVER_VERIFY_URL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // 10s timeout
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Allow self-signed/HTTPS on Android

    CURLcode res = curl_easy_perform(curl);
    
    if (res == CURLE_OK) {
        try {
            auto resJson = json::parse(response_string);
            if (resJson["status"] == "success") {
                result.success = true;
                result.message = resJson.value("message", "Key Valid");
                result.expiresAt = resJson.value("expires_at", "");
                result.daysLeft = resJson.value("days_left", 0);
            } else {
                result.success = false;
                result.message = resJson.value("message", "Invalid Key");
            }
        } catch (...) {
            result.message = "Invalid JSON Server Response";
        }
    } else {
        result.message = std::string("CURL Error: ") + curl_easy_strerror(res);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return result;
}
