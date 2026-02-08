#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace helpers {
    void save_response(const std::string& username, const nlohmann::json& response);
}
