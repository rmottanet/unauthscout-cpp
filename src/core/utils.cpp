#include <iostream>
#include "core/utils.hpp"

namespace core {
    void log_info(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }

    void log_success(const std::string& message) {
        std::cout << "[OK] " << message << std::endl;
    }

    void log_warn(const std::string& message) {
        std::cerr << "[WARN] " << message << std::endl;
    }

    void log_error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }

    void check_dependencies() {
        // Implementação de verificação de dependências
    }
}
