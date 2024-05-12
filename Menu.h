#pragma once
#include "ConsoleSize.h"
#include <sstream>
#include <vector>

class Menu
{
	int minColumn;
	int maxColumn;
	int start;
	int sizeFeature;
	std::vector<std::string> logo;
	std::vector<std::vector<std::string>> feature;
public:
	Menu();
	Menu(std::vector<std::string>, std::vector<std::vector<std::string>>);
	std::string drawLogo();
	std::string drawPannel(int);
	std::string drawPannel2(int pos);
	std::string drawMenu(int);
	std::string drawFeature(std::vector<std::vector<std::string>>, int);
	std::string gameOver();
	std::string exitGame();
};

