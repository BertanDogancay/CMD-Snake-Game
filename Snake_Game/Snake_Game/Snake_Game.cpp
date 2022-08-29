#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

//Initialize Variables
bool snakeGame;
const int width = 25;
const int height = 25;
int game_speed = 30;
//User variables
int x, y, spd = 1;
int tailX[100], tailY[100], tailLength;
//Tail coordiantes
int fposX, fposY, sposX, sposY;
//Target variables
int targetX, targetY;
//Game variables
int score;
enum directions { STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;

void game_setup() {
	snakeGame = true;
	dir = STOP;
	x = rand() % width;
	y = rand() % height;
	targetX = rand() % width;
	targetY = rand() % height;

	//ERROR when target and player overlap
	while (x == targetX && y == targetY) {
		x = rand() % width;
		y = rand() % height;
		targetX = rand() % width;
		targetY = rand() % height;
	}
	score = 0;
	tailLength = 0;
}

void pre_game_setup() {
	int wall1 = 25, wall2 = 25;
	for (int i = 0; i < wall1; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < wall2; i++) {
		for (int j = 0; j < wall1; j++) {
			if (j == 0 || j == wall1 - 1) {
				cout << "|";
			}
			else if (i == 10 && j == 4) {
				cout << "PRESS S TO START";
				j += 15;
			}
			else if (i == 12 && j == 4) {
				cout << "PRESS Q TO QUIT";
				j += 14;
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
    for (int j = 0; j < wall1; j++) {
		cout << "-";
	}
	cout << endl;
	_kbhit();
	if (_getch() == 's')
		game_setup();
	else if (_getch() == 'q')
		snakeGame = false;
	else  {
		pre_game_setup();
	}
}

void game_window() {
	system("cls");
	//Top border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;
	//Body
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width -1) {
				cout << "*";
			}
			else if (i == y && j == x) {
				cout << "S";
			}
			else if (i == targetY && j == targetX) {
				cout << "O";
			}
			else {
				bool tail = false;
				for (int k = 0; k < tailLength; k++) {
					if (j == tailX[k] && i == tailY[k]) {
						cout << "s";
						tail = true;
					}
				}
				if (!tail) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	//Bottom border
	for (int i = 0; i < width; i++) {
		cout << "*";
	}
	cout << endl;
	cout << score;
}

void game_input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (dir != RIGHT) {
				dir = LEFT;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case '0':
			snakeGame = false;
			break;
		}
	}
}

void game_program() {

	//Tail
	fposX = tailX[0];
	fposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++) {
		sposX = tailX[i];
		sposY = tailY[i];
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
	}

	switch (dir) {
	case LEFT:
		x -= spd;
		break;
	case UP:
		y -= spd;
		break;
	case DOWN:
		y += spd;
		break;
	case RIGHT:
		x += spd;
		break;
	}
	//Snake border hit
	if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1) {
		snakeGame = false;
	}

	//Snake tail hit
	for (int i = 0; i < tailLength; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			snakeGame = false;
		}
	}

	//Snake hits target
	if (x == targetX && y == targetY) {
		targetX = rand() % width;
		targetY = rand() % height;
		score++;
		tailLength++;
	}
}

int main() {
	pre_game_setup();
	while (snakeGame == true) {
		game_window();
		game_input();
		game_program();
		Sleep(game_speed);
		while (snakeGame == false) {
			pre_game_setup();
			break;
		}		
	}
}