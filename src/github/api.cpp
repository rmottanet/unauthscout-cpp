#include <string>
#include <nlohmann/json.hpp>
#include "github/api.hpp"
#include "helpers/http_client.hpp"

namespace github {
    std::string get_user_raw(const std::string& username) {
        helpers::HttpClient http_client;
        std::string url = "https://api.github.com/users/" + username;
        return http_client.get(url);
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
        helpers::HttpClient http_client;
        std::string url = "https://api.github.com/users/" + username + "/repos";
        return http_client.get(url);
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
