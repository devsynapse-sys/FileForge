#include "FileManager.hpp"
#include <iostream>
#include <sstream>

FileManager::FileManager() : current_path(std::filesystem::current_path()) {}

void FileManager::show_help() {
    std::cout << "\nAvailable commands:\n"
        << "  dir            - List directory contents\n"
        << "  select         - Interactive file/directory selection\n"
        << "  cd <path>      - Change directory (use '..' to go up)\n"
        << "  mkdir <name>   - Create a new directory\n"
        << "  cp <src> <dst> - Copy file\n"
        << "  mv <src> <dst> - Move/rename file\n"
        << "  rm <name>      - Remove file or directory\n"
        << "  touch <name>   - Create an empty text file\n"
        << "  find <pattern> - Find files by pattern (regex)\n"
        << "  diff <file1> <file2> - Compare two files\n"
        << "  help           - Show this help\n"
        << "  exit           - Exit the file manager\n\n";
}

void FileManager::run() {
    std::cout << "Simple C++ File Manager for Windows\nType 'help' for commands.\n";

    while (true) {
        std::cout << "\n" << current_path << "> ";
        std::string command;
        std::getline(std::cin, command);

        // Разбиваем команду на части
        std::vector<std::string> tokens;
        std::stringstream ss(command);
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }

        // Обработка команд
        if (tokens.empty()) continue;

        std::string cmd = tokens[0];
        if (cmd == "exit") break;
        else if (cmd == "help") show_help();
        else if (cmd == "dir") dir_viewer.list_directory(current_path);
        else if (cmd == "select") {
            dir_viewer.list_directory(current_path, true);
            std::cout << "Enter number to select (or -1 to cancel): ";
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            if (choice >= 0 && choice < static_cast<int>(dir_viewer.get_entries().size())) {
                const auto& [name, is_dir] = dir_viewer.get_entries()[choice];
                std::cout << "Selected: " << name << "\nActions: [1] Open (if dir) [2] Delete [3] Copy [4] Move\n";
                int action;
                std::cin >> action;
                std::cin.ignore();
                if (is_dir && action == 1) {
                    file_ops.change_directory(current_path, name);
                }
                else if (action == 2) {
                    file_ops.remove(current_path, name);
                }
                else if (action == 3) {
                    std::cout << "Enter destination name: ";
                    std::string dest;
                    std::getline(std::cin, dest);
                    file_ops.copy_file(current_path, name, dest);
                }
                else if (action == 4) {
                    std::cout << "Enter destination name: ";
                    std::string dest;
                    std::getline(std::cin, dest);
                    file_ops.move_file(current_path, name, dest);
                }
                else {
                    std::cout << "Invalid action.\n";
                }
            }
            else if (choice != -1) {
                std::cout << "Invalid selection.\n";
            }
        }
        else if (cmd == "cd" && tokens.size() == 2) file_ops.change_directory(current_path, tokens[1]);
        else if (cmd == "mkdir" && tokens.size() == 2) file_ops.create_directory(current_path, tokens[1]);
        else if (cmd == "cp" && tokens.size() == 3) file_ops.copy_file(current_path, tokens[1], tokens[2]);
        else if (cmd == "mv" && tokens.size() == 3) file_ops.move_file(current_path, tokens[1], tokens[2]);
        else if (cmd == "rm" && tokens.size() == 2) file_ops.remove(current_path, tokens[1]);
        else if (cmd == "touch" && tokens.size() == 2) file_ops.create_file(current_path, tokens[1]);
        else if (cmd == "find" && tokens.size() == 2) file_ops.find_files(current_path, tokens[1]);
        else if (cmd == "diff" && tokens.size() == 3) file_ops.diff_files(current_path, tokens[1], tokens[2]);
        else {
            std::cout << "Unknown command or wrong arguments. Type 'help' for commands.\n";
        }
    }
}