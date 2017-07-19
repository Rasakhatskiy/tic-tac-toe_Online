# include <SFML/Graphics.hpp>
using namespace sf;

const int size = 48;

Texture fieldTex, ramaTex, Xtex, Otex, Ttex, Ztex;
Sprite fieldSpr, ramaSprite, Xs, Os, Ts, Zs;
Text menuText, startText, 
modeForTwoText, modeVSPCText, modeOnlineText, 
okText, 
BlueWinText, RedWinText, TieText,
optionsText,
createSText, joinSText;

Font orange_juice;
void loadFiles() {
	fieldTex.loadFromFile("Images/field.png");
	Xtex.loadFromFile("Images/X.png");
	Otex.loadFromFile("Images/O.png");
	ramaTex.loadFromFile("Images/rama.png");


	fieldSpr.setTexture(fieldTex);
	Xs.setTexture(Xtex);
	Os.setTexture(Otex);
	Ts.setTexture(Ttex);
	Zs.setTexture(Ztex);
	ramaSprite.setTexture(ramaTex);
	ramaSprite.setPosition(100, 190);

	
	orange_juice.loadFromFile("font.ttf");
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
	
}