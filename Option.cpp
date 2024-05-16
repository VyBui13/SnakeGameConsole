#include "Option.h"
#include "ConsoleSize.h"
#include <sstream>

Option::Option(int _column, std::vector<std::string> _logo, std::vector<std::pair<std::string, std::string>> _color) {
	column = _column;
	logo = _logo;
	color = _color;
}

std::string Option::drawMainPannel() {
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	std::stringstream ss;
	int startRow = 1;
	int startColumn = 1;
	std::string line(column, '*');

	ss << "\x1b[38;5;86m";
	ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	for (int i = 1; i < consoleSIZE.first; i++) {
		ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
		ss << "*";
		ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(column) << "H";
		ss << "*";
	}
	ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	ss << "\x1b[0;0m";
	return ss.str();
}

std::string Option::drawSmallPannel() {
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;
	int widthCell = consoleSIZE.second - column;
	int startRow = 1;
	int startColumn = column + 1;

	std::string line(widthCell, '*');
	std::stringstream ss;
	ss << "\x1b[38;5;121m";
	ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	for (int i = 1; i < consoleSIZE.first; i++) {
		ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
		ss << "*";
		ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(consoleSIZE.second) << "H";
		ss << "*";
	}
	ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	startRow = 1 + spaceHeightEachCell + 1;
	ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	startRow += 1 + spaceHeightEachCell;
	ss << "\x1b[" << std::to_string(startRow ) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	startRow += 1 + spaceHeightEachCell;
	ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
	ss << line;
	return ss.str();
}

std::string Option::drawSettingLogo() {
	int startRow = 3;
	int startColumn = 2 + (column - 2 - logo[0].size()) / 2;
	std::stringstream ss;
	
	for (int i = 0; i < logo.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(startColumn) << "H";
		ss << logo[i];
	}

	return ss.str();
}

std::string Option::chooseHeadColor(int pos) {
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2 - 4;
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;
	
	std::stringstream ss;
	int startColumn = column + 9;
	int startRow = 2;
	for (int i = 0; i < color.size(); i++) {
		if (i == pos) {
			ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn - 2) << "H";
			ss << "\x1b[38;5;220m>\x1b[0;0m";
			ss << "\x1b[" << color[i].first;
		}
		else {
			ss << "\x1b[38;5;246m";
			ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn - 2) << "H" << " ";

		}
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << color[i].second;
	}
	ss << "\x1b[0;0m";
	return ss.str();
}

std::string Option::chooseBodyColor(int pos) {
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2 - 4;
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;

	std::stringstream ss;
	int startColumn = column + 9;
	int startRow = 2 + spaceHeightEachCell + 1;

	for (int i = 0; i < color.size(); i++) {
		if (i == pos) {
			ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn - 2) << "H";
			ss << "\x1b[38;5;220m>\x1b[0;0m";
			ss << "\x1b[" << color[i].first;
		}
		else {
			ss << "\x1b[38;5;246m";
			ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn - 2) << "H" << " ";

		}
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << color[i].second;
	}
	ss << "\x1b[0;0m";
	return ss.str();
}

std::string Option::chooseWallColor(int pos) {
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2 - 4;
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;

	std::stringstream ss;
	int startColumn = column + 9;
	int startRow = 2 + 2 * spaceHeightEachCell + 2;

	for (int i = 0; i < color.size(); i++) {
		if (i == pos) {
			ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn - 2) << "H";
			ss << "\x1b[38;5;220m>\x1b[0;0m";
			ss << "\x1b[" << color[i].first;
		}
		else {
			ss << "\x1b[38;5;246m";
			ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn - 2) << "H" << " ";

		}
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << color[i].second;
	}
	ss << "\x1b[0;0m";
	return ss.str();
}


std::string drawPartBody(bool check,int startRow, int startColumn, std::vector<std::pair<std::string, std::string>> color) {
	std::stringstream ss;
	if (check) {
		ss << "\x1b[38;5;14m";

	}
	else {
		ss << "\x1b[38;5;246m";
	}

	for (int i = 0; i < color.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << color[i].second;
	}
	ss << "\x1b[0;0m";
	return ss.str();
}

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

std::string Option::drawBody(int choice) {
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2 - 4;
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;
	std::stringstream ss;

	int startColumn = column + 9;
	
	int startHeadRow = 2;
	int startBodyRow = 2 + spaceHeightEachCell + 1;
	int startWallRow = 2 + 2 * spaceHeightEachCell + 2;

	if (choice == 1) {
		//HEADER
		ss << drawPartBody(true, startHeadRow, startColumn, color);
		ss << drawPartBody(false, startBodyRow, startColumn, color);
		ss << drawPartBody(false, startWallRow, startColumn, color);
	}
	else if(choice == 2) {
		ss << drawPartBody(false, startHeadRow, startColumn, color);
		ss << drawPartBody(true, startBodyRow, startColumn, color);
		ss << drawPartBody(false, startWallRow, startColumn, color);
	}
	else {
		ss << drawPartBody(false, startHeadRow, startColumn, color);
		ss << drawPartBody(false, startBodyRow, startColumn, color);
		ss << drawPartBody(true, startWallRow, startColumn, color);
	}
	return ss.str();
	
}

std::string Option::drawHeadColorHeader() {
	std::string header = "HEAD";
	std::stringstream ss;
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2;
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;
	int startRow = 2 + (spaceHeightEachCell - header.size())/ 2;
	int startColumn = column + 3;
	ss << "\x1b[0;93m";
	for (int i = 0; i < header.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << header[i];
	}
	ss << "\x1b[0;0m";

	startColumn += 2;
	startRow = 2;
	ss << "\x1b[38;5;121m";

	for (int i = 0; i < spaceHeightEachCell; i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << "*";
	}
	return ss.str();
}

std::string Option::drawBodyColorHeader() {
	std::string body = "BODY";
	std::stringstream ss;
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2;
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;
	int startRow = 2 + spaceHeightEachCell + 1 + (spaceHeightEachCell - body.size()) / 2;
	int startColumn = column + 3;
	ss << "\x1b[0;93m";
	for (int i = 0; i < body.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << body[i];
	}
	ss << "\x1b[0;0m";

	startColumn += 2;
	startRow = 2 + spaceHeightEachCell + 1;
	ss << "\x1b[38;5;121m";

	for (int i = 0; i < spaceHeightEachCell; i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << "*";
	}
	return ss.str();
}

std::string Option::drawWallColorHeader() {
	std::string wall = "WALL";
	std::stringstream ss;
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2;
	int spaceHeightEachCell = (consoleSIZE.first - 4) / 3;
	int startRow = 2 + 2 * spaceHeightEachCell + 2 + (spaceHeightEachCell - wall.size()) / 2;
	int startColumn = column + 3;
	ss << "\x1b[0;93m";
	for (int i = 0; i < wall.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << wall[i];
	}
	ss << "\x1b[0;0m";

	startColumn += 2;
	startRow = 2 + 2 * spaceHeightEachCell + 2;
	ss << "\x1b[38;5;121m";

	for (int i = 0; i < spaceHeightEachCell; i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << "*";
	}
	return ss.str();
}

std::string Option::drawSignature() {
	auto consoleSIZE = ConsoleSize::getConsoleSize();
	int widthCell = consoleSIZE.second - column - 2;
	std::string signature = "VB_NO_HOPE";
	
	int startRow = consoleSIZE.first - 1;
	int startColumn = column + 2 + (widthCell - 2 - signature.size()) / 2;

	std::stringstream ss;
	ss << "\x1b[0;93m";
	ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
	ss << signature;
	ss << "\x1b[0;0m";

	return ss.str();
} //for fun

std::string Option::drawExampleWall(std::string wallColor) {
	std::stringstream ss;
	auto consoleSize = ConsoleSize::getConsoleSize();

	int widthWall = column - 16;
	int heightWall = consoleSize.first - 2 - logo.size() - 6;
	int startRow = 2 + logo.size() + 3;
	int startColumn = 2 + (column - 2 - widthWall) /2;

	std::string wall(widthWall, '#');
	
	ss << "\x1b[" << wallColor;
	ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(startColumn) << "H";
	ss << wall;
	for (int i = 1; i < heightWall - 2; i++) {
		ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H" << "#";
		ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(startColumn + widthWall - 1) << "H" << "#";
	}
	ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn) << "H";
	ss << wall;
	ss << "\x1b[0;0m";
	return ss.str();
}

std::string Option::drawExampleHeadSnake(std::string headColor) {
	std::stringstream ss;
	auto consoleSize = ConsoleSize::getConsoleSize();
	int widthWall = column - 16;
	int heightWall = consoleSize.first - 2 - logo.size() - 6;
	int startRow = 2 + logo.size() + 3 + heightWall / 2;
	int startColumn = 2 + (column - 2 - widthWall) / 2 + widthWall / 2 - 5;
	 //DRAW HEAD
	ss << "\x1b[" << headColor;
	ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn++) << "H";
	ss << "o";
	ss << "\x1b[0;0m";
	return ss.str();
}

std::string Option::drawExampleBodySnake(std::string bodyColor) {
	std::stringstream ss;
	auto consoleSize = ConsoleSize::getConsoleSize();
	int widthWall = column - 16;
	int heightWall = consoleSize.first - 2 - logo.size() - 6;
	int startRow = 2 + logo.size() + 3 + heightWall / 2;
	int startColumn = 2 + (column - 2 - widthWall) / 2 + widthWall / 2 - 4;
	//DRAW BODY
	ss << "\x1b[" << bodyColor;
	for (int i = 0; i < 9; i++) {
		ss << "\x1b[" << std::to_string(startRow) << ";" << std::to_string(startColumn++) << "H";
		ss << "o";
	}
	ss << "\x1b[0;0m";
	return ss.str();
}




