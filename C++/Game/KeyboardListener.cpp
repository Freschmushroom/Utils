#include "Go.h"
#include <iostream>

using std::cout;
using std::endl;

void KeyboardListener::keyPressed(unsigned char key, int x, int y) {
	cout << "key " << (int) key << endl;
}

void KeyboardListener::keyReleased(unsigned char key, int x, int y) {

}

void KeyboardListener::specialKeyPressed(unsigned char key, int x, int y) {
	cout << "special key " << (int) key << endl;
}

void KeyboardListener::specialKeyReleased(unsigned char key, int x, int y) {

}
