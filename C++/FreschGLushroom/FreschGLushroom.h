#ifndef FRESCHGLUSHROOM_H_
#define FRESCHGLUSHROOM_H_

#include "Events.h"
#include <GL/glut.h>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

void init(int arc, char** argv);
void startRenderLoop();

void setCursorGrabbed(bool isCursorGrabbed);
void grabCursor();
void ungrabCursor();

bool isCursorGrabbed();

bool isKeyDown(unsigned char key);
bool isSpecialKeyDown(unsigned char specialKey);

bool isMouseButtonDown(unsigned char mouseButton);

int getMouseX();
int getMouseY();

void addKeyListener(KeyListener* keyListener);
void addMouseListener(MouseListener* mouseListener);
void removeKeyListener(KeyListener* keyListener);
void removeMouseListener(MouseListener* mouseListener);

void registerRenderMethod(void (* callback) (void));

int getWidth();
int getHeight();

void destroy();

void apply3DMatrix(GLdouble fov, GLdouble aspectRatio, GLdouble zNear, GLdouble zFar);
void apply2DMatrix(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);

GLuint getSelection();

#ifdef __linux__
	typedef struct rect_struct {
		long left;
		long top;
		long right;
		long bottom;
	} RECT;
	
	void ReleaseCursor();
	void ClipCursor(RECT * rect);
#endif /* Linux */

#endif

