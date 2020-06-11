#include "animation.h"

/*********************************
        OBJECT MOVEMENT
**********************************/
float startTime;
float prevTime;

typedef GLfloat point3[3];

float dropOff = 0.50;      // speed will drop 50% at each bounce

float gravity = -9.8;
float airResist = 0;
float gravMultiplier = 1;
point3 gravVel = {0, 0, 0};  // initialise, gravity is assigned later

// Ball 1
point3 ball1StartPos = {0, 2, 5};	// the initial position
point3 ball1CurrPos, ball1PrevPos;	// the current and previous location of the centre of the ball
point3 ball1ThrowVel ={0, 0, 0}; 		// initial velocity - set to 0 in all directions
point3 ball1CurrVel, ball1PrevVel; 		// current and previous velocity
float ball1YRotationAngle = 0.0f;
float ball1Scale = 1.0f;

// Ball 2
point3 ball2StartPos = {0, 10, 0 };	// the initial position
point3 ball2CurrPos, ball2PrevPos;	// the current and previous location of the centre of the ball
point3 ball2ThrowVel ={0, 0, 0}; 		// initial velocity - set to 0 in all directions
point3 ball2CurrVel, ball2PrevVel; 		// current and previous velocity
float ball2YRotationAngle = 0.0f;
float ball2Scale = 1.0f;

void animate(void)
{
    glutTimerFunc(TIMERSECS, animate, 0);

    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0 ;     // to convert the returned into seconds
    float timeSincePrevFrame = currTime - prevTime;	// time since previous frame


    // Calculate all the forces that are currently applied to the ball

    // Calculate acceleration
    // In our case, it is just the gravity g

    gravVel[1] = gravity * gravMultiplier;

    // Move one step
    ball1CurrPos[0] = ball1PrevPos[0] + ball1PrevVel[0] * timeSincePrevFrame + ball1ThrowVel[0] + gravVel[0] * timeSincePrevFrame * timeSincePrevFrame / 2;
    ball1CurrPos[1] = ball1PrevPos[1] + ball1PrevVel[1] * timeSincePrevFrame + ball1ThrowVel[1] + gravVel[1] * timeSincePrevFrame * timeSincePrevFrame / 2;
    ball1CurrPos[2] = ball1PrevPos[2] + ball1PrevVel[2] * timeSincePrevFrame + ball1ThrowVel[2] + gravVel[2] * timeSincePrevFrame * timeSincePrevFrame / 2;

    ball2CurrPos[0] = ball2PrevPos[0] + ball2PrevVel[0] * timeSincePrevFrame + ball2ThrowVel[0] + gravVel[0] * timeSincePrevFrame * timeSincePrevFrame / 2;
    ball2CurrPos[1] = ball2PrevPos[1] + ball2PrevVel[1] * timeSincePrevFrame + ball2ThrowVel[1] + gravVel[1] * timeSincePrevFrame * timeSincePrevFrame / 2;
    ball2CurrPos[2] = ball2PrevPos[2] + ball2PrevVel[2] * timeSincePrevFrame + ball2ThrowVel[2] + gravVel[2] * timeSincePrevFrame * timeSincePrevFrame / 2;

    // Calculate current velocity
    ball1CurrVel[0] = ball1PrevVel[0] + ball1ThrowVel[0] + gravVel[0] * timeSincePrevFrame;
    ball1CurrVel[1] = ball1PrevVel[1] + ball1ThrowVel[1] + gravVel[1] * timeSincePrevFrame;
    ball1CurrVel[2] = ball1PrevVel[2] + ball1ThrowVel[2] + gravVel[2] * timeSincePrevFrame;

    ball2CurrVel[0] = ball2PrevVel[0] + ball2ThrowVel[0] + gravVel[0] * timeSincePrevFrame;
    ball2CurrVel[1] = ball2PrevVel[1] + ball2ThrowVel[1] + gravVel[1] * timeSincePrevFrame;
    ball2CurrVel[2] = ball2PrevVel[2] + ball2ThrowVel[2] + gravVel[2] * timeSincePrevFrame;

    // Check collision
    //Ball 1 and ground
    if (ball1CurrPos[1] <= ball1Scale + ball1Scale*0.075) //current position <= ballSize + a litte extra to stop glitching
    {
        ball1CurrVel[0] = ball1CurrVel[0] * dropOff;
        ball1CurrVel[1] = -ball1CurrVel[1] * dropOff;
        ball1CurrVel[2] = ball1CurrVel[2] * dropOff;

        ball1ThrowVel[0] = ball1ThrowVel[0] * dropOff;
        ball1ThrowVel[1] = -ball1ThrowVel[1] * dropOff;        //ball should bounce up but continue same along x/z
        ball1ThrowVel[2] = ball1ThrowVel[2] * dropOff;

        ball1CurrPos[1] = ball1Scale;
    }

    //Ball 2 and ground
    if (ball2CurrPos[1] <= ball2Scale + ball2Scale*0.075) //current position <= ballSize + a litte extra to stop glitching
    {
        ball2CurrVel[0] = ball2CurrVel[0] * dropOff;
        ball2CurrVel[1] = -ball2CurrVel[1] * dropOff;
        ball2CurrVel[2] = ball2CurrVel[2] * dropOff;

        ball2ThrowVel[0] = ball2ThrowVel[0] * dropOff;
        ball2ThrowVel[1] = -ball2ThrowVel[1] * dropOff;        //ball should bounce up but continue same along x/z
        ball2ThrowVel[2] = ball2ThrowVel[2] * dropOff;

        ball2CurrPos[1] = ball2Scale;
    }

        //ball 1 vs pillar
    if(ball1CurrPos[0] - ball1Scale <= pillarStats.xmax && ball1CurrPos[0] + ball1Scale >= pillarStats.xmin &&
        ball1CurrPos[1] - ball1Scale <= pillarStats.ymax && ball1CurrPos[1] + ball1Scale >= pillarStats.ymin &&
        ball1CurrPos[2] - ball1Scale <= pillarStats.zmax && ball1CurrPos[2] + ball1Scale >= pillarStats.zmin)   //wall <= ballSize + a litte extra to stop glitching
    {
        if(ball1CurrPos[1] + ball1Scale >= pillarStats.ymax)  //if hit the top of pillar
        {
            //ground physics
            ball1CurrVel[0] = ball1CurrVel[0] * dropOff;
            ball1CurrVel[1] = -ball1CurrVel[1] * dropOff;
            ball1CurrVel[2] = ball1CurrVel[2] * dropOff;

            ball1ThrowVel[0] = ball1ThrowVel[0] * dropOff;
            ball1ThrowVel[1] = -ball1ThrowVel[1] * dropOff;        //ball should bounce up but continue same along x/z
            ball1ThrowVel[2] = ball1ThrowVel[2] * dropOff;

            ball1CurrPos[1] = pillarStats.ymax + ball1Scale;
        }
        else
        {
            ball1CurrVel[0] = - ball1CurrVel[0];
            //ball1CurrVel[1] = ball1CurrVel[1];    //remains unchanged
            ball1CurrVel[2] = - ball1CurrVel[2];

            ball1ThrowVel[0] = -ball1ThrowVel[0] * dropOff/2;
            ball1ThrowVel[1] = ball1ThrowVel[1] * dropOff;     //ball should keep going up/down but will bounce back on x/z axis
            ball1ThrowVel[2] = -ball1ThrowVel[2] * dropOff/2;
        }
    }

        //ball2 vs pillar
    if(ball2CurrPos[0] - ball2Scale <= pillarStats.xmax && ball2CurrPos[0] + ball2Scale >= pillarStats.xmin &&
        ball2CurrPos[1] - ball2Scale <= pillarStats.ymax && ball2CurrPos[1] + ball2Scale >= pillarStats.ymin &&
        ball2CurrPos[2] - ball2Scale <= pillarStats.zmax && ball2CurrPos[2] + ball2Scale >= pillarStats.zmin)   //wall <= ballSize + a litte extra to stop glitching
    {
        if(ball2CurrPos[1] + ball1Scale >= pillarStats.ymax)  //if hit the top of pillar
        {
            //ground physics
            ball2CurrVel[0] = ball2CurrVel[0] * dropOff;
            ball2CurrVel[1] = -ball2CurrVel[1] * dropOff;
            ball2CurrVel[2] = ball2CurrVel[2] * dropOff;

            ball2ThrowVel[0] = ball2ThrowVel[0] * dropOff;
            ball2ThrowVel[1] = -ball2ThrowVel[1] * dropOff;        //ball should bounce up but continue same along x/z
            ball2ThrowVel[2] = ball2ThrowVel[2] * dropOff;

            ball2CurrPos[1] = pillarStats.ymax + ball2Scale;
        }
        else
        {
            ball2CurrVel[0] = - ball2CurrVel[0];
            //ball1CurrVel[1] = ball1CurrVel[1];    //remains unchanged
            ball2CurrVel[2] = - ball2CurrVel[2];

            ball2CurrVel[0] = -ball2CurrVel[0] * dropOff/2;
            ball2CurrVel[1] = ball2CurrVel[1] * dropOff;     //ball should keep going up/down but will bounce back on x/z axis
            ball2CurrVel[2] = -ball2CurrVel[2] * dropOff/2;
        }
    }


    //ball1 vs walls
    if((ball1CurrPos[0] - ball1Scale <= wall1Stats.xmax && ball1CurrPos[0] + ball1Scale >= wall1Stats.xmin &&
        ball1CurrPos[1] - ball1Scale <= wall1Stats.ymax && ball1CurrPos[1] + ball1Scale >= wall1Stats.ymin &&
        ball1CurrPos[2] - ball1Scale <= wall1Stats.zmax && ball1CurrPos[2] + ball1Scale >= wall1Stats.zmin) ||      //wall 1
       (ball1CurrPos[0] - ball1Scale <= wall2Stats.xmax && ball1CurrPos[0] + ball1Scale >= wall2Stats.xmin &&
        ball1CurrPos[1] - ball1Scale <= wall2Stats.ymax && ball1CurrPos[1] + ball1Scale >= wall2Stats.ymin &&
        ball1CurrPos[2] - ball1Scale <= wall2Stats.zmax && ball1CurrPos[2] + ball1Scale >= wall2Stats.zmin) ||      //wall 2
       (ball1CurrPos[0] - ball1Scale <= wall3Stats.xmax && ball1CurrPos[0] + ball1Scale >= wall3Stats.xmin &&
        ball1CurrPos[1] - ball1Scale <= wall3Stats.ymax && ball1CurrPos[1] + ball1Scale >= wall3Stats.ymin &&
        ball1CurrPos[2] - ball1Scale <= wall3Stats.zmax && ball1CurrPos[2] + ball1Scale >= wall3Stats.zmin) ||      //wall 4
       (ball1CurrPos[0] - ball1Scale <= wall4Stats.xmax && ball1CurrPos[0] + ball1Scale >= wall4Stats.xmin &&
        ball1CurrPos[1] - ball1Scale <= wall4Stats.ymax && ball1CurrPos[1] + ball1Scale >= wall4Stats.ymin &&
        ball1CurrPos[2] - ball1Scale <= wall4Stats.zmax && ball1CurrPos[2] + ball1Scale >= wall4Stats.zmin))        //wall 4
    {

        ball1CurrVel[0] = - ball1CurrVel[0];
        //currVel[1] = - currVel[1];
        ball1CurrVel[2] = - ball1CurrVel[2];

        ball1ThrowVel[0] = -ball1ThrowVel[0] * dropOff/2;
        ball1ThrowVel[1] = ball1ThrowVel[1] * dropOff;     //ball should keep going up/down but will bounce back on x/z axis
        ball1ThrowVel[2] = -ball1ThrowVel[2] * dropOff/2;
    }

        //ball2 vs walls
    if((ball2CurrPos[0] - ball2Scale <= wall1Stats.xmax && ball2CurrPos[0] + ball2Scale >= wall1Stats.xmin &&
        ball2CurrPos[1] - ball2Scale <= wall1Stats.ymax && ball2CurrPos[1] + ball2Scale >= wall1Stats.ymin &&
        ball2CurrPos[2] - ball2Scale <= wall1Stats.zmax && ball2CurrPos[2] + ball2Scale >= wall1Stats.zmin) ||      //wall 1
       (ball2CurrPos[0] - ball2Scale <= wall2Stats.xmax && ball2CurrPos[0] + ball2Scale >= wall2Stats.xmin &&
        ball2CurrPos[1] - ball2Scale <= wall2Stats.ymax && ball2CurrPos[1] + ball2Scale >= wall2Stats.ymin &&
        ball2CurrPos[2] - ball2Scale <= wall2Stats.zmax && ball2CurrPos[2] + ball2Scale >= wall2Stats.zmin) ||      //wall 2
       (ball2CurrPos[0] - ball2Scale <= wall3Stats.xmax && ball2CurrPos[0] + ball2Scale >= wall3Stats.xmin &&
        ball2CurrPos[1] - ball2Scale <= wall3Stats.ymax && ball2CurrPos[1] + ball2Scale >= wall3Stats.ymin &&
        ball2CurrPos[2] - ball2Scale <= wall3Stats.zmax && ball2CurrPos[2] + ball2Scale >= wall3Stats.zmin) ||      //wall 4
       (ball2CurrPos[0] - ball2Scale <= wall4Stats.xmax && ball2CurrPos[0] + ball2Scale >= wall4Stats.xmin &&
        ball2CurrPos[1] - ball2Scale <= wall4Stats.ymax && ball2CurrPos[1] + ball2Scale >= wall4Stats.ymin &&
        ball2CurrPos[2] - ball2Scale <= wall4Stats.zmax && ball2CurrPos[2] + ball2Scale >= wall4Stats.zmin))        //wall 4
    {

        ball2CurrVel[0] = - ball2CurrVel[0];
        //currVel[1] = - currVel[1];
        ball2CurrVel[2] = - ball2CurrVel[2];

        ball2ThrowVel[0] = -ball2ThrowVel[0] * dropOff/2;
        ball2ThrowVel[1] = ball2ThrowVel[1] * dropOff;     //ball should keep going up/down but will bounce back on x/z axis
        ball2ThrowVel[2] = -ball2ThrowVel[2] * dropOff/2;
    }

    //collision with balls into each other
    // distance formula: (P1,P2) = sqrt( (x2 -x1)^2 + (y2-y1)^2 + (z )
    double distance = fabs((sqrt( pow((ball2CurrPos[0] - ball1CurrPos[0]), 2) + pow((ball2CurrPos[1] - ball1CurrPos[1]), 2) + pow((ball2CurrPos[2] - ball1CurrPos[2]), 2))));
    if(distance <= ball1Scale + ball2Scale)//little extra to avoid glitching
     {
        // Ball 2 physics
        ball2CurrVel[0] = ball1CurrVel[0];
        ball2CurrVel[1] = ball1CurrVel[1];
        ball2CurrVel[2] = ball1CurrVel[2];

        ball2ThrowVel[0] = ball1ThrowVel[0];
        ball2ThrowVel[1] = ball1ThrowVel[1];
        ball2ThrowVel[2] = ball1ThrowVel[2];

        //Ball 1 physics
        ball1CurrVel[0] = - ball1CurrVel[0];
        if(ball2CurrPos[1] + ball2Scale < 0 + (ball2Scale * 0.075))      //if ball 2 on the ground plus a little extra to avoid glitching
           ball1CurrVel[1] = -ball1CurrVel[1];      //reverse y velocity  else maintain it
        ball1CurrVel[2] = - ball1CurrVel[2];

        //ball 1 velocity deprication
        ball1ThrowVel[0] = -ball1ThrowVel[0] * dropOff/2;
        if(ball2CurrPos[1] + ball2Scale < 0 + (ball2Scale * 0.075)) //if ball 2 on the ground plus a little extra to avoid glitching
            ball1ThrowVel[1] = -ball1ThrowVel[1] * dropOff;  //reverse y velocity  else maintain it
        else
            ball1ThrowVel[1] = ball1ThrowVel[1] * dropOff;     //ball should keep going up/down but will bounce back on x/z axis
        ball1ThrowVel[2] = -ball1ThrowVel[2] * dropOff/2;
    }

 // Put curPos to prevPos
    //Ball 1
    ball1PrevPos[0] = ball1CurrPos[0];
    ball1PrevPos[1] = ball1CurrPos[1];
    ball1PrevPos[2] = ball1CurrPos[2];

    ball1PrevVel[0] = ball1CurrVel[0];
    ball1PrevVel[1] = ball1CurrVel[1];
    ball1PrevVel[2] = ball1CurrVel[2];

    //Ball 2
    ball2PrevPos[0] = ball2CurrPos[0];
    ball2PrevPos[1] = ball2CurrPos[1];
    ball2PrevPos[2] = ball2CurrPos[2];

    ball2PrevVel[0] = ball2CurrVel[0];
    ball2PrevVel[1] = ball2CurrVel[1];
    ball2PrevVel[2] = ball2CurrVel[2];

    prevTime = currTime;
}

void resetObjects(void)
{
    // Ball 1
    ball1CurrPos[0] = ball1StartPos[0];
    ball1CurrPos[1] = ball1StartPos[1];
    ball1CurrPos[2] = ball1StartPos[2];

    ball1PrevPos[0] = ball1StartPos[0];
    ball1PrevPos[1] = ball1StartPos[1];
    ball1PrevPos[2] = ball1StartPos[2];

    ball1PrevVel[0] = 0;
    ball1PrevVel[1] = 0;
    ball1PrevVel[2] = 0;

    ball1CurrVel[0] = 0;
    ball1CurrVel[1] = 0;
    ball1CurrVel[2] = 0;

    ball1ThrowVel[0] = 0;
    ball1ThrowVel[1] = 0;
    ball1ThrowVel[2] = 0;

    // Ball 2
    ball2CurrPos[0] = ball2StartPos[0];
    ball2CurrPos[1] = ball2StartPos[1];
    ball1CurrPos[2] = ball1StartPos[2];

    ball2PrevPos[0] = ball2StartPos[0];
    ball2PrevPos[1] = ball2StartPos[1];
    ball2PrevPos[2] = ball2StartPos[2];

    ball2PrevVel[0] = 0;
    ball2PrevVel[1] = 0;
    ball2PrevVel[2] = 0;

    ball2CurrVel[0] = 0;
    ball2CurrVel[1] = 0;
    ball2CurrVel[2] = 0;

    ball2ThrowVel[0] = 0;
    ball2ThrowVel[1] = 0;
    ball2ThrowVel[2] = 0;
}

void ballSwap()
{
    // temp storage
    point3 tempCurrPos, tempPrevPos;	// the current and previous location of the centre of the ball
    point3 tempThrowVel ={0, 0, 0}; 		// initial velocity - set to 0 in all directions
    point3 tempCurrVel, tempPrevVel; 		// current and previous velocity
    float tempYRotationAngle = 0.0f;
    float tempScale = 0.0f;

    memcpy(tempCurrPos, ball1CurrPos, sizeof(float)*3);
    memcpy(tempPrevPos, ball1PrevPos, sizeof(float)*3);
    memcpy(tempThrowVel, ball1ThrowVel, sizeof(float)*3);
    memcpy(tempCurrVel, ball1CurrVel, sizeof(float)*3);
    memcpy(tempPrevVel, ball1PrevVel, sizeof(float)*3);
    tempYRotationAngle = ball1YRotationAngle;
    tempScale = ball1Scale;

    memcpy(ball1CurrPos, ball2CurrPos, sizeof(float)*3);
    memcpy(ball1PrevPos, ball2PrevPos, sizeof(float)*3);
    memcpy(ball1ThrowVel, ball2ThrowVel, sizeof(float)*3);
    memcpy(ball1CurrVel, ball2CurrVel, sizeof(float)*3);
    memcpy(ball1PrevVel, ball2PrevVel, sizeof(float)*3);
    ball1YRotationAngle = ball2YRotationAngle;
    ball1Scale = ball2Scale;

    memcpy(ball2CurrPos, tempCurrPos, sizeof(float)*3);
    memcpy(ball2PrevPos, tempPrevPos, sizeof(float)*3);
    memcpy(ball2ThrowVel, tempThrowVel, sizeof(float)*3);
    memcpy(ball2CurrVel, tempCurrVel, sizeof(float)*3);
    memcpy(ball2PrevVel, tempPrevVel, sizeof(float)*3);
    ball2YRotationAngle = tempYRotationAngle;
    ball2Scale = tempScale;
}
