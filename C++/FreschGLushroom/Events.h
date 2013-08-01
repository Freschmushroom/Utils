#ifndef EVENTS_H_
#define EVENTS_H_


class KeyListener {
public:
	virtual void keyPressed(unsigned char key, int x, int y) = 0;
	virtual void keyReleased(unsigned char key, int x, int y) = 0;

	virtual void specialKeyPressed(unsigned char specialKey, int x, int y) = 0;
	virtual void specialKeyReleased(unsigned char specialKey, int x, int y) = 0;

	virtual ~KeyListener();
};

class MouseListener {
public:
	virtual void mousePressed(int button, int x, int y) = 0;
	virtual void mouseReleased(int button, int x, int y) = 0;

	virtual void mouseMoved(int oldX, int oldY, int newX, int newY) = 0;

	virtual ~MouseListener();
};

#endif
