#include "HelpSystem.h"
#include "ConsoleSize.h"
#include <sstream>
#include <vector>

HelpSystem::HelpSystem(int _pos) {
	pos = _pos;
}

auto consoleSIZE = ConsoleSize::getConsoleSize();

std::string HelpSystem::drawMainPannel() {
	int maxColumn = pos;
	std::string line(maxColumn, '*');
	std::stringstream ss;

	ss << "\x1b[0;96m";
	ss << line;
	for (int i = 2; i <= consoleSIZE.first - 1; i++) {
		ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(0) << "H" << "*";
		ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(maxColumn) << "H" << "*";
	}
	ss << "\x1b[" << std::to_string(consoleSIZE.first) << ";" << std::to_string(0) << "H";
	ss << line;
	ss << "\x1b[0;0m";

	return ss.str();
}

std::string HelpSystem::drawInstructionLogo() {
	std::vector<std::string> instruction{
		"  _____ _   _  _____ _______ _____  _    _  _____ _______ _____ ____  _   _ ",
		" |_   _| \\ | |/ ____|__   __|  __ \\| |  | |/ ____|__   __|_   _/ __ \\| \\ | |",
		"   | | |  \\| | (___    | |  | |__) | |  | | |       | |    | || |  | |  \\| |",
		"   | | | . ` |\\___ \\   | |  |  _  /| |  | | |       | |    | || |  | | . ` |",
		"  _| |_| |\\  |____) |  | |  | | \\ \\| |__| | |____   | |   _| || |__| | |\\  |",
		" |_____|_| \\_|_____/   |_|  |_|  \\_\\\\____/ \\_____|  |_|  |_____\\____/|_| \\_|"
	};

	std::stringstream ss;
	int startRow = 2;
	int startColumn = (pos - 2 - instruction[0].size()) + 1;
	for (int i = 0; i < instruction.size(); i++) {
		if (i & 1) {
			ss << "\x1b[0;36m";
		}
		else {
			ss << "\x1b[0;33m";
		}
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << instruction[i];
	}

	std::string line(instruction[0].size() - 8, '-');
	ss << "\x1b[" << std::to_string(startRow + instruction.size() + 1) << ";" << std::to_string(startColumn + 4) << "H";
	ss << line;
	ss << "\x1b[0;0m";
	return ss.str();
}

std::string HelpSystem::drawInstruction() {
	std::vector<std::string> instruction{
		" _______                     __                     __             ", 
		"|   |   |.-----.--.--.--.   |  |_.-----.   .-----.|  |.---.-.--.--.",
		"|       ||  _  |  |  |  |   |   _|  _  |   |  _  ||  ||  _  |  |  |",
		"|___|___||_____|________|   |____|_____|   |   __||__||___._|___  |",
		"                                           |__|             |_____|"
	};

	std::stringstream ss;
	ss << "\x1b[0;91m";
	int startRow = 9;
	int startColumn = 3;
	for (int i = 0; i < instruction.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << instruction[i];
	}

	ss << "\x1b[0;0m";
	return ss.str();
}

std::string HelpSystem::drawSmallPannel() {
	
	return "hehe";
}