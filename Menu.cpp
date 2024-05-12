#include "Menu.h"
#include "ConsoleSize.h"

Menu::Menu() {
    auto console = ConsoleSize::getConsoleSize();
    minColumn = (console.second - 50) / 2 + 1;
    maxColumn = minColumn + logo[0].size() - 1;
    start = 0;
}

Menu::Menu(std::vector<std::string> logo, std::vector<std::vector<std::string>> feature) {
    auto console = ConsoleSize::getConsoleSize();
    this->logo = logo;
    minColumn = (console.second - 50) / 2 + 1;
    maxColumn = minColumn + logo[0].size() - 1;
    this->feature = feature;
    sizeFeature = this->feature[0].size() + 4;
    start = 1 + this->logo.size()  +1;
}

std::string Menu::drawLogo() {
    
    std::stringstream ss;
    
    for (int i = 1; i <= logo.size(); i++) {
        if (i & 1) {
            ss << "\x1b[0;33m";
        }
        else {
            ss << "\x1b[0;36m";
        }
        ss << "\x1b[" << std::to_string(i + 1) << ";" << std::to_string(minColumn) << "H";
        ss << logo[i - 1];
        if (i != logo.size()) {
            ss << "\n";
        }
    }
    ss << "\x1b[0;0m";
    return ss.str();
}

std::string Menu::drawPannel(int pos) {
    std::stringstream ss;
    ss << "\x1b[0;95m";
    for (int i = 0; i < 2; i++) {
        if (i == pos) {
            ss << "\x1b[0;95m";
        }
        else {
            ss << "\x1b[38;5;59m";
        }
        int rowTemp = start + i * sizeFeature;
        if (i != 0) rowTemp = rowTemp + 3;
        ss << "\x1b[" << std::to_string(rowTemp) << ";" << std::to_string(minColumn) << "H";
        for (int i = 0; i < (maxColumn - minColumn + 1); i++) {
            ss << "_";
        }
        for (int i = rowTemp + 1; i < rowTemp + sizeFeature + 1; i++) {
            ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(minColumn) << "H" << "|";
            ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(maxColumn) << "H" << "|";
        }
        ss << "\x1b[" << std::to_string(rowTemp + sizeFeature + 1) << ";" << std::to_string(minColumn) << "H";
        for (int i = 0; i < (maxColumn - minColumn + 1); i++) {
            if (i == 0 || i == (maxColumn - minColumn)) {
                ss << "|";
            }
            else {
                ss << "_";
            }
        }
    }
    ss << "\x1b[0;0;0m";
    return ss.str();
}

std::string Menu::drawPannel2(int pos) {
    std::stringstream ss;
    ss << "\x1b[0;95m";
    int minColumnPannel = minColumn - logo[0].size() / 2;
    int maxColumnPannel = minColumnPannel + logo[0].size();
    for (int i = 0; i < 2; i++) {
        if (i == pos) {
            ss << "\x1b[0;95m";
        }
        else {
            ss << "\x1b[38;5;59m";
        }
        int rowTemp = start + i * sizeFeature;

        if (i != 0) rowTemp = rowTemp + 3;
        ss << "\x1b[" << std::to_string(rowTemp) << ";" << std::to_string(minColumnPannel) << "H";
        
        //DRAW PANNEL COLUMN 1
        for (int i = 0; i < (maxColumnPannel - minColumnPannel + 1); i++) {
            ss << "_";
        }
        for (int i = rowTemp + 1; i < rowTemp + sizeFeature + 1; i++) {
            ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(minColumnPannel) << "H" << "|";
            ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(maxColumnPannel) << "H" << "|";
        }

        ss << "\x1b[" << std::to_string(rowTemp + sizeFeature + 1) << ";" << std::to_string(minColumnPannel) << "H";
        for (int i = 0; i < (maxColumnPannel - minColumnPannel + 1); i++) {
            if (i == 0 || i == (maxColumnPannel - minColumnPannel)) {
                ss << "|";
            }
            else {
                ss << "_";
            }
        }
        //DRAW PANNELCOLUMN 1
    }

    //DRAW PANNELCOLUMN 2
    for (int i = 2; i < 4; i++) {
        if (i == pos) {
            ss << "\x1b[0;95m";
        }
        else {
            ss << "\x1b[38;5;59m";
        }
        int rowTemp = start + (i - 2) * sizeFeature;
        if (i - 2 != 0) rowTemp = rowTemp + 3;

        ss << "\x1b[" << std::to_string(rowTemp) << ";" << std::to_string(maxColumnPannel + 2) << "H";
        for (int i = 0; i < (maxColumnPannel - minColumnPannel + 1); i++) {
            ss << "_";
        }

        for (int i = rowTemp + 1; i < rowTemp + sizeFeature + 1; i++) {
            ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(maxColumnPannel + 2) << "H" << "|";
            ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(maxColumnPannel + 2 + logo[0].size()) << "H" << "|";
        }
        ss << "\x1b[" << std::to_string(rowTemp + sizeFeature + 1) << ";" << std::to_string(maxColumnPannel + 2) << "H";
        for (int i = 0; i < (maxColumnPannel - minColumnPannel + 1); i++) {
            if (i == 0 || i == (maxColumnPannel - minColumnPannel)) {
                ss << "|";
            }
            else {
                ss << "_";
            }
        }
    }
    //DRAW PANNELCOLUMN 2

    ss << "\x1b[0;0;0m";
    return ss.str();
}

std::string Menu::drawMenu(int pos) {
    std::stringstream ss;
    int minColumnPannel = minColumn - logo[0].size() / 2;
    int maxColumnPannel = minColumnPannel + logo[0].size();
    for (int i = 0; i < 2; i++) {
        if (i == pos) {
            ss << "\x1b[38;5;226m";
        }
        else {
            ss << "\x1b[38;5;59m";
        }
        int size = feature[i][0].size();
        int newMinColumn = minColumnPannel + (logo[0].size() - size) / 2 + 1;
        int newMinRow = start + (sizeFeature - feature[0].size()) / 2 + i * sizeFeature + 1;
        if (i != 0) newMinRow = newMinRow + 3;
        for (int j = 0; j < feature[i].size(); j++) {
            ss << "\x1b[" << std::to_string(newMinRow + j) << ";" << std::to_string(newMinColumn) << "H";
            ss << feature[i][j];
        }
    }

    for (int i = 2; i < feature.size(); i++) {
        if (i == pos) {
            ss << "\x1b[38;5;226m";
        }
        else {
            ss << "\x1b[38;5;59m";
        }
        int size = feature[i][0].size();
        int newMinColumn = maxColumnPannel + 2 + (logo[0].size() - size) / 2 + 1;
        int newMinRow = start + (sizeFeature - feature[0].size()) / 2 + (i - 2) * sizeFeature + 1;
        if (i -2  != 0) newMinRow = newMinRow + 3;
        for (int j = 0; j < feature[i].size(); j++) {
            ss << "\x1b[" << std::to_string(newMinRow + j) << ";" << std::to_string(newMinColumn) << "H";
            ss << feature[i][j];
        }
    }

    return ss.str();
}

std::string Menu::gameOver() {
    
    std::vector<std::string> over = {
        "  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$        /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$ ",
        " /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/       /$$__  $$| $$   | $$| $$_____/| $$__  $$",
        "| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$            | $$  \\ $$| $$   | $$| $$      | $$  \\ $$",
        "| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$         | $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/",
        "| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/         | $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$",
        "| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$            | $$  | $$  \\  $$$/  | $$      | $$  \\ $$",
        "|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$      |  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$",
        " \\______/ |__/  |__/|__/     |__/|________/       \\______/     \\_/    |________/|__/  |__/"
    };
             
    auto console = ConsoleSize::getConsoleSize();
    int newMinColumn = (console.second - over[0].size()) / 2;
    std::stringstream ss;

    for (int i = 1; i <= over.size(); i++) {
        if (i & 1) {
            ss << "\x1b[0;33m";
        }
        else {
            ss << "\x1b[0;36m";
        }
        ss << "\x1b[" << std::to_string(i + 1) << ";" << std::to_string(newMinColumn) << "H";
        ss << over[i - 1];
        if (i != over.size()) {
            ss << "\n";
        }
    }
    ss << "\x1b[0;0m";
    return ss.str();

}

std::string Menu::drawFeature(std::vector<std::vector<std::string>> newFeature, int pos) {
    std::stringstream ss;
    for (int i = 0; i < newFeature.size(); i++) {
        if (i == pos) {
            ss << "\x1b[38;5;226m";
        }
        else {
            ss << "\x1b[38;5;59m";
        }
        int size = newFeature[i][0].size();
        int newMinColumn = minColumn + ((maxColumn - minColumn) - size) / 2;
        int newMinRow = start + (sizeFeature - feature.size()) / 2 + i * sizeFeature + 1;
        if (i != 0) newMinRow = newMinRow + 3;
        for (int j = 0; j < newFeature[i].size(); j++) {
            ss << "\x1b[" << std::to_string(newMinRow + j) << ";" << std::to_string(newMinColumn) << "H";
            ss << newFeature[i][j];
        }
    }

    return ss.str();
}

std::string Menu::exitGame() {
    std::vector<std::string> exit{
        "  /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$        /$$$$$$$  /$$     /$$ /$$$$$$$$",
        " /$$__  $$ /$$__  $$ /$$__  $$| $$__  $$      | $$__  $$|  $$   /$$/| $$_____/",
        "| $$  \__/| $$  \ $$| $$  \ $$| $$  \ $$      | $$  \ $$ \  $$ /$$/ | $$      ",
        "| $$ /$$$$| $$  | $$| $$  | $$| $$  | $$      | $$$$$$$   \  $$$$/  | $$$$$   ",
        "| $$|_  $$| $$  | $$| $$  | $$| $$  | $$      | $$__  $$   \  $$/   | $$__/   ",
        "| $$  \ $$| $$  | $$| $$  | $$| $$  | $$      | $$  \ $$    | $$    | $$      ",
        "|  $$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$/      | $$$$$$$/    | $$    | $$$$$$$$",
        " \______/  \______/  \______/ |_______/       |_______/     |__/    |________/"

    };

    std::stringstream ss;
    int start = 4;
    auto console = ConsoleSize::getConsoleSize();
    std::string line(console.second, '*');
    ss << "\x1b[" << std::to_string(start) << ";0H";
    ss << line;
    ss << "\x1b[" << std::to_string(start + exit.size() + 1) << ";0H";
    ss << line;

    start = 5;
    int minColumnExit = (console.second - exit[0].size()) / 2 + 1;
    int maxColumnExit = minColumnExit + exit[0].size() - 1;
    for (int i = -maxColumn + 1; i < maxColumnExit; i++) {
        
        for (int j = start; j < start + exit.size(); j++) {
            ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(i) << "H";
            ss << exit[i - start];
        }
        Sleep(400);
    }
    return ss.str();
}
