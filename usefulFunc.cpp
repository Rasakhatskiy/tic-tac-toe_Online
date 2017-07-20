#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "globals.h"
using namespace sf;


//checks if the game ands ant who win
char check() {
	for (int i = 0; i < 3; i++) {
		if (gameField[i][0] != ' ')
			if (gameField[i][0] == gameField[i][1] && gameField[i][0] == gameField[i][2]) {
				return gameField[i][1];
			}
		if (gameField[0][i] != ' ')
			if (gameField[0][i] == gameField[1][i] && gameField[0][i] == gameField[2][i]) {
				return gameField[1][i];
			}
	}
	if (gameField[0][0] != ' ')
		if (gameField[0][0] == gameField[1][1] && gameField[1][1] == gameField[2][2]) {
			return gameField[1][1];
		}
	if (gameField[0][2] != ' ')
		if (gameField[0][2] == gameField[1][1] && gameField[1][1] == gameField[2][0]) {
			return gameField[1][1];
		}
	//tie or not?
	bool all = true;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (gameField[i][j] == ' ')
				all = false;

	if (all) return 't';//tie
	return ' ';
}

//draws gameField at the window
void drawTable(RenderWindow &window) {
	float w, h;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 0) h = 0;
			if (i == 1) h = 200;
			if (i == 2) h = 400;
			if (j == 0) w = 0;
			if (j == 1) w = 200;
			if (j == 2) w = 400;

			if (gameField[i][j] == 'x')
				Ts = Xs;//x
			else
				if (gameField[i][j] == 'o')
					Ts = Os;//0
				else
					Ts = Zs;//empty sprite
			Vector2f v(w, h);
			Ts.setPosition(v);
			window.draw(Ts);
		}
	}
}

//erase gamefield and winner
void reset() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			gameField[i][j] = ' ';
	winner = ' ';
	gameOver = false;
	clickTimer = 0;
}

//check if move is possible(true), fill symbols, change turn
bool turner(int a, int b) {
	if (a < 0 || b < 0 || a > 2 || b > 2) {
		return false;
	}
	if (gameField[a][b] == ' ') {
		if (turn)gameField[a][b] = 'x';
		else gameField[a][b] = 'o';
		turn = !turn;
		return true;
	}
	return false;
}

bool diap200x200(Vector2f pos, int x, int y) {
	if (pos.x >= x * 200 && pos.x < x * 200 + 200 &&
		pos.y >= y * 200 && pos.y < y * 200 + 200) {
		if (turner(x, y)) {
			toSendX = x;
			toSendY = y;
			return true;
		}
	}
	else
		return false;
}