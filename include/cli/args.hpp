#pragma once
#include <string>

namespace cli {
    void show_help();
    void show_version();
    void parse_arguments(int argc, char* argv[], std::string& username, bool& run_github, bool& run_gitlab, bool& fetch_repos, bool& summarize, bool& raw_mode, bool& pretty_json, bool& save_flag);
}
