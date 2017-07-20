#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
using namespace sf;

const int size = 48;//font size
const unsigned short PORT = 5001;

extern char gameField[3][3];
extern char winner;//x , o or Tie (t)

extern int toSendX;
extern int toSendY;

extern bool turn;//true == X, false == O
extern bool gameOver;//true if game ends

extern float clickTimer;//clickDelay, without it mouse and keyboard clicks too many times

extern Texture fieldTex, ramaTex, Xtex, Otex, Ttex, Ztex;//Game textures
extern Sprite fieldSpr, ramaSprite, Xs, Os, Ts, Zs;//game Sprites
//Text that we can see in game
extern Text menuText, startText,
modeForTwoText, modeVSPCText, modeOnlineText,
okText,
BlueWinText, RedWinText, TieText,
optionsText,
createSText, joinSText, waitScreenText,
helpText, help2Text, input;
//Top font
extern Font orange_juice;
extern IpAddress ipGlobal, ipLocal;

char check();
void reset();
void loadFiles();
void choose(RenderWindow &window, char mode);
void drawTable(RenderWindow &window);
void menu(RenderWindow &window);
bool turner(int a, int b);
void twoPlayers(RenderWindow &window);
bool diap200x200(Vector2f mouse, int x, int y);