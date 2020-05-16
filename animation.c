#include "animation.h"

/*********************************
        OBJECT MOVEMENT
**********************************/
float startTime;
float prevTime;

typedef GLfloat point3[3];

float dropOff = 0.70;      // speed will drop with 30% at each bounce

point3 g = {0, -9.8, 0};	// this is the acceleration
point3 startPos = {0, 20, 0};	// the initial position
point3 currPos, prevPos;	// the current and previous location of the centre of the ball
point3 v0 ={0, 0, 0}; 		// initial velocity - set to 0 in all directions
point3 currVel, prevVel; 		// current and previous velocity

float yRotationAngle = 0.0f;
float objScale = 1.0f;

void animate(void)
{
     glutTimerFunc(TIMERSECS, animate, 0);

    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0 ;     // to convert the returned into seconds
    float timeSincePrevFrame = currTime - prevTime;	// time since previous frame


    // Calculate all the forces that are currently applied to the ball

    // Calculate acceleration
    // In our case, it is just the gravity g


    // Move one step
    currPos[0] = prevPos[0] + prevVel[0] * timeSincePrevFrame + v0[0] + g[0] * timeSincePrevFrame * timeSincePrevFrame / 2;
    currPos[1] = prevPos[1] + prevVel[1] * timeSincePrevFrame + v0[1] + g[1] * timeSincePrevFrame * timeSincePrevFrame / 2;
    currPos[2] = prevPos[2] + prevVel[2] * timeSincePrevFrame + v0[2] + g[2] * timeSincePrevFrame * timeSincePrevFrame / 2;

    // Calculate current velocity
    currVel[0] = prevVel[0] + v0[0] + g[0] * timeSincePrevFrame;
    currVel[1] = prevVel[1] + v0[1] + g[1] * timeSincePrevFrame;
    currVel[2] = prevVel[2] + v0[2] + g[2] * timeSincePrevFrame;

    // Check collision
    float distToFloor = sqrt(currPos[0]*currPos[0] + currPos[1]*currPos[1] + currPos[2] * currPos[2]);

    if (currPos[1] <= objScale + objScale*0.075) //distToFloor <= ballSize + a litte extra to stop glitching
    {

        currVel[0] = - currVel[0] * dropOff;
        currVel[1] = - currVel[1] * dropOff;
        currVel[2] = - currVel[2] * dropOff;

        v0[0] *= 0.8;
        v0[1] *= 0.8;
        v0[2] *= 0.8;

        currPos[1] = objScale;
    }

 // Put curPos to prevPos
    prevPos[0] = currPos[0];
    prevPos[1] = currPos[1];
    prevPos[2] = currPos[2];

    prevVel[0] = currVel[0];
    prevVel[1] = currVel[1];
    prevVel[2] = currVel[2];

    prevTime = currTime;

}

void resetObject(void)
{
    currPos[0] = startPos[0];
    currPos[1] = startPos[1];
    currPos[2] = startPos[2];

    prevPos[0] = startPos[0];
    prevPos[1] = startPos[1];
    prevPos[2] = startPos[2];

    prevVel[0] = 0;
    prevVel[1] = 0;
    prevVel[2] = 0;

    currVel[0] = 0;
    currVel[1] = 0;
    currVel[2] = 0;
}
