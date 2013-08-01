#ifndef GO_H_
#define GO_H_

#include "Events.h"

void update();
void render();

class GameField;
class Field;

extern GameField gameField;

class KeyboardListener: public KeyListener {
public:
	void keyPressed(unsigned char, int, int);
	void keyReleased(unsigned char, int, int);
	void specialKeyPressed(unsigned char, int, int);
	void specialKeyReleased(unsigned char, int, int);
};

class GameField {
	Field** fields;
	int width;
public:
	GameField(const int width);
	int getWidth();
	Field* getField(const int x, const int y);
	Field* getField(const int index);
	void render();
	int getFieldWidth();
	~GameField();
};

class Field {
	GameField* parent;
	unsigned char state;
	int x, y;
public:
	bool isMouseHovering;

	Field(GameField* parent, int x, int y);
	Field** getNeighbors();
	unsigned char getState();
	bool isEmpty();
	bool belongsPlayer1();
	bool belongsPlayer2();
	void claimFor(int player);
	void render();
	~Field();
};

#endif
