//userInput.c - User input for assignment 2
//Connor Nicholson
//16 May 20

#ifndef USERINPUT_H
#define USERINPUT_H

#include <GL/freeglut.h>
#include "animation.h"

extern float angle;
extern float angle1;
// actual vector representing the camera's direction
extern float lx;
extern float ly;
extern float lz;
// XYZ position of the camera
extern float xc;
extern float yc;
extern float zc;
extern float speed;

extern float xrotSpeed;    //mouse sensitivity
extern float yrotSpeed;    //mouse sensitivity

/************************************************************/

void mouseMovement(int x, int y);

void mouseClick(int button, int state, int x, int y);

void processMouse(void);

void keyPressed(unsigned char key, int x, int y);

void keyUp(unsigned char key, int x, int y);

void processKeys(void);

#endif // USERINPUT_H

