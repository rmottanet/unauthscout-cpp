#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
#include "gitlab/api.hpp"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

namespace gitlab {
    std::string get_user_raw(const std::string& username) {
        CURL* curl = curl_easy_init();
        std::string response;

        if (curl) {
            std::string url = "https://gitlab.com/api/v4/users?username=" + username;
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
        auto users = nlohmann::json::parse(raw_user);
        if (users.is_array() && !users.empty()) {
            auto user = users[0];
            nlohmann::json normalized = {
                {"platform", "gitlab"},
                {"handle", user.value("username", "N/A")},
                {"name", user.value("name", user.value("username", "N/A"))},
                {"bio", user.value("bio", nlohmann::json())},
                {"public_repos", static_cast<int>(user.value("projects", nlohmann::json::array()).size())},
                {"followers", user.value("followers", 0)},
                {"following", user.value("following", 0)},
                {"created_at", user.value("created_at", nlohmann::json())},
                {"updated_at", user.value("updated_at", nlohmann::json())},
                {"url", user.value("web_url", "N/A")}
            };
            return normalized;
        }
        return nlohmann::json::object();
    }

    std::string get_repos_raw(const std::string& username) {
        CURL* curl = curl_easy_init();
        std::string response;

        if (curl) {
            std::string url = "https://gitlab.com/api/v4/users/" + username + "/projects?visibility=public&per_page=100";
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
                {"full_name", repo.value("path_with_namespace", "N/A")},
                {"url", repo.value("web_url", "N/A")},
                {"description", repo.value("description", nlohmann::json())},
                {"stars", repo.value("star_count", 0)},
                {"language", repo.value("languages", nlohmann::json::array()).size() > 0 ? repo["languages"][0].value("name", nlohmann::json()) : nlohmann::json()},
                {"updated_at", repo.value("last_activity_at", nlohmann::json())},
                {"topics", repo.value("topics", repo.value("tag_list", nlohmann::json::array()))}
            };
            normalized_repos.push_back(normalized_repo);
        }
        return normalized_repos;
    }
}
