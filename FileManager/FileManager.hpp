#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include "../DirectoryViewer/DirectoryViewer.hpp"
#include "../FileOperations/FileOperations.hpp"
#include <string>

class FileManager {
private:
    std::filesystem::path current_path;
    DirectoryViewer dir_viewer;
    FileOperations file_ops;

    void show_help();

public:
    FileManager();
    void run();
};

#endif // FILE_MANAGER_HPP