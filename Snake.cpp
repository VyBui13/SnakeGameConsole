#include "Snake.h"

Snake::Snake() {
	nTail = 1;
	tailX.resize(1);
	tailY.resize(1);
	tailX[0] = 1;
	tailY[0] = 1;
}

Snake::Snake(int x, int y) {
	nTail = 1;
	tailX.resize(1);
	tailY.resize(1);
	tailX[0] = x;
	tailY[0] = y;
}

void Snake::setLocation(int x, int y) {
	tailX[0] = x;
	tailY[0] = y;
}