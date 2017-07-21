#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "globals.h"
using namespace sf;

const bool setBlock = false;

void runServer(RenderWindow &window) {
	clickTimer = 0;
	TcpSocket socket;
	TcpListener listener;
	socket.setBlocking(false);
	listener.setBlocking(false);
	Packet p;
	bool turn = true;//true - server, false - client
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
		while (window.pollEvent(Event)){
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
			socket.setBlocking(setBlock);
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(pixelPos);//position of the mouse
			drawTable(window);
			//if server turn
			if (turn) {
				if (clickTimer > 200) {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						if (!gameOver) {
							done = diap200x200(pos);
							winner = check();
						}
						clickTimer = 0;
					}
				}
				if (done) {
					std::cout << "done\n";
					turn = false;
					p.clear();
					//
					p << toSendX << toSendY;
					if (socket.send(p) == Socket::Done) {
						done = false;
					}
				}
			}
			drawTable(window);
			//if client turn
			if(!turn) {
				//todo
				int tx, ty;
				p.clear();
				if (socket.receive(p) == Socket::Done) {
					p >> tx >> ty;
					turner(tx, ty);
					turn = true;
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
		}
		if (!connected) {
			window.draw(waitScreenText);
			if (listener.accept(socket) == sf::Socket::Done){
				std::cout << "connected\n";
				std::string temp = "start";
				p << temp;
				if (socket.send(p) == Socket::Done) {
					std::cout << "Ready for play!\n";
					connected = true;
				}
			}
		}

		window.display();
		window.clear();
	}
}
void runClient(RenderWindow &window) {
	clickTimer = 0;
	TcpSocket socket;
	socket.setBlocking(setBlock);
	IpAddress ip;
	RectangleShape shape(Vector2f(600, 600));
	shape.setFillColor(Color::White);
	bool turn = true;//true - server, false - client
	bool connected = false;
	bool done = false;
	Packet p;
	std::string s;

	Clock clock;
	while (window.isOpen()) {
		window.draw(shape);
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 900;
		clickTimer += time;


		sf::Event Event;
		while (window.pollEvent(Event)){
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
			socket.setBlocking(setBlock);
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(pixelPos);//position of the mouse
			drawTable(window);
			//if client turn
			if (!turn) {
				if (clickTimer > 200) {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						if (!gameOver) {
							done = diap200x200(pos);
							winner = check();
						}
						clickTimer = 0;
					}
				}
				if (done) {
					std::cout << "done\n";
					turn = true;
					p.clear();
					p << toSendX << toSendY;
					if (socket.send(p) == Socket::Done)
						done = false;//
				}
			}
			drawTable(window);
			//if server turn
			if (turn) {
				//todo
				int tx, ty;
				p.clear();
				if (socket.receive(p) == Socket::Done) {
					p >> tx >> ty;
					turner(tx, ty);
					turn = false;
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
		}
		if (!connected) {
			window.draw(helpText);
			window.draw(help2Text);
			window.draw(input);
			char t = inputFromKeybord();
			if (t != ' ')
				s += t;
			input.setString(s);
			if (clickTimer > 150) {
				if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
					if (s.size() > 0) {
						s.pop_back();
						clickTimer = 0;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					s = "127.0.0.1";
				}
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
					clickTimer = 0;
					ip = s;
					socket.connect(ip, PORT);
					std::cout << "connected!\n";
					while (!connected) {
						socket.receive(p);
						std::string temp;
						p >> temp;
						if (temp == "start") {
							connected = true;
							std::cout << "Ready to begin!";
						}
					}
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