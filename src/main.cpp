#include <iostream>
#include "cli/args.hpp"
#include "core/utils.hpp"
#include "github/api.hpp"
#include "gitlab/api.hpp"
#include "report/render.hpp"
#include "helpers/file.hpp"

int main(int argc, char* argv[]) {
    std::string username;
    bool run_github = false;
    bool run_gitlab = false;
    bool fetch_repos = false;
    bool summarize = false;
    bool raw_mode = false;
    bool pretty_json = false;
    bool save_flag = false;

    cli::parse_arguments(argc, argv, username, run_github, run_gitlab, fetch_repos, summarize, raw_mode, pretty_json, save_flag);

    if (run_github || run_gitlab) {
        if (username.empty()) {
            cli::show_help();
            return 0;
        }

        if (run_github) {
            std::string raw_gh_user = github::get_user_raw(username);
            auto normalized_gh_user = github::normalize_user(raw_gh_user);

            if (raw_mode) {
                std::cout << normalized_gh_user.dump(pretty_json ? 2 : -1) << std::endl;
            } else {
                report::render_user_report(normalized_gh_user);
            }

            if (save_flag) {
                helpers::save_response(username, normalized_gh_user);
            }

            if (fetch_repos) {
                std::string raw_gh_repos = github::get_repos_raw(username);
                auto normalized_gh_repos = github::normalize_repos(raw_gh_repos);

                if (raw_mode) {
                    std::cout << normalized_gh_repos.dump(pretty_json ? 2 : -1) << std::endl;
                } else {
                    report::render_repos_list(normalized_gh_repos);
                    if (summarize) {
                        report::render_intel_summary(normalized_gh_repos);
                    }
                }

                if (save_flag) {
                    helpers::save_response(username + "_repos", normalized_gh_repos);
                }
            }
        }

        if (run_gitlab) {
            std::string raw_gl_user = gitlab::get_user_raw(username);
            auto normalized_gl_user = gitlab::normalize_user(raw_gl_user);

            if (raw_mode) {
                std::cout << normalized_gl_user.dump(pretty_json ? 2 : -1) << std::endl;
            } else {
                report::render_user_report(normalized_gl_user);
            }

            if (save_flag) {
                helpers::save_response(username, normalized_gl_user);
            }

            if (fetch_repos) {
                std::string raw_gl_repos = gitlab::get_repos_raw(username);
                auto normalized_gl_repos = gitlab::normalize_repos(raw_gl_repos);

                if (raw_mode) {
                    std::cout << normalized_gl_repos.dump(pretty_json ? 2 : -1) << std::endl;
                } else {
                    report::render_repos_list(normalized_gl_repos);
                    if (summarize) {
                        report::render_intel_summary(normalized_gl_repos);
                    }
                }

                if (save_flag) {
                    helpers::save_response(username + "_repos", normalized_gl_repos);
                }
            }
        }
    }

    return 0;
}
