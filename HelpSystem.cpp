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

	ss << "\x1b[38;5;153m";
	ss << "\x1b[1;1H";
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
	int startColumn = (pos - 2 - instruction[0].size()) / 2 + 1;
	ss << "\x1b[1m";
	ss << "\x1b[38;5;119m";
	for (int i = 0; i < instruction.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << instruction[i];
	}

	ss << "\x1b[0;96m";
	std::string line(instruction[0].size() - 8, '.');
	ss << "\x1b[" << std::to_string(startRow + instruction.size() + 1) << ";" << std::to_string(startColumn + 4) << "H";
	ss << line;
	ss << "\x1b[0;0m";

	return ss.str();
}

std::string HelpSystem::drawInstruction() {
	std::vector<std::string> instructionHeader1{            
		" |_|  _        _|_  _   ._  |  _.    ",
		" | | (_) \\/\\/   |_ (_)  |_) | (_| \\/ ",
		"                        |         /  "
	};

	std::vector<std::string> instructionHeader2{         
		" |\\ |  _ _|_  _  ",
		" | \\| (_) |_ (/_ "
	};

	std::vector<std::string> instructionBody1{
		"- Using \x1b[38;5;219m\"W A S D\" \x1b[0;0mfor moving!",
		"- Trying to avoid the surrounding \x1b[38;5;219mwalls!\x1b[0;0m",
		"- After eating \x1b[38;5;219mapple\x1b[0;0m on the map, \x1b[0;36mscore\x1b[0;0m will be increased and \x1b[0;36mspeed\x1b[0;0m will, too!"
	};

	std::stringstream ss;
	std::string line2(20, '_');

	ss << "\x1b[38;5;168m";
	int startRow = 11;
	int startColumn = 3;
	for (int i = 0; i < instructionHeader1.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << instructionHeader1[i];
	}
	ss << "\x1b[0;96m";
	ss << "\x1b[" << std::to_string(startRow + instructionHeader1.size() - 1) << ";" << std::to_string(startColumn) << "H";
	ss << line2;
	ss << "\x1b[0;0m";
	
	int tempRow = startRow + instructionHeader1.size() + 1;
	for (int i = 0; i < instructionBody1.size(); i++) {
		ss << "\x1b[" << std::to_string(tempRow + i) << ";" << std::to_string(startColumn + 3) << "H";
		ss << instructionBody1[i];
	}

	startRow = 11 + instructionHeader1.size() + 5;
	ss << "\x1b[38;5;168m";
	for (int i = 0; i < instructionHeader2.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << instructionHeader2[i];
	}
	ss << "\x1b[0;96m";
	ss << "\x1b[" << std::to_string(startRow + instructionHeader1.size() - 1) << ";" << std::to_string(startColumn) << "H";
	ss << line2;
	ss << "\x1b[0;0m";

	//DRAW KEYBOARD
	std::vector<std::string> keyboard{
		"    \x1b[0;36m,---,	  ",
		"    | \x1b[38;5;219mW\x1b[0;36m |	  ",
		",---'---'---,",
		"| \x1b[38;5;219mA\x1b[0;36m | \x1b[38;5;219mS\x1b[0;36m | \x1b[38;5;219mD\x1b[0;36m |",
		"'---'---'---'\x1b[0;0m"
	};

	tempRow = startRow + instructionHeader2.size() + 2;
	for (int i = 0; i < keyboard.size(); i++) {
		ss << "\x1b[" << std::to_string(tempRow + i) << ";" << std::to_string(startColumn + 3) << "H";
		ss << keyboard[i];
	}
	ss << "\x1b[" << std::to_string(tempRow + keyboard.size()) << ";" << std::to_string(startColumn + 5) << "H";
	ss << "KEYBOARD";
	//DRAW KEYBOARD

	//DRAW WALL
	std::vector<std::string> walls{
		"\x1b[0;35m###########",
		"#         #",
		"#         #",
		"#         #",
		"###########\x1b[0;0m"
	};

	startColumn += 25;
	for (int i = 0; i < walls .size(); i++) {
		ss << "\x1b[" << std::to_string(tempRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << walls[i];
	}
	ss << "\x1b[" << std::to_string(tempRow + keyboard.size()) << ";" << std::to_string(startColumn + 3) << "H";
	ss << "WALLS";
	//DRAW WALL

	//DRAW SNAKE
	std::vector<std::string> snake{
		"           ",
		"    \x1b[0;36mooooo\x1b[0;33mo ",
		"   \x1b[0;36moo      ",
		" ooo       ",
		"           \x1b[0;0m",
	};
	startColumn += 20;
	for (int i = 0; i < snake.size(); i++) {
		ss << "\x1b[" << std::to_string(tempRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << snake[i];
	}
	ss << "\x1b[" << std::to_string(tempRow + keyboard.size()) << ";" << std::to_string(startColumn + 3) << "H";
	ss << "SNAKE";
	//DRAW SNAKE

	//DRAW SNAKE EAT APPLE
	std::vector<std::string> snakeWithApple{
		"           ",
		"    \x1b[0;36moooo\x1b[0;33mo  \x1b[0;31mo",
		"   \x1b[0;36moo      ",
		" ooo       ",
		"           \x1b[0;0m",
	};
	startColumn += 20;
	for (int i = 0; i < snakeWithApple.size(); i++) {
		ss << "\x1b[" << std::to_string(tempRow + i) << ";" << std::to_string(startColumn) << "H";
		ss << snakeWithApple[i];
	}
	ss << "\x1b[" << std::to_string(tempRow + keyboard.size()) << ";" << std::to_string(startColumn + 1) << "H";
	ss << "EAT APPLE";
	//DRAW SNAKE EAT APPLE

	ss << "\x1b[0;0m";
	ss << "\x1b[" << std::to_string(consoleSIZE.first) << ";" << std::to_string(consoleSIZE.second) << "H";

	return ss.str();
}

std::string HelpSystem::drawSmallPannel(unsigned char input) {
	std::stringstream ss;
	int sizeSmallPannel = consoleSIZE.second - pos;
	int startRow = 1;
	int startColumn = pos + 1;
	std::string line(sizeSmallPannel, '*');

	ss << "\x1b[38;5;214m";
	ss << "\x1b[0;" << std::to_string(startColumn) << "H";
	ss << line;

	for (int i = 2; i <= consoleSIZE.first - 1; i++) {
		ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(startColumn) << "H" << "*";
		ss << "\x1b[" << std::to_string(i) << ";" << std::to_string(consoleSIZE.second) << "H" << "*";
	}
	ss << "\x1b[" << std::to_string(consoleSIZE.first) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	std::vector<std::vector<std::string>> keyBoard{
		{
			" ____ ",
			"||W ||",
			"||__||",
			"|/__\\|"
		},
		{
			" ____ ",
			"||A ||",
			"||__||",
			"|/__\\|"
		},
		{
			" ____ ",
			"||S ||",
			"||__||",
			"|/__\\|"
		},
		{
			" ____ ",
			"||D ||",
			"||__||",
			"|/__\\|"
		}

	};
	std::vector<std::string> testWord{
		"  _____ ___ ___ _____ ",
		" |_   _| __/ __|_   _|",
		"   | | | _|\\__ \\ | |  ",
		"   |_| |___|___/ |_|  "
	};

	int startTestRow = startRow + 2;
	size_t startTestColumn = startColumn + 1 + (sizeSmallPannel - testWord[0].size() - 2) / 2;

	ss << "\x1b[38;5;195m";
	for (int i = 0; i < testWord.size(); i++) {
		ss << "\x1b[" << std::to_string(startTestRow + i) << ";" << std::to_string(startTestColumn) << "H";
		ss << testWord[i];
	}

	ss << "\x1b[38;5;50m";
	std::string lineTest(testWord[0].size(), '-');
	ss << "\x1b[" << std::to_string(startTestRow + testWord.size()) << ";" << std::to_string(startTestColumn) << "H";
	ss << lineTest;

	int keyBoardStartRow = startTestRow + testWord.size() + 1;
	int keyBoardStartColumn = startColumn + 1 + (sizeSmallPannel - 2 - (3 * keyBoard[0].size() - 2)) / 2;

	int choice = -1;
	if (input == 'w' || input == 'W') {
		choice = 0;
	} 
	else if (input == 'a' || input == 'A') {
		choice = 1;
	}
	else if (input == 's' || input == 'S') {
		choice = 2;
	}
	else if (input == 'd' || input == 'D') {
		choice = 3;
	}

	if (choice == 0) {
		ss << "\x1b[38;5;208m";
	}
	else {
		ss << "\x1b[0;0m";
	}

	for (int i = 0; i < keyBoard[0].size(); i++) {
		ss << "\x1b[" << std::to_string(keyBoardStartRow++) << ";" << std::to_string(keyBoardStartColumn + keyBoard[0].size() - 1) << "H";
		ss << keyBoard[0][i];
	}

	for (int i = 1; i < keyBoard.size(); i++) {
		if (choice == i) {
			ss << "\x1b[38;5;208m";
		}
		else {
			ss << "\x1b[0;0m";
		}
		for (int j = 0; j < keyBoard[i].size(); j++) {
			ss << "\x1b[" << std::to_string(keyBoardStartRow + j) << ";" << std::to_string(keyBoardStartColumn - 2 + (i - 1) * keyBoard[0].size() + (i - 1)) << "H";
			ss << keyBoard[i][j];
		}
	}

	startRow = keyBoardStartRow + keyBoard[0].size() + 1;
	startColumn = pos + 1;
	ss << "\x1b[38;5;214m";
	ss << "\x1b[" << std::to_string(startRow++) << ";" << std::to_string(startColumn) << "H";
	ss << line;

	std::vector<std::string> exitHelp{
		
		"  \x1b[38;5;195m ___                   ", 
		"  \x1b[38;5;195m| _ \\_ _ ___ ______    ", 
		"  \x1b[38;5;195m| _ / '_/ -_|_-<_-<    ",  
		"  \x1b[38;5;195m|_|_|_|_\\___/__/__/    ", 
		"     \x1b[38;5;197m| __/ __|/ __|      ", 
		"     \x1b[38;5;197m| _|\\__ \\ (__       ", 
		"     \x1b[38;5;197m|___|___/\\___|\x1b[38;5;195m_ _   ",
		"| |_ ___   _____ _(_) |_ ",
		"|  _/ _ \\ / -_) \\ / |  _|",
		" \\__\\___/ \\___/_\\_\\_|\\__|"
                          

	};

	/*startRow++;*/
	for (int i = 0; i < exitHelp.size(); i++) {
		ss << "\x1b[" << std::to_string(startRow + i) << ";" << std::to_string(startColumn + 3) << "H";
		ss << exitHelp[i];
	}

	ss << "\x1b[0;0m";


	return ss.str();
}