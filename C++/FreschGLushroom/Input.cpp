#include "GL/glut.h"
#include "InternalGL.h"
#include "Events.h"
#include "FreschGLushroom.h"
#include <list>

using std::list;

bool isGrabbed = false;

bool keys[255];
bool specialKeys[255];
bool mouseButtons[255];

int mouseX = -1;
int mouseY = -1;

list<KeyListener*> keyListeners;
list<MouseListener*> mouseListeners;

int getMouseX() {
	return mouseX;
}

int getMouseY() {
	return mouseY;
}

void keyboard(unsigned char key, bool state, int x, int y) {
	for (list<KeyListener*>::iterator it = keyListeners.begin();
			it != keyListeners.end(); it++) {
		if (state) {
			((KeyListener*) *it)->keyPressed(key, x, y);
		} else {
			((KeyListener*) *it)->keyReleased(key, x, y);
		}
	}
	keys[key] = state;
}

void keyboardDown(unsigned char key, int x, int y) {
	keyboard(key, true, x, y);
}

void keyboardUp(unsigned char key, int x, int y) {
	keyboard(key, false, x, y);
}

void specialKeyboard(int key, bool state, int x, int y) {
	for (list<KeyListener*>::iterator it = keyListeners.begin();
			it != keyListeners.end(); it++) {
		if (state) {
			((KeyListener*) *it)->specialKeyPressed((unsigned char) key, x, y);
		} else {
			((KeyListener*) *it)->specialKeyReleased((unsigned char) key, x, y);
		}
	}
	specialKeys[key] = state;
}

void specialKeyboardDown(int key, int x, int y) {
	specialKeyboard(key, true, x, y);
}

void specialKeyboardUp(int key, int x, int y) {
	specialKeyboard(key, false, x, y);
}

void mouse(int button, int state, int x, int y) {
	for (list<MouseListener*>::iterator it = mouseListeners.begin();
			it != mouseListeners.end(); it++) {
		if (state) {
			((MouseListener*) *it)->mouseReleased(button, x, y);
		} else {
			((MouseListener*) *it)->mousePressed(button, x, y);
		}
	}
	mouseButtons[button] = state;
}

void mouseMotion(int x, int y) {
	int oldX = mouseX, oldY = mouseY;
	mouseX = x, mouseY = y;
	for (list<MouseListener*>::iterator it = mouseListeners.begin();
			it != mouseListeners.end(); it++) {
		((MouseListener*) *it)->mouseMoved(oldX, oldY, mouseX, mouseY);
	}
}

void grabCursor() {
	isGrabbed = true;
	mouseX = getWidth() / 2;
	mouseY = getHeight() / 2;
	glutWarpPointer(mouseX, mouseY);
	int windowX = glutGet(GLUT_WINDOW_X);
	int windowY = glutGet(GLUT_WINDOW_Y);
	RECT rect;
	rect.left = windowX;
	rect.right = windowX + getWidth();
	rect.top = windowY;
	rect.bottom = windowY + getHeight();
	ClipCursor(&rect);
	glutSetCursor(GLUT_CURSOR_NONE);
}

void ungrabCursor() {
	isGrabbed = false;
	ClipCursor(NULL);
	glutSetCursor(GLUT_CURSOR_INHERIT);
	glutWarpPointer(getWidth() / 2, getHeight() / 2);
}

void setCursorGrabbed(bool cursorGrabbed) {
	if (cursorGrabbed != isCursorGrabbed()) {
		if (cursorGrabbed) {
			grabCursor();
		} else {
			ungrabCursor();
		}
	}
}

bool isCursorGrabbed() {
	return isGrabbed;
}

bool isKeyDown(unsigned char key) {
	return keys[key];
}

bool isSpecialKeyDown(unsigned char specialKey) {
	return specialKeys[specialKey];
}

bool isMouseButtonDown(unsigned char mouseButton) {
	return mouseButtons[mouseButton];
}

void addKeyListener(KeyListener* keyListener) {
	keyListeners.push_back(keyListener);
}

void addMouseListener(MouseListener* mouseListener) {
	mouseListeners.push_back(mouseListener);
}

void removeKeyListener(KeyListener* keyListener) {
	keyListeners.remove(keyListener);
	delete keyListener;
}

void removeMouseListener(MouseListener* mouseListener) {
	mouseListeners.remove(mouseListener);
	delete mouseListener;
}

void destroyInput() {
	for (list<KeyListener*>::iterator it = keyListeners.begin();
			it != keyListeners.end();) {
		delete ((KeyListener*) *it);
		it = keyListeners.erase(it);
	}
	for (list<MouseListener*>::iterator it = mouseListeners.begin();
			it != mouseListeners.end();) {
		delete ((MouseListener*) *it);
		it = mouseListeners.erase(it);
	}
}


KeyListener::~KeyListener() {

}

MouseListener::~MouseListener() {

}
