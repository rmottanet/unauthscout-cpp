#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace report {
    void render_user_report(const nlohmann::json& user_data);
    void render_repos_list(const nlohmann::json& repos_data);
    void render_intel_summary(const nlohmann::json& repos_data);
}
