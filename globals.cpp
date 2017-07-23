#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
#include "globals.h"
using namespace sf;

char gameField[3][3];
char winner;

int toSendX;
int toSendY;

bool twoPlayersTurn;//true == X, false == O
bool gameOver;

float clickTimer;//clickDelay

Texture fieldTex, ramaTex, Xtex, Otex, Ttex, Ztex;
Sprite fieldSpr, ramaSprite, Xs, Os, Ts, Zs;
Text menuText, startText,
modeForTwoText, modeVSPCText, modeOnlineText,
okText,
BlueWinText, RedWinText, TieText,
optionsText,
createSText, joinSText, waitScreenText,
helpText, help2Text, input, disconText, waitingText,
yourTurn, opponentTurn;

Font orange_juice;
IpAddress ipGlobal, ipLocal;

RectangleShape shape;

void set() {
	reset();
	winner = ' ';
	twoPlayersTurn = true;//true == X, false == O
	gameOver = false;
	clickTimer = 0;//clickDelay


	fieldSpr.setTexture(fieldTex);
	Xs.setTexture(Xtex);
	Os.setTexture(Otex);
	Ts.setTexture(Ttex);
	Zs.setTexture(Ztex);
	ramaSprite.setTexture(ramaTex);
	ramaSprite.setPosition(100, 190);

	//BDSM SFML c++
	//fuck you, Access violation!

	menuText.setFont(orange_juice);
	menuText.setCharacterSize(size);
	menuText.setColor(Color::Black);
	menuText.setPosition(170, 0);
	menuText.setString("Tic - Tac - Toe");

	startText.setFont(orange_juice);
	startText.setColor(Color::Blue);
	startText.setCharacterSize(size);
	startText.setString("Start Game");
	startText.setPosition(170, 100);

	optionsText.setFont(orange_juice);
	optionsText.setColor(Color::Blue);
	optionsText.setCharacterSize(size);
	optionsText.setString("Options");
	optionsText.setPosition(170, 200);

	modeForTwoText.setFont(orange_juice);
	modeForTwoText.setColor(Color::Blue);
	modeForTwoText.setCharacterSize(size);
	modeForTwoText.setString("Two for one PC");
	modeForTwoText.setPosition(170, 100);

	modeVSPCText.setFont(orange_juice);
	modeVSPCText.setColor(Color::Blue);
	modeVSPCText.setCharacterSize(size);
	modeVSPCText.setString("Player vs PC");
	modeVSPCText.setPosition(170, 200);

	modeOnlineText.setFont(orange_juice);
	modeOnlineText.setColor(Color::Blue);
	modeOnlineText.setCharacterSize(size);
	modeOnlineText.setString("Online Game");
	modeOnlineText.setPosition(170, 300);

	okText.setFont(orange_juice);
	okText.setColor(Color::Blue);
	okText.setCharacterSize(size);
	okText.setString("OK");
	okText.setPosition(250, 300);

	BlueWinText.setFont(orange_juice);
	BlueWinText.setColor(Color::Blue);
	BlueWinText.setCharacterSize(size);
	BlueWinText.setString("Blue Win!");
	BlueWinText.setPosition(200, 200);

	RedWinText.setFont(orange_juice);
	RedWinText.setCharacterSize(size);
	RedWinText.setColor(Color::Red);
	RedWinText.setString("Red Win!");
	RedWinText.setPosition(200, 200);

	TieText.setFont(orange_juice);
	TieText.setColor(Color::Black);
	TieText.setCharacterSize(size);
	TieText.setString("Tie!");
	TieText.setPosition(250, 200);

	createSText.setFont(orange_juice);
	createSText.setColor(Color::Blue);
	createSText.setCharacterSize(size);
	createSText.setString("Create Server");
	createSText.setPosition(170, 100);

	joinSText.setFont(orange_juice);
	joinSText.setColor(Color::Blue);
	joinSText.setCharacterSize(size);
	joinSText.setString("Join Server");
	joinSText.setPosition(170, 200);

	waitScreenText.setFont(orange_juice);
	waitScreenText.setColor(Color::Blue);
	waitScreenText.setCharacterSize(size);

	waitScreenText.setPosition(100, 200);
	ipGlobal = sf::IpAddress::getPublicAddress();
	ipLocal = sf::IpAddress::getLocalAddress();
	sf::String g, l;
	g = ipGlobal.toString();
	l = ipLocal.toString();
	waitScreenText.setString("Waiting For Conection...\nGlobal IP : " + g
		+ "\nLocal IP :" + l
		+ "\n\nPort : " + std::to_string(PORT));


	
	disconText.setFont(orange_juice);
	disconText.setColor(Color::Magenta);
	disconText.setCharacterSize(size);
	disconText.setString("You have been disconnected...");
	disconText.setPosition(100, 200);

	helpText.setFont(orange_juice);
	helpText.setColor(Color::Blue);
	helpText.setCharacterSize(size);
	helpText.setString("Press Escape to cancel");
	helpText.setPosition(100, 500);

	help2Text.setFont(orange_juice);
	help2Text.setColor(Color::Blue);
	help2Text.setCharacterSize(size);
	help2Text.setString("Enter target IP\nexample: 111.222.333.444\n\nThen press enter");
	help2Text.setPosition(100, 100);

	input.setFont(orange_juice);
	input.setColor(Color::Magenta);
	input.setCharacterSize(size);
	input.setString("");
	input.setPosition(100, 200);

	
	waitingText.setFont(orange_juice);
	waitingText.setColor(Color::Black);
	waitingText.setCharacterSize(size);
	waitingText.setString("Waiting for your opponent...");
	waitingText.setPosition(10, 640);

	yourTurn.setFont(orange_juice);
	yourTurn.setColor(Color::Black);
	yourTurn.setCharacterSize(size);
	yourTurn.setString("Your turn");
	yourTurn.setPosition(10, 600);

	opponentTurn.setFont(orange_juice);
	opponentTurn.setColor(Color::Black);
	opponentTurn.setCharacterSize(size);
	opponentTurn.setString("Opponent turn");
	opponentTurn.setPosition(10, 600);

	shape.setSize(Vector2f(600, 700));
	shape.setFillColor(Color::White);
}
//load textures, fonts, set sprites etc.
void loadFiles() {
	fieldTex.loadFromFile("Images/field.png");
	Xtex.loadFromFile("Images/X.png");
	Otex.loadFromFile("Images/O.png");
	ramaTex.loadFromFile("Images/rama.png");
	orange_juice.loadFromFile("font.ttf");
	set();
}