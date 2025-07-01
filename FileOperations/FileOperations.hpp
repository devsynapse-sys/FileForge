#ifndef FILE_OPERATIONS_HPP
#define FILE_OPERATIONS_HPP

#include <filesystem>
#include <string>
#include "../ConsoleUtils/ConsoleUtils.hpp"

namespace fs = std::filesystem;

class FileOperations {
private:
    ConsoleUtils console;

public:
    void change_directory(fs::path& current_path, const std::string& dir);
    void create_directory(const fs::path& current_path, const std::string& dir_name);
    void copy_file(const fs::path& current_path, const std::string& source, const std::string& destination);
    void move_file(const fs::path& current_path, const std::string& source, const std::string& destination);
    void remove(const fs::path& current_path, const std::string& name);
    void create_file(const fs::path& current_path, const std::string& file_name);
    void find_files(const fs::path& current_path, const std::string& pattern);
    void diff_files(const fs::path& current_path, const std::string& file1, const std::string& file2);
};

#endif // FILE_OPERATIONS_HPP