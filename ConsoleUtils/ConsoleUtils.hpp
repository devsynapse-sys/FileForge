#ifndef CONSOLE_UTILS_HPP
#define CONSOLE_UTILS_HPP

#include <windows.h>
#include <string>

class ConsoleUtils {
private:
    HANDLE hConsole;

public:
    ConsoleUtils();
    void set_color(int color);
    void reset_color();
};

#endif // CONSOLE_UTILS_HPP