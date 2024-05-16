#pragma once
#include <iostream>
#include <vector>

class Option
{
	std::vector<std::string> logo;
	std::vector<std::pair<std::string, std::string>> color;
	int column;
public:
	Option(int, std::vector<std::string>, std::vector<std::pair<std::string, std::string>>);
	std::string drawMainPannel();
	std::string drawSmallPannel();
	std::string drawSettingLogo();
	std::string drawHeadColorHeader();
	std::string drawBodyColorHeader();
	std::string drawWallColorHeader();
	std::string drawSignature(); //for fun
	std::string drawBody(int);
	std::string chooseHeadColor(int);
	std::string chooseBodyColor(int);
	std::string chooseWallColor(int);
	std::string drawExampleWall(std::string);
	std::string drawExampleHeadSnake(std::string);
	std::string drawExampleBodySnake(std::string);

};

