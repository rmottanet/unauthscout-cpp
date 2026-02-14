#include "helpers/http_client.hpp"
#include <stdexcept>

namespace helpers {
    HttpClient::HttpClient() : curl(curl_easy_init()), user_agent("UnauthScout") {
        if (!curl) {
            throw std::runtime_error("Failed to initialize CURL");
        }
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    }

    HttpClient::~HttpClient() {
        if (curl) {
            curl_easy_cleanup(curl);
        }
    }

    HttpClient::HttpClient(HttpClient&& other) noexcept : curl(other.curl), user_agent(std::move(other.user_agent)) {
        other.curl = nullptr;
    }

    HttpClient& HttpClient::operator=(HttpClient&& other) noexcept {
        if (this != &other) {
            if (curl) curl_easy_cleanup(curl);
            curl = other.curl;
            user_agent = std::move(other.user_agent);
            other.curl = nullptr;
        }
        return *this;
    }

    void HttpClient::set_user_agent(const std::string& new_user_agent) {
        user_agent = new_user_agent;
    }

    size_t HttpClient::WriteCallback(const char* contents, size_t size, size_t nmemb, std::string* output) {
        size_t total_size = size * nmemb;
        output->append(contents, total_size);
        return total_size;
    }

    std::string HttpClient::get(const std::string& url) {
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            throw std::runtime_error("CURL error: " + std::string(curl_easy_strerror(res)));
        }

        return response;
    }
}
