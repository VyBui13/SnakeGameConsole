#include "ConsoleSize.h"
#include "Game.h"
#include "Menu.h"
#include "HelpSystem.h"
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
            std::cout << newGame.drawSnake();
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
            "|  |  |   __|  |  |  _  |",
            "|     |   __|  |__|   __|",
            "|__|__|_____|_____|__|   "     
        },
        {             
            " _____ __ __ _____ _____ ",
            "|   __|  |  |     |_   _|",
            "|   __|-   -|-   -| | |  ",
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
            std::cout << newGame.drawPanel();
            std::cout << newGame.drawFruit();
            std::thread thread1(playGame, std::ref(newMenu));
            std::thread thread2(inputKey);
            thread2.join();
            thread1.join();
        }
        //PLAYGAME

        //HELP
        if (selected == 3) {
            HelpSystem help(80);
            std::cout << help.drawMainPannel();
            std::cout << help.drawInstructionLogo();
            std::cout << help.drawInstruction();
            system("pause");
        }
        //HELP


        //EXIT
        if (selected == 4) {
            break;
        }
        //EXIT

        system("cls");
    }
    //GOODBYE 
    std::vector<std::string> exit{
        "  /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$        /$$$$$$$  /$$     /$$ /$$$$$$$$",
        " /$$__  $$ /$$__  $$ /$$__  $$| $$__  $$      | $$__  $$|  $$   /$$/| $$_____/",
        "| $$  \\__/| $$  \\ $$| $$  \\ $$| $$  \\ $$      | $$  \\ $$ \\  $$ /$$/ | $$      ",
        "| $$ /$$$$| $$  | $$| $$  | $$| $$  | $$      | $$$$$$$   \\  $$$$/  | $$$$$   ",
        "| $$|_  $$| $$  | $$| $$  | $$| $$  | $$      | $$__  $$   \\  $$/   | $$__/   ",
        "| $$  \\ $$| $$  | $$| $$  | $$| $$  | $$      | $$  \\ $$    | $$    | $$      ",
        "|  $$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$/      | $$$$$$$/    | $$    | $$$$$$$$",
        " \\______/  \\______/  \\______/ |_______/       |_______/     |__/    |________/"

    };
    std::vector<std::string> snake{
        "                           @@@@@@@@@",
        "                          @@@@@@@@@@",
        "                          @@@@@@@@@@",
        "     @@@@@             @@@@@@@@@@@@ ",
        "  @@@@@@@@@@@@        @@@@@@@@      ", 
        "(@@@@@@@@@@@@@@@      @@@@@@@       ", 
        "@@@@@@@   @@@@@@@@@    @@@@@@@@     ", 
        " @@@@@@@@   @@@@@@@@@   @@@@@@@@@   ", 
        "   @@@@@@@@#   @@@@@@@@@   @@@@@@@@ ", 
        "     @@@@@@@@@   @@@@@@@@@   @@@@@@ ", 
        "       .@@@@@@@@    @@@@@@@@@@@@@@* ", 
        "@@@@@@@   @@@@@@@@    @@@@@@@@@@@   ", 
        "@@@@@@@@@   @@@@@@                  ", 
        "   @@@@@@@@@@@@@@@                  ", 
        "     @@@@@@@@@@@@                   "
    };
    std::vector<std::string> exitWord{
        "  ____  ____  _____ ____ ____       _    _   ___   __  ",
        " |  _ \\|  _ \\| ____/ ___/ ___|     / \\  | \\ | \\ \\ / /  ",
        " | |_) | |_) |  _| \\___ \\___ \\    / _ \\ |  \\| |\\ V /   ",
        " |  __/|  _ <| |___ ___) |__) |  / ___ \\| |\\  | | |    ",
        " |_| __|_|_\\_\\_____|____/____/  /_/___\\_\\_|_\\_|_|_|___ ",
        "| |/ / ____\\ \\ / / |_   _/ _ \\  | ____\\ \\/ /_ _|_   _|",
        "| ' /|  _|  \\ V /    | || | | | |  _|  \\  / | |  | |  ",
        "| . \\| |___  | |     | || |_| | | |___ /  \\ | |  | |  ",
        "|_|\\_\\_____| |_|     |_| \\___/  |_____/_/\\_\\___| |_|  "
    };

    //DRAW LINE
    int start = 3;
    auto console = ConsoleSize::getConsoleSize();
    std::string line(console.second, '*');
    std::cout << "\x1b[0;93m";
    std::cout << "\x1b[" << std::to_string(start) << ";0H";
    std::cout << line;
    std::cout << "\x1b[" << std::to_string(start + exit.size() + 1) << ";0H";
    std::cout << line;
    std::cout << "\x1b[0;0m";

    std::string newLine(console.second, '-');
    std::cout << "\x1b[0;96m";
    std::cout << "\x1b[" << std::to_string(start + exit.size() + 2) << ";0H";
    std::cout << newLine;
    std::cout << "\x1b[" << std::to_string(start - 1) << ";0H";
    std::cout << newLine;
    std::cout << "\x1b[0;0m";
    //DRAW LINE

    int minColumnSnake = 6;

    //DRAW SNAKE ICON
    std::cout << "\x1b[5;92m";
    for (int i = 0; i < snake.size(); i++) {
        std::cout << "\x1b[" << std::to_string(start + exit.size() + 4 + i) << ";6H";
        std::cout << snake[i];
    }
    std::cout << "\x1b[0;0m";
    //DRAW SNAKE ICON

    //DRAW EXIT NOTIFICATION
    size_t minColumnExitWord = minColumnSnake + snake[0].size() + 12;
    for (int i = 0; i < exitWord.size(); i++) {
        if (i <= 4) {
            std::cout << "\x1b[0;91m";
        }
        else {
            std::cout << "\x1b[0;96m";
        }
        std::cout << "\x1b[" << std::to_string(start + exit.size() + 7 + i) << ";" << std::to_string(minColumnExitWord) << "H";
        std::cout << exitWord[i];
    }
    std::cout << "\x1b[0;0m";
    //DRAW EXIT NOTIFICATION

    //DRAW "GOODBYE"
    start = 4;
    size_t minColumnExit = (console.second - exit[0].size()) / 2 + 1;
    for (int i = 1; i <= minColumnExit; i++) {
        std::string temp(i, ' ');
        for (int j = start; j < start + exit.size(); j++) {
            std::cout << "\x1b[" << std::to_string(j) << ";" << std::to_string(0) << "H";
            std::cout << temp;
            std::cout << "\x1b[" << std::to_string(j) << ";" << std::to_string(i) << "H";
            std::cout << exit[j - start];
        }
        Sleep(100);
    }
    //DRAW "GOODBYE"

    auto c = _getch();
    system("cls");
    return 0;
}
   