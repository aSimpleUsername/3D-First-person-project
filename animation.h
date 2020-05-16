//animation.h - animation for assignment 2
//Connor Nicholson
//16 May 20

#ifndef ANIMATION_H
#define ANIMATION_H

#include <GL/freeglut.h>

#define TIMERSECS 1000/60   //ms in a seccond / frames per seccond

extern float startTime;
extern float prevTime;
typedef GLfloat point3[3];

extern float dropOff;      // speed will drop with 30% at each bounce

extern point3 g;	// this is the acceleration
extern point3 startPos;	// the initial position
extern point3 currPos, prevPos;	// the current and previous location of the centre of the ball
extern point3 v0; 		// initial velocity - set to 0 in all directions
extern point3 currVel, prevVel; 		// current and previous velocity

extern float yRotationAngle;
extern float objScale;

/****************************************************************/

void animate(void);

void resetObject(void);



#endif
