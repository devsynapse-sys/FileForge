#ifndef DIRECTORY_VIEWER_HPP
#define DIRECTORY_VIEWER_HPP

#include <filesystem>
#include <vector>
#include <string>
#include "../ConsoleUtils/ConsoleUtils.hpp"

namespace fs = std::filesystem;

class DirectoryViewer {
private:
    std::vector<std::pair<std::string, bool>> entries; 
    ConsoleUtils console;

public:
    void list_directory(const fs::path& path, bool interactive = false);
    const std::vector<std::pair<std::string, bool>>& get_entries() const;
};

#endif // DIRECTORY_VIEWER_HPP