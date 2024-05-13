#pragma once
#include <iostream>

class HelpSystem {
	int pos;
public:
	HelpSystem(int);
	std::string drawMainPannel();
	std::string drawInstructionLogo();
	std::string drawInstruction();
	std::string drawSmallPannel(unsigned char);
};