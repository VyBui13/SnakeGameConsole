#include "Game.h"
#include "randomInteger.h"
#include <conio.h>
#include <Windows.h>
#include "ConsoleSize.h"

std::vector<int> oldPosX(1);
std::vector<int> oldPosY(1);
int maxRow;
int minRow;
int maxColumn;
int minColumn;
auto console = ConsoleSize::getConsoleSize();

Game::Game() {
    gameOver = false;
    xStart = 1;
    yStart = 1;
    timePush = 400;
}

Game::Game(std::pair<int, int> _size) {
    size = _size;
    minRow = 1;
    maxRow = console.first;
    minColumn = 1;
    maxColumn = size.second;
    gameOver = false;
    timePush = 400;
    yStart = (maxRow + minRow + 1) / 2;
    xStart = (maxColumn + minColumn + 1) / 2;;
    theChosenSnake.setLocation(xStart, yStart);
    oldPosX[0] = xStart;
    oldPosY[0] = yStart;
    
    apple.y = randomInteger::random(minRow + 1, maxRow - 1);
    apple.x = randomInteger::random(minColumn + 1, maxColumn - 1);
}

int Game::getSizeSnake() {
    return theChosenSnake.nTail;
}

std::string Game::drawPanel() {
    std::stringstream ss;
    auto console = ConsoleSize::getConsoleSize();
    ss << "\x1b[s";
    ss << "\x1b[0;35m";
    
    ss << "\x1b[" << std::to_string(minRow) << ";" << std::to_string(minColumn) << "H";
    for (int i = 0; i < size.second; i++) {
        ss << "#";
    }
    for (int i = 1; i < maxRow - minRow; i++) {
        ss << "\x1b[" << std::to_string(i + minRow) << ";" << std::to_string(minColumn) << "H" << "#";
        ss << "\x1b[" << std::to_string(i + minRow) << ";" << std::to_string(maxColumn) << "H" << "#";
    }
    ss << "\x1b[" << std::to_string(maxRow) << ";" << std::to_string(minColumn) << "H";
    for (int i = 0; i < size.second; i++) {
        ss << "#";
    }
    ss << "\x1b[0;0m";

    ss << "\x1b[u";
    ss << "\x1b[" << std::to_string(console.first) << ";" << std::to_string(console.second) << "H";
    return ss.str();
}

std::string Game::drawFruit() {
    std::stringstream ss;
    ss << "\x1b[0;31m";
    ss << "\x1b[" << std::to_string(apple.y) << ";"
        << std::to_string(apple.x) << "H";
    ss << "o";
    ss << "\x1b[0;0m";
    return ss.str();
}

std::string Game::drawSnake() {
    std::stringstream ss;
    for (int i = 0; i < theChosenSnake.nTail; i++) {
        if (i == 0) {
            ss << "\x1b[0;33m";
        }
        else {
            ss << "\x1b[0;36m";
        }
        ss << "\x1b[" << std::to_string(theChosenSnake.tailY[i]) << ";"
            << std::to_string(theChosenSnake.tailX[i]) << "H";
        ss << "o";

        ss << "\x1b[" << std::to_string(oldPosY[i]) << ";"
            << std::to_string(oldPosX[i]) << "H";
        ss << " ";
      
    }
    ss << "\x1b[0;0m";
    ss << "\x1b[" << std::to_string(console.first) << ";" << std::to_string(console.second) << "H";
    return ss.str();
}

std::string Game::drawCurrentSnake() {
    std::stringstream ss;
    for (int i = 0; i < theChosenSnake.nTail; i++) {
        if (i == 0) {
            ss << "\x1b[0;33m";
        }
        else {
            ss << "\x1b[0;36m";
        }
        ss << "\x1b[" << std::to_string(theChosenSnake.tailY[i]) << ";"
            << std::to_string(theChosenSnake.tailX[i]) << "H";
        ss << "o";
    }
    ss << "\x1b[0;0m";
    ss << "\x1b[" << std::to_string(console.first) << ";" << std::to_string(console.second) << "H";
    return ss.str();
}


enum Keys : int {
    Arrow = 224,
    Up = 72,
    Down = 80,
    Left = 75,
    Right = 77,
    Escaped = 27
};

void Game::control(unsigned char key) {

    if (key == Keys::Up || key == 'w' || key == 'W') {
        int temp = yStart - 1;
        for (int i = 0; i < theChosenSnake.nTail; i++) {
            if (xStart == theChosenSnake.tailX[i] && temp == theChosenSnake.tailY[i]) {
                gameOver = true;
                return;
            }
        }
        yStart--;
    }
    else if (key == Keys::Down || key == 's' || key == 'S') {
        int temp = yStart + 1;
        for (int i = 0; i < theChosenSnake.nTail; i++) {
            if (xStart == theChosenSnake.tailX[i] && temp == theChosenSnake.tailY[i]) {
                gameOver = true;
                return;
            }
        }
        yStart++;
    }
    else if (key == Keys::Left || key == 'a' || key == 'A') {
        int temp = xStart - 1;
        for (int i = 0; i < theChosenSnake.nTail; i++) {
            if (temp == theChosenSnake.tailX[i] && yStart == theChosenSnake.tailY[i]) {
                gameOver = true;
                return;
            }
        }
        xStart--;
    }
    else if (key == Keys::Right || key == 'd' || key == 'D') {
        int temp = xStart + 1;
        for (int i = 0; i < theChosenSnake.nTail; i++) {
            if (temp == theChosenSnake.tailX[i] && yStart == theChosenSnake.tailY[i]) {
                gameOver = true;
                return;
            }
        }
        xStart++;
    }
    else if (key == Keys::Escaped) {
        return;
    }

    if (xStart == apple.x && yStart == apple.y) {
        bool check = false;
        theChosenSnake.nTail++;
        if (timePush > 50)
            timePush -= 30;
        theChosenSnake.tailX.resize(theChosenSnake.nTail);
        theChosenSnake.tailY.resize(theChosenSnake.nTail);
        do {
            apple.y = randomInteger::random(minRow + 1, maxRow - 1);
            apple.x = randomInteger::random(minColumn + 1, maxColumn - 1);
            for (int i = 0; i < theChosenSnake.nTail; i++) {
                if (apple.x == theChosenSnake.tailX[i] && apple.y == theChosenSnake.tailY[i]) {
                    check = true;
                    break;
                }
            }
        } while (check);
        std::cout << drawFruit();
    }
    else if (xStart == minColumn || yStart == minRow || xStart == maxColumn || yStart == maxRow) {
        gameOver = true;
        return;
    }
    oldPosX = theChosenSnake.tailX;
    oldPosY = theChosenSnake.tailY;

    int prevX = theChosenSnake.tailX[0];
    int prevY = theChosenSnake.tailY[0];

    theChosenSnake.tailX[0] = xStart;
    theChosenSnake.tailY[0] = yStart;

    int prevX_2 = 0;
    int prevY_2 = 0;
    for (int i = 1; i < theChosenSnake.nTail; i++) {
        prevX_2 = theChosenSnake.tailX[i];
        prevY_2 = theChosenSnake.tailY[i];
        
        theChosenSnake.tailX[i] = prevX;
        theChosenSnake.tailY[i] = prevY;

        prevX = prevX_2;
        prevY = prevY_2;
    }
}

void Game::resetGame() {
    minRow = 1;
    maxRow = console.first;
    minColumn = 1;
    maxColumn = size.second;
    gameOver = false;
    timePush = 400;
    yStart = (maxRow + minRow + 1) / 2;
    xStart = (maxColumn + minColumn + 1) / 2;;
    theChosenSnake.tailX.resize(1);
    theChosenSnake.tailY.resize(1);
    theChosenSnake.nTail = 1;
    theChosenSnake.setLocation(xStart, yStart);
    oldPosX.resize(1);
    oldPosY.resize(1);

    oldPosX[0] = xStart;
    oldPosY[0] = yStart;

    apple.y = randomInteger::random(minRow + 1, maxRow - 1);
    apple.x = randomInteger::random(minColumn + 1, maxColumn - 1);
}

std::string Game::drawPannelScore() {
    int minColumnScore = maxColumn + 2;
    std::stringstream ss;
    std::string line(console.second - maxColumn - 1, '*');
    ss << "\x1b[0;" << std::to_string(minColumnScore) << "H";
    ss << line;
    for (int i = 2; i <= console.first - 1; i++) {
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(minColumnScore) << "H" << "*";
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(console.second) << "H" << "*";
    }
    ss << "\x1b[" << std::to_string(console.first) << ";" << std::to_string(minColumnScore) << "H";
    ss << line;
    for (int i = 1; i <= console.first; i++) {
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(minColumnScore - 1) << "H" << "|";

    }
    return ss.str();
}

const int heightScorePannel = 7;
const int widthScorePannel = 21;
const int widthLine = ((console.first - 2) - (heightScorePannel * 3)) / 4;


std::string Game::drawScore() {
    int scoreStartRow = 1 + widthLine + 1;
    int sizeScorePannel = console.second - size.second;
    int scoreStartColumn = maxColumn + 2 + (sizeScorePannel - widthScorePannel) / 2 + 1;
    std::stringstream ss;
    std::string line(widthScorePannel, '*');
    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    std::string score = "SCORE";
    size_t wordScoreStartColumn = scoreStartColumn + (widthScorePannel - 2 - score.size()) / 2 + 1;
    ss << "\x1b[" << std::to_string(scoreStartRow) << ";" << std::to_string(wordScoreStartColumn) << "H";
    ss << score;
    ss << "\x1b[" << std::to_string(scoreStartRow) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << "*";
    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn + widthScorePannel -1) << "H";
    ss << "*";

    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    for (int i = scoreStartRow; i < scoreStartRow + heightScorePannel - 4; i++) {
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(scoreStartColumn) << "H";
        ss << "*";
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(scoreStartColumn + widthScorePannel - 1) << "H";
        ss << "*";
    }
    ss << "\x1b[" << std::to_string(scoreStartRow + heightScorePannel - 4) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    return ss.str();
}

std::string Game::drawStatus(bool stopGame) {
    int scoreStartRow = 1 + 3 * widthLine + 2 * heightScorePannel + 1;
    int sizeScorePannel = console.second - size.second;
    int scoreStartColumn = maxColumn + 2 + (sizeScorePannel - widthScorePannel) / 2 + 1;
    std::stringstream ss;
    std::string line(widthScorePannel, '*');
    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    std::string score = "STATUS";
    size_t wordScoreStartColumn = scoreStartColumn + (widthScorePannel - 2 - score.size()) / 2 + 1;
    ss << "\x1b[" << std::to_string(scoreStartRow) << ";" << std::to_string(wordScoreStartColumn) << "H";
    ss << score;
    ss << "\x1b[" << std::to_string(scoreStartRow) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << "*";
    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn + widthScorePannel - 1) << "H";
    ss << "*";

    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    for (int i = scoreStartRow; i < scoreStartRow + heightScorePannel - 4; i++) {
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(scoreStartColumn) << "H";
        ss << "*";
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(scoreStartColumn + widthScorePannel - 1) << "H";
        ss << "*";
    }
    ss << "\x1b[" << std::to_string(scoreStartRow + heightScorePannel - 4) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    return ss.str();
}

std::string Game::drawBestScore(int bestScore) {
    int scoreStartRow = 1 + 2 * widthLine + heightScorePannel + 1;
    int sizeScorePannel = console.second - size.second;
    int scoreStartColumn = maxColumn + 2 + (sizeScorePannel - widthScorePannel) / 2 + 1;
    std::stringstream ss;
    std::string line(widthScorePannel, '*');
    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    std::string score = "BESTSCORE";
    size_t wordScoreStartColumn = scoreStartColumn + (widthScorePannel - 2 - score.size()) / 2 + 1;
    ss << "\x1b[" << std::to_string(scoreStartRow) << ";" << std::to_string(wordScoreStartColumn) << "H";
    ss << score;
    ss << "\x1b[" << std::to_string(scoreStartRow) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << "*";
    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn + widthScorePannel - 1) << "H";
    ss << "*";

    ss << "\x1b[" << std::to_string(scoreStartRow++) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    for (int i = scoreStartRow; i < scoreStartRow + heightScorePannel - 4; i++) {
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(scoreStartColumn) << "H";
        ss << "*";
        ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(scoreStartColumn + widthScorePannel - 1) << "H";
        ss << "*";
    }
    ss << "\x1b[" << std::to_string(scoreStartRow + heightScorePannel - 4) << ";" << std::to_string(scoreStartColumn) << "H";
    ss << line;

    return ss.str();
}