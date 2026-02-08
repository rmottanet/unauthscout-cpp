#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include "helpers/file.hpp"

namespace helpers {
    void save_response(const std::string& username, const nlohmann::json& response) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d");
        std::string date = oss.str();

        std::string dirname = "output";
        mkdir(dirname.c_str(), 0755);

        std::string filename = dirname + "/" + username + "_" + date + ".json";
        std::ofstream out_file(filename);
        out_file << response.dump(2);
        out_file.close();
    }
}
