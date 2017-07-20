#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "globals.h"
using namespace sf;

void runServer(RenderWindow &window) {
	clickTimer = 0;
	TcpSocket socket;
	TcpListener listener;
	socket.setBlocking(false);
	listener.setBlocking(false);
	Packet p;
	bool turn = true;
	bool connected = false;
	bool done = false;

	RectangleShape shape(Vector2f(600, 600));
	shape.setFillColor(Color::White);
	listener.listen(PORT);
	Clock clock;
	while (window.isOpen()) {
		window.draw(shape);
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

		if (connected) {
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(pixelPos);//position of the mouse
			window.draw(fieldSpr);
			drawTable(window);
			//if server turn
			if (turn) {
				if (clickTimer > 200) {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						if (!gameOver) {
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 3; j++) {
									done = diap200x200(pos, i, j);
								}
							}
							winner = check();
						}
						clickTimer = 0;
					}
				}
				if (done) {
					p.clear();
					p << turn << toSendX << toSendY;
					socket.send(p);
					done = false;
				}
			}

			//if client turn
			if(!turn) {
				//todo
				int tx, ty;
				p.clear();
				socket.receive(p);
				p >> tx >> ty;
				turner(tx, ty);
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
		}
		if (!connected) {
			window.draw(waitScreenText);
			if (listener.accept(socket) == sf::Socket::Done){
				connected = true;
			}
		}




		

		window.display();
		window.clear();
	}
}
void runClient(RenderWindow &window) {
	clickTimer = 0;
	TcpSocket socket;
	socket.setBlocking(false);

	RectangleShape shape(Vector2f(600, 600));
	shape.setFillColor(Color::White);

	bool connected = false;
	std::string s;

	Clock clock;
	while (window.isOpen()) {
		window.draw(shape);
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

		if (connected) {

		}
		if (!connected) {
			window.draw(helpText);
			window.draw(help2Text);
			window.draw(input);
			char t = inputFromKeybord();
			if (t != ' ')
				s += t;
			input.setString(s);
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				if (s.size() > 0) {
					s.pop_back();
					clickTimer = 0;
				}
			}
		}


		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		window.display();
		window.clear();
	}
}

//client or server side
void choose(RenderWindow &window, char mode) {
	if (mode == 's')runServer(window);
	if (mode == 'c')runClient(window);
}