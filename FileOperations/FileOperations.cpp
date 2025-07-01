#include "FileOperations.hpp"
#include <fstream>
#include <regex>
#include <iostream>

void FileOperations::change_directory(fs::path& current_path, const std::string& dir) {
    fs::path new_path = dir == ".." ? current_path.parent_path() : current_path / dir;
    if (fs::exists(new_path) && fs::is_directory(new_path)) {
        current_path = fs::canonical(new_path);
    }
    else {
        console.set_color(12);
        std::cout << "Error: Directory '" << dir << "' does not exist or is not a directory.\n";
        console.reset_color();
    }
}

void FileOperations::create_directory(const fs::path& current_path, const std::string& dir_name) {
    if (fs::create_directory(current_path / dir_name)) {
        std::cout << "Directory '" << dir_name << "' created successfully.\n";
    }
    else {
        console.set_color(12);
        std::cout << "Error: Failed to create directory '" << dir_name << "'.\n";
        console.reset_color();
    }
}

void FileOperations::copy_file(const fs::path& current_path, const std::string& source, const std::string& destination) {
    fs::path src_path = current_path / source;
    fs::path dest_path = current_path / destination;
    try {
        if (!fs::is_regular_file(src_path)) {
            console.set_color(12);
            std::cout << "Error: '" << source << "' is not a file.\n";
            console.reset_color();
            return;
        }
        uint64_t size = fs::file_size(src_path);
        std::ifstream in(src_path, std::ios::binary);
        std::ofstream out(dest_path, std::ios::binary);
        char buffer[8192];
        uint64_t copied = 0;
        while (in.read(buffer, sizeof(buffer))) {
            out.write(buffer, in.gcount());
            copied += in.gcount();
            std::cout << "\rCopying: " << (copied * 100 / size) << "%" << std::flush;
        }
        if (in.eof()) {
            out.write(buffer, in.gcount());
            copied += in.gcount();
            std::cout << "\rCopying: 100%\n";
            std::cout << "File '" << source << "' copied to '" << destination << "'.\n";
        }
        else {
            throw fs::filesystem_error("Read error", src_path, std::error_code());
        }
    }
    catch (const fs::filesystem_error& e) {
        console.set_color(12);
        std::cout << "Error: " << e.what() << "\n";
        console.reset_color();
    }
}

void FileOperations::move_file(const fs::path& current_path, const std::string& source, const std::string& destination) {
    fs::path src_path = current_path / source;
    fs::path dest_path = current_path / destination;
    try {
        fs::rename(src_path, dest_path);
        std::cout << "File '" << source << "' moved to '" << destination << "'.\n";
    }
    catch (const fs::filesystem_error& e) {
        console.set_color(12);
        std::cout << "Error: " << e.what() << "\n";
        console.reset_color();
    }
}

void FileOperations::remove(const fs::path& current_path, const std::string& name) {
    fs::path target = current_path / name;
    try {
        if (fs::is_directory(target)) {
            fs::remove_all(target);
            std::cout << "Directory '" << name << "' removed.\n";
        }
        else if (fs::is_regular_file(target)) {
            fs::remove(target);
            std::cout << "File '" << name << "' removed.\n";
        }
        else {
            console.set_color(12);
            std::cout << "Error: '" << name << "' does not exist.\n";
            console.reset_color();
        }
    }
    catch (const fs::filesystem_error& e) {
        console.set_color(12);
        std::cout << "Error: " << e.what() << "\n";
        console.reset_color();
    }
}

void FileOperations::create_file(const fs::path& current_path, const std::string& file_name) {
    std::ofstream file(current_path / file_name);
    if (file.is_open()) {
        std::cout << "File '" << file_name << "' created successfully.\n";
        file.close();
    }
    else {
        console.set_color(12);
        std::cout << "Error: Failed to create file '" << file_name << "'.\n";
        console.reset_color();
    }
}

void FileOperations::find_files(const fs::path& current_path, const std::string& pattern) {
    try {
        std::regex regex_pattern(pattern, std::regex::icase);
        std::cout << "Files matching '" << pattern << "':\n";
        for (const auto& entry : fs::recursive_directory_iterator(current_path)) {
            if (std::regex_match(entry.path().filename().string(), regex_pattern)) {
                std::cout << entry.path().string() << "\n";
            }
        }
    }
    catch (const std::regex_error& e) {
        console.set_color(12);
        std::cout << "Error: Invalid regex pattern '" << pattern << "'.\n";
        console.reset_color();
    }
}

void FileOperations::diff_files(const fs::path& current_path, const std::string& file1, const std::string& file2) {
    fs::path path1 = current_path / file1;
    fs::path path2 = current_path / file2;
    try {
        if (!fs::is_regular_file(path1) || !fs::is_regular_file(path2)) {
            console.set_color(12);
            std::cout << "Error: Both '" << file1 << "' and '" << file2 << "' must be files.\n";
            console.reset_color();
            return;
        }
        std::ifstream f1(path1, std::ios::binary);
        std::ifstream f2(path2, std::ios::binary);
        char c1, c2;
        size_t pos = 0;
        while (f1.get(c1) && f2.get(c2)) {
            if (c1 != c2) {
                std::cout << "Files differ at byte " << pos << "\n";
                return;
            }
            ++pos;
        }
        if (f1.eof() && f2.eof()) {
            std::cout << "Files are identical.\n";
        }
        else {
            std::cout << "Files differ in length.\n";
        }
    }
    catch (const std::exception& e) {
        console.set_color(12);
        std::cout << "Error: " << e.what() << "\n";
        console.reset_color();
    }
}