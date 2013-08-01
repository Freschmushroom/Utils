#include "Go.h"
#include "GL/gl.h"
#include <iostream>

using std::cout;
using std::endl;

Field::Field(GameField* parent, int x, int y) {
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->state = 0;
	this->isMouseHovering = false;
}

Field** Field::getNeighbors() {
	Field** neighbors = new Field*[4];
	if (this->y > 0) {
		neighbors[0] = parent->getField(this->x, this->y - 1);
	} else {
		neighbors[0] = 0;
	}
	if (this->x > 0) {
		neighbors[1] = parent->getField(this->x - 1, this->y);
	} else {
		neighbors[1] = 0;
	}
	if (this->x < parent->getWidth() - 1) {
		neighbors[2] = parent->getField(this->x + 1, this->y);
	} else {
		neighbors[2] = 0;
	}
	if (this->y < parent->getWidth() - 1) {
		neighbors[3] = parent->getField(this->x, this->y + 1);
	} else {
		neighbors[3] = 0;
	}
	return neighbors;
}

unsigned char Field::getState() {
	return this->state;
}

bool Field::isEmpty() {
	return getState() == 0;
}

bool Field::belongsPlayer1() {
	return getState() == 1;
}

bool Field::belongsPlayer2() {
	return getState() == 2;
}

void Field::claimFor(int player) {
	this->state = (unsigned char) player;
}

void Field::render() {
	glPushMatrix();
	switch (this->state) {
	case 0:
		if (isMouseHovering) {
			glColor3ub(114, 168, 107);
		} else {
			glColor3ub(14, 68, 7);
		}
		glRectd(-parent->getFieldWidth() / 3.0, -parent->getFieldWidth() / 3.0,
				parent->getFieldWidth() / 3.0, parent->getFieldWidth() / 3.0);
		break;
	case 1:
		glColor3ub(0, 0, 0);
		glRectd(-parent->getFieldWidth() / 2.0, -parent->getFieldWidth() / 2.0,
				parent->getFieldWidth() / 2.0, parent->getFieldWidth() / 2.0);
		break;
	case 2:
		glColor3ub(255, 255, 255);
		glRectd(-parent->getFieldWidth() / 2.0, -parent->getFieldWidth() / 2.0,
				parent->getFieldWidth() / 2.0, parent->getFieldWidth() / 2.0);
		break;
	}
}

Field::~Field() {
	delete parent;
}
