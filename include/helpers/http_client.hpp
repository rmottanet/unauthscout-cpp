#pragma once
#include <string>
#include <curl/curl.h>

namespace helpers {
    class HttpClient {
    public:
        HttpClient();
        ~HttpClient();

        // Delete copy constructor and copy assignment operator
        HttpClient(const HttpClient&) = delete;
        HttpClient& operator=(const HttpClient&) = delete;

        // Move constructor and move assignment operator
        HttpClient(HttpClient&& other) noexcept;
        HttpClient& operator=(HttpClient&& other) noexcept;

        std::string get(const std::string& url);
        void set_user_agent(const std::string& new_user_agent);

    private:
        CURL* curl;
        std::string user_agent;
        static size_t WriteCallback(const char* contents, size_t size, size_t nmemb, std::string* output);
    };
}
