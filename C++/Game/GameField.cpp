#include "Go.h"
#include <GL/gl.h>
#include <iostream>

using std::cout;
using std::endl;

GameField::GameField(const int width) {
	this->width = width;
	this->fields = new Field*[width * width];
	for (int i = 0; i < width * width; i++) {
		this->fields[i] = new Field(this, i % width, i / width);
	}
}

int GameField::getWidth() {
	return this->width;
}

Field* GameField::getField(const int x, const int y) {
	return getField(x + y * width);
}

Field* GameField::getField(const int index) {
	return this->fields[index];
}

GameField::~GameField() {
	delete[] fields;
}

void GameField::render() {
	glPushMatrix();
	glColor3ub(14, 68, 7);
	glBegin(GL_LINES);
	for (int i = 0; i < width; i++) {
		int x = 500 + (int) (920 / (float) (width - 1) * i);
		glVertex2f(x, 200);
		glVertex2f(x, 1080 - 200);
	}
	for (int i = 0; i < width; i++) {
		int y = 200 + (int) (680 / (float) (width - 1) * i);
		glVertex2f(500, y);
		glVertex2f(1920 - 500, y);
	}
	glEnd();
	glPushMatrix();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			int x = 500 + (int) (920 / (float) (width - 1) * i);
			int y = 200 + (int) (680 / (float) (width - 1) * j);
			glTranslatef(x, y, 0);
			fields[i + j * width]->render();
			glLoadIdentity();
		}
	}
	glPopMatrix();
	glPopMatrix();
}

int GameField::getFieldWidth() {
	return (int) (width / 10.0) * 30;
}
