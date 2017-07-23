//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //hide console
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "globals.h"
using namespace sf;



//main menu of the game
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
					choose(window, 's');
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
					choose(window, 'c');
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
	reset();
	winner = ' ';
	twoPlayersTurn = true;//true == X, false == O
	gameOver = false;
	clickTimer = 0;//clickDelay
	menu(window);
	
	return 0;
}
