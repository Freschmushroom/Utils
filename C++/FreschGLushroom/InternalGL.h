#ifndef INTERNALGL_H_
#define INTERNALGL_H_

void render(void);

void keyboard(unsigned char, bool, int, int);
void keyboardDown(unsigned char, int, int);
void keyboardUp(unsigned char, int, int);

void specialKeyboard(int, bool, int, int);
void specialKeyboardDown(int, int, int);
void specialKeyboardUp(int, int, int);

void mouse(int, int, int, int);
void mouseMotion(int, int);

void changeSize(int, int);

void destroyInput();

#endif
