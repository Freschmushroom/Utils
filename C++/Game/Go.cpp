#include <GL/glut.h>
#include "FreschGLushroom.h"
#include "Go.h"
#ifdef _WIN32
#include "Sockets.h"
#endif
#ifdef __linux__
#include "sockets.h"
#include <GL/glu.h>
#endif
#include <iostream>
#include <string>
#include <math.h>
#include <boost/thread.hpp>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int player = 0;
bool hasDraw = false;
bool isRunning = true;
#ifdef _WIN32
WinSocket* gameSocket;
#endif
#ifdef __linux__
UnixSocket* gameSocket;
#endif
GameField gameField(13);

char* lastPacket = 0;
//class KeyboardListener: public KeyListener {
//public:
//	void keyPressed(unsigned char key, int x, int y) {

//	}

//	void keyReleased(unsigned char key, int x, int y) {

//	}

//	void specialKeyPressed(unsigned char key, int x, int y) {
//	}

//	void specialKeyReleased(unsigned char key, int x, int y) {
//
//	}
//};

void sendClaimRequest(int, int, int);

class ClickListener: public MouseListener {
public:
	void mousePressed(int button, int x, int y) {
		if (!hasDraw) {
			cout << "you cant do that" << endl;
			return;
		}
		if (button == GLUT_LEFT_BUTTON) {
			for (int i = 0; i < gameField.getWidth() * gameField.getWidth();
					i++) {
				Field* field = gameField.getField(i);
				if (field->isMouseHovering && field->getState() == 0) {
					field->claimFor(player);
					render();
					hasDraw = false;
					sendClaimRequest(player, i % gameField.getWidth(),
							i / gameField.getWidth());
				}
			}
		}
	}

	void mouseReleased(int button, int x, int y) {
	}

	void mouseMoved(int oldX, int oldY, int newX, int newY) {
		int fieldWidth = gameField.getFieldWidth();
		int x = (int) ((newX * 1920) / (float) getWidth());
		int y = (int) ((newY * 1080) / (float) getHeight());
		for (int i = 0; i < gameField.getWidth(); i++) {
			for (int j = 0; j < gameField.getWidth(); j++) {
				int fieldX = 500
						+ (int) (920 / (float) (gameField.getWidth() - 1) * i);
				int fieldY = 200
						+ (int) (680 / (float) (gameField.getWidth() - 1) * j);
				Field* field = gameField.getField(i, j);
				if (abs(fieldX - x) <= fieldWidth
						&& abs(fieldY - y) <= fieldWidth) {
					field->isMouseHovering = true;
				} else {
					field->isMouseHovering = false;
				}
			}
		}
	}
};

KeyboardListener keyboardListener;
ClickListener mouseListener;
#ifdef _WIN32
WinSocket* clientOrServer() {
	cout << "Do you play as black or white?" << endl;
	string s;
	cin >> s;
	if (s == "black") {
		player = 1;
		hasDraw = true;
		WinServer* server = new WinServer(50000);
		server->start();
		return server;
	} else {
		player = 2;
		hasDraw = false;
		WinClient* client = new WinClient("127.0.0.1", 50000);
		client->start();
		if (client->isConnected()) {
			return client;
		} else {
			return 0;
		}
	}
}
#endif
#ifdef __linux__
UnixSocket* clientOrServer() {
	cout << "Do you play as black or white?" << endl;
	string s;
	cin >> s;
	if (s == "black") {
		player = 1;
		hasDraw = true;
		UnixServer* server = new UnixServer(50000);
		server->start();
		return server;
	} else {
		player = 2;
		hasDraw = false;
		UnixClient* client = new UnixClient("127.0.0.1", 50000);
		client->start();
		if (client->isConnected()) {
			return client;
		} else {
			return 0;
		}
	}
}
#endif
	

void disconnect() {
	char* buffer = new char[1];
	buffer[0] = -1;
	gameSocket->writeToStream(buffer, 1);
	delete[] buffer;
	isRunning = false;
}

void run() {
	cout << "started receiving thread..." << endl;
	gameSocket->setRecvTimeout(1000);
	while (isRunning) {
		if (lastPacket != 0) {
			continue;
		}
		cout << "waiting for packet..." << endl;
		char buffer[256];
		memset(buffer, 0, 256);
		gameSocket->readFromStream(buffer, 256);
		if (buffer[0] == 0) {
			continue;
		}
		lastPacket = buffer;
	}
	cout << "stopping receiving thread..." << endl;
}

int main(int argc, char** argv) {
	gameSocket = clientOrServer();
	if (gameSocket == 0) {
		cout << "Active game not found." << endl;
		system("PAUSE");
		exit(0);
	}
	init(argc, argv);
	if (player == 1) {
		glutSetWindowTitle("Playing GO! as black.");
	} else if (player == 2) {
		glutSetWindowTitle("Playing GO! as white.");
	}
	boost::thread connectionThread(run);
	registerRenderMethod(update);
	addKeyListener(&keyboardListener);
	addMouseListener(&mouseListener);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	startRenderLoop();
	cout << "Shutting down" << endl;
	//destroy();
	cout << "Disconnecting..." << endl;
	disconnect();
	cout << "Joining thread..." << endl;
	connectionThread.join();
	cout << "Cleaning up heap space..." << endl;
	delete gameSocket;
	system("PAUSE");
}

void claim(char* buffer, int offset) {
	char x = buffer[offset];
	char y = buffer[offset + 1];
	char player = buffer[offset + 2];
	Field* field = gameField.getField(x, y);
	if (field->isEmpty()) {
		field->claimFor(player);
		hasDraw = true;
		cout << "Received response." << endl;
	}
}

void handlePacket(char* packet, int packetSize) {
	switch (packet[0]) {
	case 0:
		return;
	case 1:
		break;
	case 2:
		claim(packet, 1);
		break;
	case -1:
		disconnect();
		break;
	}
}

void renderDisconnectedScreen() {
	glColor4ub(100, 100, 100, 100);
	glRecti(0, 0, 1920, 1080);
}

void update() {
	if (lastPacket != 0) {
		handlePacket(lastPacket, 256);
		delete[] lastPacket;
		lastPacket = 0;
	}
	render();
}

void renderBackground() {
	glColor3ub(201, 146, 53);
	glRecti(400, 140, 1920 - 400, 1080 - 140);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(400, 140);
	glVertex2f(500, 200);
	glVertex2f(400, 1080 - 140);
	glVertex2f(500, 1080 - 200);
	glVertex2f(1920 - 400, 1080 - 140);
	glVertex2f(1920 - 500, 1080 - 200);
	glVertex2f(1920 - 400, 140);
	glVertex2f(1920 - 500, 200);
	glEnd();
	glColor3ub(251, 196, 103);
	glRecti(500, 200, 1920 - 500, 1080 - 200);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	apply2DMatrix(0, 1920, 1080, 0);
	renderBackground();
	gameField.render();
	if (!isRunning) {
		renderDisconnectedScreen();
	}
	glPopMatrix();

	glutSwapBuffers();
}

void sendClaimRequest(int player, int x, int y) {
	char* buffer = new char[4];
	buffer[0] = (char) 2;
	buffer[1] = (char) x;
	buffer[2] = (char) y;
	buffer[3] = (char) player;
	gameSocket->writeToStream(buffer, 4);
	delete[] buffer;
}
