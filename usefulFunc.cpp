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
	window.clear();
	window.draw(fieldSpr);
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
		if (twoPlayersTurn)gameField[a][b] = 'x';
		else gameField[a][b] = 'o';
		twoPlayersTurn = !twoPlayersTurn;
		return true;
	}
	return false;
}

bool diap200x200(Vector2f pos) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (pos.x >= i * 200 && pos.x < i * 200 + 200 &&
				pos.y >= j * 200 && pos.y < j * 200 + 200) {
				if (turner(j, i)) {
					toSendX = j;
					toSendY = i;
					return true;
				}
			}
		}
	}
	return false;
}

char inputFromKeybord() {
	char t = ' ';
	if (clickTimer > 150) {
		if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1)) {
			t = '1';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2)) {
			t = '2';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3)) {
			t = '3';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4)) {
			t = '4';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5)) {
			t = '5';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6)) {
			t = '6';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7)) {
			t = '7';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8)) {
			t = '8';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9)) {
			t = '9';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num0) || Keyboard::isKeyPressed(Keyboard::Numpad0)) {
			t = '0';
			clickTimer = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Period) || Keyboard::isKeyPressed(Keyboard::Delete)) {
			t = '.';
			clickTimer = 0;
		}
	}
	return t;
}