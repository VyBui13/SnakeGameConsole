#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "Snake.h"
#include "Fruit.h"

class Game {
    int xStart;
    int yStart;
    std::pair<int, int> size;
    Snake theChosenSnake;
    Fruit apple;
public:
    int timePush;
    bool gameOver;

    Game();
    Game(std::pair<int, int>);
    int getSizeSnake();
    std::string drawPanel();
    std::string drawSnake();
    std::string drawCurrentSnake();
    std::string drawFruit();
    std::string drawPannelScore();
    void control(unsigned char);
    void resetGame();
    std::string drawScore();
    std::string drawStatus(bool);
    std::string drawBestScore(int);
};