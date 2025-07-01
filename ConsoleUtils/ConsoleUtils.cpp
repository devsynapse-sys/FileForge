#include "ConsoleUtils.hpp"

ConsoleUtils::ConsoleUtils() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleUtils::set_color(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void ConsoleUtils::reset_color() {
    SetConsoleTextAttribute(hConsole, 7); 
}