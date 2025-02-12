﻿#include "ConsoleSize.h"
#include "Game.h"
#include "Menu.h"
#include "HelpSystem.h"
#include "Option.h"
#include <ctime>
#include <stdlib.h>
#include <thread>
#include <conio.h>

auto consoleSize = ConsoleSize::getConsoleSize();
Game newGame({ 16, 80 });
unsigned char key = 'w';
unsigned char oldKey;
bool continueGame = true;
bool stopGame = false;
std::string headSnakeColor = "0;33m";
std::string bodySnakeColor = "0;36m";
std::string wallColor = "0;35m";

enum class MenuOption {
    Play,
    Option,
    Help,
    Exit
};

enum Keys : int {
    Arrow = 224,
    Up = 72,
    Down = 80,
    Left = 75,
    Right = 77,
    Escaped = 27,
    Enter = 13,
    Del = 83
};

enum class MenuOptionV2 {
    BackToMenu,
    Exit
};

void playGame(Menu menu) {
    //PLAYING GAME
    std::cout << newGame.drawPannelScore();
    
    while (!newGame.gameOver) {
        std::cout << newGame.drawCurrentSnake();
        std::cout << newGame.drawScore();
        std::cout << newGame.drawBestScore(2);
        std::cout << newGame.drawStatus(true);
        while (!stopGame) {
            std::cout << newGame.drawSnake(headSnakeColor, bodySnakeColor);
            //std::cout << newGame.deleteSnake();
            Sleep(newGame.timePush);
            newGame.control(key);
            if (newGame.gameOver) {
                stopGame = true;
            }
        }
    }
    //PLAYING GAME

    /*SNAKE DIED*/
    system("cls");
    std::vector<std::vector<std::string>> newFeature{
        {
            " _____ _____ _____ _____ ",
            "| __  |  _  |    _|  |  |",
            "| __ -|     |  --_|    -|",
            "|_____|__|__|_____|__|__|"
        },
        {
            " _____ __ __ _____ _____ ",
            "|   __|  |  |     |_   _|",
            "|   __|-   -|-   -| | |  ",
            "|_____|__|__|_____| |_|  ",
        }
    };
    int tempChoice = -1;
    bool check = true;
    MenuOptionV2 selectedOption = MenuOptionV2::BackToMenu;

    //GAMEOVER MENU
    while (true) {
        std::cout << menu.gameOver();
        for (int i = 0; i <= static_cast<int>(MenuOptionV2::Exit); i++) {
            if (selectedOption == static_cast<MenuOptionV2>(i)) {
                tempChoice = i;
                break;
            }
        }
        std::cout << menu.drawPannel(tempChoice);
        std::cout << menu.drawFeature(newFeature, tempChoice);
        unsigned char tempKey = _getch();
        if (tempKey == 'w' || tempKey == 'W') {
            selectedOption = static_cast<MenuOptionV2>(static_cast<int>(selectedOption) - 1);
            if (selectedOption < MenuOptionV2::BackToMenu) {
                selectedOption = MenuOptionV2::Exit;
            }
        }
        if (tempKey == 's' || tempKey == 'S'){
            selectedOption = static_cast<MenuOptionV2>(static_cast<int>(selectedOption) + 1);
            if (selectedOption > MenuOptionV2::Exit) {
                selectedOption = MenuOptionV2::BackToMenu;
            }

        }
        else {
            switch (tempKey) {
            case Keys::Enter: {
                switch (selectedOption) {
                case MenuOptionV2::Exit:
                    {
                        
                        continueGame = false;
                        break;
                    }
                default: {
                        newGame.resetGame();
                        stopGame = false;
                    }
                }
                check = false;
            }
            }
            if (!check)
                break;
        }

    }
    //GAMEOVER MENU
}

int chooseColor(Option& obj, std::string(Option::* func)(int), std::string(Option::* func2)(std::string) , int input, std::vector<std::pair<std::string, std::string>> color) {
    unsigned char optionColorKey = ';';
    int choiceColor = 0;
    while (optionColorKey != Keys::Escaped && optionColorKey != Keys::Enter) {
        std::cout << (obj.*func)(choiceColor);
        std::cout << (obj.*func2)(color[choiceColor].first);
        optionColorKey = _getch();
        if (optionColorKey == 'w' || optionColorKey == 'W') {
            choiceColor--;
        }
        else if (optionColorKey == 's' || optionColorKey == 'S') {
            choiceColor++;
        }
        else {
            continue;
        }

        if (choiceColor < 0) {
            choiceColor = color.size() - 1;
        }
        else if (choiceColor > color.size() - 1) {
            choiceColor = 0;
        }
    }
    return choiceColor;
}

void inputKey() {
    while (!newGame.gameOver) {
        if (key != Keys::Escaped)
            oldKey = key;
        key = _getch();
        if (oldKey == 'w' && key == 's') {
            key = 'w';
        }
        else if (oldKey == 's' && key == 'w') {
            key = 's';
        }
        else if (oldKey == 'a' && key == 'd') {
            key = 'a';
        }
        else if (oldKey == 'd' && key == 'a') {
            key = 'd';
        }
        else if (key == Keys::Escaped) {
            stopGame = true;
        }
        else if (key == Keys::Enter) {
            key = oldKey;
            stopGame = false;

        }
        else if (key != 'a' && key != 'd' && key != 'w' && key != 's') {
            key = oldKey;
        }
        Sleep(newGame.timePush);
    }
}

int main() {
    ConsoleSize::hiddenScreenPointer();

    std::vector<std::string> logo = {
        "  / $$$$$$ / $$  /$$  /$$$$$$  / $$  / $$/ $$$$$$$$",
        " / $$__$$ | $$$ | $$ /$$__  $$| $$  /$$/| $$_____/ ",
        "| $$  \\__/| $$$$| $$| $$  \\ $$| $$ /$$/ | $$       ",
        "| $$$$$$  | $$ $$ $$| $$$$$$$$| $$$$$/  | $$$$$    ",
        " \\____ $$ | $$  $$$$| $$__  $$| $$  $$  | $$__/    ",
        " /$$ \\ $$ | $$\\  $$$| $$  | $$| $$\\  $$ | $$       ",
        "| $$$$$$ /| $$ \\  $$| $$  | $$| $$ \\  $$| $$$$$$$$ ",
        " \\______/ |__/  \\__/|__/  |__/|__/  \\__/|________/ "
    };
    std::vector<std::vector<std::string>> feature{
        {
            " _____  __     _____  __ __ ",
            "|.._..||..|   |.._..||..|..|",
            "|...__||..|__ |.....||_..._|",
            "|__|   |_____||__|__|  |_|  "
        },
        {
            " _____  _____  _____  _____  _____  _____ ",
            "|.....||.._..||_..._||.....||.....||...|.|",
            "|..|..||...__|  |.|   |-.-| |..|..||.|.|.|",
            "|_____||__|     |_|  |_____||_____||_|___|"
        },
        {              
            " _____ _____ __    _____ ",
            "|..|..|...__|..|  |.._..|",
            "|.....|...__|..|__|...__|",
            "|__|__|_____|_____|__|   "     
        },
        {             
            " _____ __ __ _____ _____ ",
            "|...__|..|..|.....|_..._|",
            "|...__||-.-| |-.-|  |.|  ",
            "|_____|__|__|_____| |_|  "
        }
    };

    int choice = -1;
    int selected = -1;
    MenuOption selectedOption = MenuOption::Play;
    Menu newMenu(logo, feature);

    while (continueGame) {
        bool check = true;
        std::cout << newMenu.drawLogo();

        //MAIN MENU
        while (true) {
            for (int i = 0; i <= static_cast<int>(MenuOption::Exit); i++) {
                if (selectedOption == static_cast<MenuOption>(i)) {
                    choice = i;
                    break;
                }
            }
            std::cout << newMenu.drawPannel2(choice);
            std::cout << newMenu.drawMenu(choice);
            unsigned char tempKey = _getch();
            if (tempKey == 'w' || tempKey == 'W') {
                MenuOption tempSelectedOption = static_cast<MenuOption>(static_cast<int>(selectedOption) - 1);
                if (selectedOption == MenuOption::Play || selectedOption == MenuOption::Help) {
                    continue;
                }
                selectedOption = tempSelectedOption;
            }
            if (tempKey == 's' || tempKey == 'S') {
                MenuOption tempSelectedOption = static_cast<MenuOption>(static_cast<int>(selectedOption) + 1);
                if (selectedOption == MenuOption::Option || selectedOption == MenuOption::Exit) {
                    continue;
                }
                selectedOption = tempSelectedOption;
            }
            if (tempKey == 'a' || tempKey == 'A') {
                MenuOption tempSelectedOption = static_cast<MenuOption>(static_cast<int>(selectedOption) - 2);
                if (selectedOption == MenuOption::Play || selectedOption == MenuOption::Option) {
                    continue;
                }
                selectedOption = tempSelectedOption;
            }
            if (tempKey == 'd' || tempKey == 'D') {
                MenuOption tempSelectedOption = static_cast<MenuOption>(static_cast<int>(selectedOption) + 2);
                if (selectedOption == MenuOption::Help || selectedOption == MenuOption::Exit) {
                    continue;
                }
                selectedOption = tempSelectedOption;
            }
            else {
                switch (tempKey) {
                case Keys::Enter: {
                    switch (selectedOption) {
                    case MenuOption::Exit:
                    {
                        selected = 4;
                        break;
                    }
                    case MenuOption::Help:
                    {
                        selected = 3;
                        break;
                    }
                    case MenuOption::Option:
                    {
                        selected = 2;
                        break;
                    }
                    default:
                        selected = 1;
                    }
                    check = false;
                }
                }
                if (!check) {
                    break;
                }
            }

        }
        //MAIN MENU

        system("cls");

        //PLAY GAME
        if (selected == 1) {
            std::cout << newGame.drawPanel(wallColor);
            std::cout << newGame.drawFruit();
            std::thread thread1(playGame, std::ref(newMenu));
            std::thread thread2(inputKey);
            thread2.join();
            thread1.join();
        }
        //PLAYGAME

        //OPTION
        if (selected == 2) {
            std::vector<std::string> logo{
                " _____ _____ _____ _____ _____ _   _ _____  ",
                "/  ___|  ___|_   _|_   _|_   _| \\ | |  __ \\ ",
                "\\ `--.| |__   | |   | |   | | |  \\| | |  \\/ ",
                " `--. \\  __|  | |   | |   | | | . ` | | __  ",
                "/\\__/ / |___  | |   | |  _| |_| |\\  | |_\\ \\ ",
                "\\____/\\____/  \\_/   \\_/  \\___/\\_| \\_/\\____/ "
            };
            std::vector<std::pair<std::string, std::string>> color{
                {"0;31m", "Red"},
                {"0;32m", "Green"},
                {"0;33m", "Yellow"},
                {"0;34m", "Blue"},
                {"0;35m", "Magenta"},
                {"0;36m", "Cyan"},
                {"0;37m", "White"},
                {"0;30m", "Black"},
            };
            Option newOption(80, logo, color);
            std::cout << newOption.drawMainPannel();
            std::cout << newOption.drawSettingLogo();
            std::cout << newOption.drawSmallPannel();
            std::cout << newOption.drawHeadColorHeader();
            std::cout << newOption.drawBodyColorHeader();
            std::cout << newOption.drawWallColorHeader();
            std::cout << newOption.drawSignature();
            std::cout << newOption.drawExampleWall(wallColor);
            std::cout << newOption.drawExampleHeadSnake(headSnakeColor);
            std::cout << newOption.drawExampleBodySnake(bodySnakeColor);


            int choice = 1;
            while (true) {
                unsigned char optionKey = 'l';
                while (optionKey != Keys::Escaped && optionKey != Keys::Enter) {
                    std::cout << newOption.drawBody(choice);
                    optionKey = _getch();
                    if (optionKey == 'w' || optionKey == 'W') {
                        choice--;
                    }
                    else if (optionKey == 's' || optionKey == 'S') {
                        choice++;
                    }
                    else {
                        continue;
                    }

                    if (choice < 1) {
                        choice = 3;
                    }
                    else if (choice > 3) {
                        choice = 1;
                    }
                }

                if (optionKey == Keys::Escaped) {
                    break;
                }
                if (choice == 1) {
                    std::string(Option::* ptr2)(std::string) = &Option::drawExampleHeadSnake;
                    std::string(Option:: * ptr)(int) = &Option::chooseHeadColor;
                    int result = chooseColor(newOption, ptr, ptr2, 0, color);
                    headSnakeColor = color[result].first;
                }
                else if (choice == 2) {
                    std::string(Option::* ptr2)(std::string) = &Option::drawExampleBodySnake;
                    std::string(Option:: * ptr)(int) = &Option::chooseBodyColor;
                    int result = chooseColor(newOption, ptr, ptr2, 0, color);
                    bodySnakeColor = color[result].first;
                }
                else {
                    std::string(Option:: * ptr)(int) = &Option::chooseWallColor;
                    std::string(Option::* ptr2)(std::string) = &Option::drawExampleWall;

                    int result = chooseColor(newOption, ptr,ptr2, 0, color);
                    wallColor = color[result].first;
                }
            }
        }
        //OPTION

        //HELP
        if (selected == 3) {
            bool isLoop = true;
            unsigned char c = 'w';
            HelpSystem help(90);
            while (isLoop) {
                std::cout << help.drawMainPannel();
                std::cout << help.drawInstructionLogo();
                std::cout << help.drawInstruction();
                std::cout << help.drawSmallPannel(c);
                c = _getch();
                if (c == Keys::Escaped) {
                    isLoop = false;
                }
            }
        }
        //HELP

        //EXIT
        if (selected == 4) {
            break;
        }
        //EXIT

        system("cls");
    }
    newMenu.exitGame();

    auto c = _getch();
    system("cls");
    return 0;
}
   