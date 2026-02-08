#pragma once
#include <string>

namespace core {
    void log_info(const std::string& message);
    void log_success(const std::string& message);
    void log_warn(const std::string& message);
    void log_error(const std::string& message);
    void check_dependencies();
}
