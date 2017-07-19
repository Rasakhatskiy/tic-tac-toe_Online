#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
using namespace sf;

const int size = 48;
const unsigned short PORT = 5001;

extern char gameField[3][3];
extern char winner;

extern bool turn;//true == X, false == O
extern bool gameOver;

extern float clickTimer;//clickDelay

extern Texture fieldTex, ramaTex, Xtex, Otex, Ttex, Ztex;
extern Sprite fieldSpr, ramaSprite, Xs, Os, Ts, Zs;
extern Text menuText, startText,
modeForTwoText, modeVSPCText, modeOnlineText,
okText,
BlueWinText, RedWinText, TieText,
optionsText,
createSText, joinSText, waitScreenText,
helpText, help2Text, input;

extern Font orange_juice;
extern IpAddress ipGlobal, ipLocal;

char check();
void reset();
void loadFiles();
void drawTable(RenderWindow &window);
void menu(RenderWindow &window);
bool turner(int a, int b);
void twoPlayers(RenderWindow &window);

void loadFiles();