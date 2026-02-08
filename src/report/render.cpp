#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "report/render.hpp"

namespace report {
    void render_user_report(const nlohmann::json& user_data) {
        std::string platform = user_data.value("platform", "N/A");
        std::string handle = user_data.value("handle", "N/A");
        std::string name = user_data.value("name", "N/A");
        std::string profile_url = user_data.value("url", "N/A");
        std::string bio = user_data.value("bio", nlohmann::json()).is_null() ? "N/A" : user_data.value("bio", "N/A");

        std::cout << "\n[" << platform << " PROFILE: @" << handle << "]\n";
        std::cout << "Name:    " << name << "\n";
        std::cout << "Link:    " << profile_url << "\n";
        if (bio != "N/A") {
            std::cout << "Bio:     " << bio << "\n";
        }
    }

    void render_repos_list(const nlohmann::json& repos_data) {
        if (repos_data.empty() || repos_data.is_null()) {
            return;
        }

        std::cout << "\nTop Public Repositories (Unified Intel):\n";
        std::cout << std::left << std::setw(20) << "Updated At"
                  << std::setw(30) << "Full Name"
                  << std::setw(15) << "Language"
                  << "Stars\n";
        std::cout << std::string(80, '-') << "\n";

        for (const auto& repo : repos_data) {
            std::string updated_at = repo.value("updated_at", nlohmann::json()).is_null() ? "N/A" : repo.value("updated_at", "N/A").substr(0, 10);
            std::string full_name = repo.value("full_name", "N/A");
            std::string language = repo.value("language", nlohmann::json()).is_null() ? "N/A" : repo.value("language", "N/A");
            std::string stars = std::to_string(repo.value("stars", 0));

            std::cout << std::left << std::setw(20) << updated_at
                      << std::setw(30) << full_name
                      << std::setw(15) << language
                      << stars << "★\n";
        }
    }

    void render_intel_summary(const nlohmann::json& repos_data) {
        if (repos_data.empty() || repos_data.is_null()) {
            return;
        }

        int total_stars = 0;
        std::string top_repo_name;
        int top_repo_stars = 0;
        std::map<std::string, int> language_counts;

        for (const auto& repo : repos_data) {
            int stars = repo.value("stars", 0);
            total_stars += stars;

            if (stars > top_repo_stars) {
                top_repo_stars = stars;
                top_repo_name = repo.value("full_name", "N/A");
            }

            std::string language = repo.value("language", nlohmann::json()).is_null() ? "N/A" : repo.value("language", "N/A");
            if (language != "N/A") {
                language_counts[language]++;
            }
        }

        std::vector<std::pair<std::string, int>> sorted_languages(language_counts.begin(), language_counts.end());
        std::sort(sorted_languages.begin(), sorted_languages.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });

        std::string top_languages;
        for (size_t i = 0; i < std::min(sorted_languages.size(), static_cast<size_t>(3)); ++i) {
            if (i > 0) {
                top_languages += ", ";
            }
            top_languages += sorted_languages[i].first;
        }

        std::string last_activity;
        if (!repos_data.empty()) {
            std::vector<std::string> activities;
            for (const auto& repo : repos_data) {
                std::string updated_at = repo.value("updated_at", nlohmann::json()).is_null() ? "N/A" : repo.value("updated_at", "N/A").substr(0, 10);
                activities.push_back(updated_at);
            }
            std::sort(activities.begin(), activities.end());
            last_activity = activities.back();
        }

        std::cout << "\n[ 🧠 RECON INTELLIGENCE SUMMARY ]\n";
        std::cout << "Total Stars:    " << total_stars << "★\n";
        std::cout << "Top Languages:  " << (top_languages.empty() ? "N/A" : top_languages) << "\n";
        std::cout << "Most Starred:   " << top_repo_name << " (" << top_repo_stars << "★)\n";
        std::cout << "Latest Activity: " << last_activity << "\n";
    }
}
