#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace gitlab {
    std::string get_user_raw(const std::string& username);
    nlohmann::json normalize_user(const std::string& raw_user);
    std::string get_repos_raw(const std::string& username);
    nlohmann::json normalize_repos(const std::string& raw_repos);
}
