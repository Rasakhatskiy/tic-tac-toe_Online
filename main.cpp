//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //hide console
#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "drawing.h"

using namespace sf;
char arr[3][3] = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
char winner = ' ';
bool turn = true;
bool gameOver = false;
float clickTimer = 0;


char check();
void reset();
void drawTable(RenderWindow &window);
void twoPlayers(RenderWindow &window);
void onlineGame(RenderWindow &window, char mode);
void menu(RenderWindow &window);
void turner(int a, int b);

char check() {
	for (int i = 0; i < 3; i++) {
		if (arr[i][0] != ' ')
			if (arr[i][0] == arr[i][1] && arr[i][0] == arr[i][2]) {
				//std::cout << std::endl << arr[i][1] << " Wins!\n";
				return arr[i][1];
				
			}
		if (arr[0][i] != ' ')
			if (arr[0][i] == arr[1][i] && arr[0][i] == arr[2][i]) {
				//std::cout << std::endl << arr[1][i] << " Wins!\n";
				return arr[1][i];
			}
	}
	if (arr[0][0] != ' ')
		if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) {
			//std::cout << std::endl << arr[1][1] << " Wins!\n";
			return arr[1][1];
		}
	if (arr[0][2] != ' ')
		if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) {
			//std::cout << std::endl << arr[1][1] << " Wins!\n";
			return arr[1][1];
		}
	bool all = true;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (arr[i][j] == ' ')
				all = false;

	if (all) return 't';
	return ' ';
}
	
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

			if (arr[i][j] == 'x')
				Ts = Xs;//x
			else 
				if (arr[i][j] == 'o')
					Ts = Os;//0
					else 
						Ts = Zs;//empty sprite
			Vector2f v(w, h);
			Ts.setPosition(v);
			window.draw(Ts);
		}
	}
}

void reset() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			arr[i][j] = ' ';
	winner = ' ';
	gameOver = false;
	clickTimer = 0;
}

void turner(int a, int b) {
	if (arr[a][b] == ' ') {
		if (turn)arr[a][b] = 'x';
		else arr[a][b] = 'o';
		turn = !turn;
	}
}

void twoPlayers(RenderWindow &window) {
	Clock clock;
	char turnc;
	clickTimer = 0;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 900;
		
		clickTimer += time;


		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::R))
				reset();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				reset();
				menu(window);
			}
				
		}

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		window.draw(fieldSpr);
		drawTable(window);

		if (clickTimer > 200) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (!gameOver) {
					if (turn) turnc = 'x';
					else turnc = 'o';

					if (pos.x >= 0 && pos.x < 200 && pos.y >= 0 && pos.y < 200)
						turner(0, 0);
					if (pos.x >= 200 && pos.x < 400 && pos.y >= 0 && pos.y < 200)
						turner(0, 1);
					if (pos.x >= 400 && pos.x < 600 && pos.y >= 0 && pos.y < 200)
						turner(0, 2);

					if (pos.x >= 0 && pos.x < 200 && pos.y >= 200 && pos.y < 400)
						turner(1, 0);
					if (pos.x >= 200 && pos.x < 400 && pos.y >= 200 && pos.y < 400)
						turner(1, 1);
					if (pos.x >= 400 && pos.x < 600 && pos.y >= 200 && pos.y < 400)
						turner(1, 2);

					if (pos.x >= 0 && pos.x < 200 && pos.y >= 400 && pos.y < 600)
						turner(2, 0);
					if (pos.x >= 200 && pos.x < 400 && pos.y >= 400 && pos.y < 600)
						turner(2, 1);
					if (pos.x >= 400 && pos.x < 600 && pos.y >= 400 && pos.y < 600)
						turner(2, 2);


					for (int i = 0; i < 3; i++) {
						//std::cout << std::endl;
						for (int j = 0; j < 3; j++) {
							//std::cout << arr[i][j] << " ";
						}
					}
					winner = check();

					clickTimer = 0;
				}
			}
		}
		if (winner == 'x') {
			window.draw(ramaSprite);
			window.draw(RedWinText);
			gameOver = true;
		}
		if (winner == 'o') {
			window.draw(ramaSprite);
			window.draw(BlueWinText);
			gameOver = true;
		}
		if (winner == 't') {
			window.draw(ramaSprite);
			window.draw(TieText);
			gameOver = true;
		}
		if (gameOver) {
			if (pos.x >= 250 && pos.x < 315 && pos.y >= 300 && pos.y < 350) {
				okText.setColor(Color(255, 144, 0));
				window.draw(okText);
				if (Mouse::isButtonPressed(Mouse::Left))
					reset();
			}
			else {
				okText.setColor(Color::Blue);
				window.draw(okText);
			}
		}
		window.display();
	}
}

void onlineGame(RenderWindow &window, char mode) {

}

void menu(RenderWindow &window) {
	Clock clock;
	clickTimer = 0;
	int menulvl = 1;
	RectangleShape whiteS;
	whiteS.setSize(Vector2f(600, 600));
	whiteS.setFillColor(Color::White);
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 900;
		clickTimer += time;

		window.draw(menuText);

		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::R))
				reset();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				menulvl = 1;
		}

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		if (menulvl == 1) {
			if (pos.x >= 170 && pos.x < 400 && pos.y >= 100 && pos.y < 150) {
				startText.setColor(Color(255, 144, 0));
				window.draw(startText);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					if (clickTimer > 200) {
						menulvl = 2;
						clickTimer = 0;
					}
				}
			}
			else {
				startText.setColor(Color::Blue);
				window.draw(startText);
			}


			if (pos.x >= 170 && pos.x < 350 && pos.y >= 200 && pos.y < 250) {
				optionsText.setColor(Color(255, 144, 0));
				window.draw(optionsText);
			}
			else {
				optionsText.setColor(Color::Blue);
				window.draw(optionsText);
			}

		}
		if (menulvl == 2) {
			if (pos.x >= 170 && pos.x < 400 && pos.y >= 100 && pos.y < 150) {
				modeForTwoText.setColor(Color(255, 144, 0));
				window.draw(modeForTwoText);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					if (clickTimer > 200) {
						clickTimer = 0;
						twoPlayers(window);
					}
				}
			}
			else {
				modeForTwoText.setColor(Color::Blue);
				window.draw(modeForTwoText);
			}

			if (pos.x >= 170 && pos.x < 350 && pos.y >= 200 && pos.y < 250) {
				modeVSPCText.setColor(Color(255, 144, 0));
				window.draw(modeVSPCText);
			}
			else {
				modeVSPCText.setColor(Color::Blue);
				window.draw(modeVSPCText);
			}

			if (pos.x >= 170 && pos.x < 350 && pos.y >= 300 && pos.y < 350) {
				modeOnlineText.setColor(Color(255, 144, 0));
				window.draw(modeOnlineText);
				if (Mouse::isButtonPressed(Mouse::Left)){
					if (clickTimer > 200) {
						clickTimer = 0;
						menulvl = 3;
					}
				}
			}
			else {
				modeOnlineText.setColor(Color::Blue);
				window.draw(modeOnlineText);
			}
		}
		if (menulvl == 3) {
			if (pos.x >= 170 && pos.x < 450 && pos.y >= 100 && pos.y < 150) {
				createSText.setColor(Color(255, 144, 0));
				window.draw(createSText);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					clickTimer = 0;
					onlineGame(window, 's');
				}
			}
			else {
				createSText.setColor(Color::Blue);
				window.draw(createSText);
			}


			if (pos.x >= 170 && pos.x < 375 && pos.y >= 200 && pos.y < 250) {
				joinSText.setColor(Color(255, 144, 0));
				window.draw(joinSText);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					clickTimer = 0;
					onlineGame(window, 'c');
				}
			}
			else {
				joinSText.setColor(Color::Blue);
				window.draw(joinSText);
			}

		}

		if (clickTimer > 200) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				clickTimer = 0;
			}
		}


		window.display();
		window.clear();
		window.draw(whiteS);
	}
}

int main()
{
	loadFiles();
	sf::RenderWindow window(sf::VideoMode(600, 600, 32), "Tic-Tac toe");
	menu(window);

	return 0;
}
