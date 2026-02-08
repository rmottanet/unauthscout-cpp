#include <iostream>
#include <string>
#include <cstdlib>
#include "cli/args.hpp"
#include "core/utils.hpp"

namespace cli {
    void show_help() {
        std::cout << "UnauthScout v0.3.0 - Unified OSINT Reconnaissance for GitLab & GitHub\n";
        std::cout << "Usage:\n";
        std::cout << "    unauthscout [options] <username>\n";
        std::cout << "Arguments:\n";
        std::cout << "    <username>      The target git username to scout.\n";
        std::cout << "Platform Filters:\n";
        std::cout << "    -gh, --github   Search only on GitHub.\n";
        std::cout << "    -gl, --gitlab   Search only on GitLab.\n";
        std::cout << "Recon & Intelligence:\n";
        std::cout << "    -r, --repos     Fetch and list public repositories/projects.\n";
        std::cout << "    -s, --summarize Generate an intelligence summary.\n";
        std::cout << "Output Formatting:\n";
        std::cout << "    --raw           Output unified JSON.\n";
        std::cout << "    --pretty        Indents JSON output for human readability.\n";
        std::cout << "    --save          Save the API response to a JSON file.\n";
        std::cout << "General Options:\n";
        std::cout << "    -h, --help      Show this help message and exit.\n";
        std::cout << "    -v, --version   Show version information and exit.\n";
        exit(0);
    }

    void show_version() {
        std::cout << "UnauthScout v0.3.0\n";
        exit(0);
    }

    void parse_arguments(int argc, char* argv[], std::string& username, bool& run_github, bool& run_gitlab, bool& fetch_repos, bool& summarize, bool& raw_mode, bool& pretty_json, bool& save_flag) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--help" || arg == "-h") {
                show_help();
            } else if (arg == "--version" || arg == "-v") {
                show_version();
            } else if (arg == "--github" || arg == "-gh") {
                run_github = true;
            } else if (arg == "--gitlab" || arg == "-gl") {
                run_gitlab = true;
            } else if (arg == "--repos" || arg == "-r") {
                fetch_repos = true;
            } else if (arg == "--summarize" || arg == "-s") {
                summarize = true;
            } else if (arg == "--raw") {
                raw_mode = true;
            } else if (arg == "--pretty") {
                pretty_json = true;
            } else if (arg == "--save") {
                save_flag = true;
            } else if (arg[0] != '-') {
                username = arg;
            }
        }

        if (username.empty()) {
            show_help();
        }

        if (!run_github && !run_gitlab) {
            run_github = true;
            run_gitlab = true;
        }
    }
}
