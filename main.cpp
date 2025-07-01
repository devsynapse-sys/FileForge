#include "FileManager/FileManager.hpp"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    FileManager fm;
    fm.run();
    return 0;
}