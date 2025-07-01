#include "DirectoryViewer.hpp"
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <iostream>

void DirectoryViewer::list_directory(const fs::path& path, bool interactive) {
    entries.clear();
    console.set_color(7);
    std::cout << "\nCurrent directory: " << path << "\n\n";
    std::cout << std::setw(50) << std::left << "Name"
        << std::setw(20) << "Size"
        << std::setw(25) << "Last Modified" << "\n";
    std::cout << std::string(95, '-') << "\n";

    for (const auto& entry : fs::directory_iterator(path)) {
        std::string name = entry.path().filename().string();
        bool is_dir = entry.is_directory();
        entries.emplace_back(name, is_dir);
    }

    std::sort(entries.begin(), entries.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return std::lexicographical_compare(
            a.first.begin(), a.first.end(),
            b.first.begin(), b.first.end(),
            [](char c1, char c2) { return std::tolower(c1) < std::tolower(c2); }
        );
        });

    for (size_t i = 0; i < entries.size(); ++i) {
        const auto& [name, is_dir] = entries[i];
        fs::path entry_path = path / name;
        std::string size_str = is_dir ? "<DIR>" : std::to_string(fs::file_size(entry_path)) + " bytes";
        auto mod_time = fs::last_write_time(entry_path);
        auto time_point = std::chrono::time_point_cast<std::chrono::system_clock::duration>(mod_time - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
        std::time_t tt = std::chrono::system_clock::to_time_t(time_point);
        std::string time_str = std::ctime(&tt);
        time_str = time_str.substr(0, time_str.length() - 1);

        if (interactive) std::cout << "[" << i << "] ";
        console.set_color(is_dir ? 10 : 11);
        std::cout << std::setw(50 - (interactive ? 4 : 0)) << std::left << name
            << std::setw(20) << size_str
            << std::setw(25) << time_str << "\n";
        console.reset_color();
    }
    std::cout << "\n";
}

const std::vector<std::pair<std::string, bool>>& DirectoryViewer::get_entries() const {
    return entries;
}