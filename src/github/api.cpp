#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
#include "github/api.hpp"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

namespace github {
    std::string get_user_raw(const std::string& username) {
        CURL* curl = curl_easy_init();
        std::string response;

        if (curl) {
            std::string url = "https://api.github.com/users/" + username;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "UnauthScout/0.3.0");

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                response = R"({"error": ")" + std::string(curl_easy_strerror(res)) + "\"}";
            }

            curl_easy_cleanup(curl);
        }

        return response;
    }

    nlohmann::json normalize_user(const std::string& raw_user) {
        auto user = nlohmann::json::parse(raw_user);
        nlohmann::json normalized = {
            {"platform", "github"},
            {"handle", user.value("login", "N/A")},
            {"name", user.value("name", user.value("login", "N/A"))},
            {"bio", user.value("bio", nlohmann::json())},
            {"public_repos", user.value("public_repos", 0)},
            {"followers", user.value("followers", 0)},
            {"following", user.value("following", 0)},
            {"created_at", user.value("created_at", nlohmann::json())},
            {"updated_at", user.value("updated_at", nlohmann::json())},
            {"url", user.value("html_url", "N/A")}
        };
        return normalized;
    }

    std::string get_repos_raw(const std::string& username) {
        CURL* curl = curl_easy_init();
        std::string response;

        if (curl) {
            std::string url = "https://api.github.com/users/" + username + "/repos";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "UnauthScout/0.3.0");

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                response = R"({"error": ")" + std::string(curl_easy_strerror(res)) + "\"}";
            }

            curl_easy_cleanup(curl);
        }

        return response;
    }

    nlohmann::json normalize_repos(const std::string& raw_repos) {
        auto repos = nlohmann::json::parse(raw_repos);
        nlohmann::json normalized_repos = nlohmann::json::array();
        for (const auto& repo : repos) {
            nlohmann::json normalized_repo = {
                {"name", repo.value("name", "N/A")},
                {"full_name", repo.value("full_name", "N/A")},
                {"url", repo.value("html_url", "N/A")},
                {"description", repo.value("description", nlohmann::json())},
                {"stars", repo.value("stargazers_count", 0)},
                {"language", repo.value("language", nlohmann::json())},
                {"updated_at", repo.value("updated_at", nlohmann::json())},
                {"topics", repo.value("topics", nlohmann::json::array())}
            };
            normalized_repos.push_back(normalized_repo);
        }
        return normalized_repos;
    }
}
