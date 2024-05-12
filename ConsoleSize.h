#pragma once
#include <iostream>
#include <Windows.h>

class ConsoleSize {
public:
    static std::pair<int, int> getConsoleSize() {

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return {
            rows,
            columns
        };
    }
};


