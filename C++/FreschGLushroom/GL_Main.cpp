#include <GL/freeglut.h>
#include <GL/glu.h>
#include "InternalGL.h"
#include "FreschGLushroom.h"
#include <iostream>
#include <time.h>
#include <list>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

int width = 0;
int height = 0;

GLuint selection = 0;

void (*renderCallback)(void);

void init(int argc, char** argv) {
	try {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(640, 480);
		glutCreateWindow("Simple GLUT Application");

		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		glutDisplayFunc(render);
		glutIdleFunc(render);
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		glutKeyboardFunc(keyboardDown);
		glutKeyboardUpFunc(keyboardUp);
		glutSpecialFunc(specialKeyboardDown);
		glutSpecialUpFunc(specialKeyboardUp);
		glutMouseFunc(mouse);
		glutPassiveMotionFunc(mouseMotion);

		glutReshapeFunc(changeSize);
	} catch (...) {
		cout << "Unexpected exception." << endl;
	}
}

void startRenderLoop() {
	glutMainLoop();
	glFlush();
}

GLuint* processHits(int hits, GLuint* buffer) {
	GLuint min = 0xffffffff, *names = new GLuint[16];
	int index = 0;
	for (int i = 0; i < hits; i++) {
		int noNames = buffer[index];
		GLuint minDepth = buffer[++index];
		index += 2;
		if (min > minDepth) {
			min = minDepth;
			for (int j = 0; j < noNames; j++) {
				names[j] = buffer[index + j];
			}
		}
		index += noNames;
	}
	return names;
}

void render(void) {
	if (renderCallback != NULL) {
		renderCallback();

		GLuint* buffer = new GLuint[1024];
		for (int i = 0; i < 1024; i++) {
			buffer[i] = -1;
		}
		glSelectBuffer(10, buffer);
		glRenderMode(GL_SELECT);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		int* viewport = new int[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		int x, y;
		if (isCursorGrabbed()) {
			x = width / 2;
			y = height / 2;
		} else {
			x = getMouseX();
			y = getMouseY();
		}
		gluPickMatrix(x, viewport[3] - y, 5, 5, viewport);
		gluPerspective(45, width / height, 0.1, 500);
		glMatrixMode(GL_MODELVIEW);
		glInitNames();
		renderCallback();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glFlush();
		int hits = glRenderMode(GL_RENDER);
		GLuint* hit = processHits(hits, buffer);
		selection = hit[0];
		delete[] viewport;
		delete[] buffer;
		delete[] hit;
	}
	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = 1.0 * w / h;

	apply3DMatrix(45, ratio, 0.001, 1000);

	glViewport(0, 0, w, h);

	width = w;
	height = h;
}

int getWidth() {
	return width;
}

int getHeight() {
	return height;
}

void registerRenderMethod(void (*callback)(void)) {
	renderCallback = callback;
}

void destroy() {
	destroyInput();
	glFlush();
}

void apply3DMatrix(GLdouble fov, GLdouble aspectRatio, GLdouble zNear, GLdouble zFar) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspectRatio, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}

void apply2DMatrix(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

GLuint getSelection() {
	return selection;
}

#ifdef __linux__
	void ReleaseCursor() {
		Display *display;
		display = XOpenDisplay(NULL);
		XUngrabPointer(display, CurrentTime);
	};
	
	void ClipCursor(RECT * rect) {
		if(rect == NULL) {
			ReleaseCursor();
		} else {
			Display *display;
			Window window;
			window = glutGetWindow();
			display = XOpenDisplay(NULL);
			XGrabPointer(display, window, True, 0, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
		}
		
	};
#endif