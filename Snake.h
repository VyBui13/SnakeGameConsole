#pragma once
#include <vector>

class Snake
{
public:
	int nTail;
	std::vector<int> tailX;
	std::vector<int> tailY;

	Snake();
	Snake(int, int);
	void setLocation(int, int);
};


