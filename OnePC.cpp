#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "globals.h"
using namespace sf;



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