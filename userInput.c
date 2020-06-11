#include "userInput.h"

const int true = 1;
const int false = 0;


/****************************
        CAMERA
****************************/

float angle=0;
float angle1 = 0;
// actual vector representing the camera's direction
float lx = 0;
float ly = 0;       //default values just to start looking where I want
float lz = 0;
// XYZ position of the camera
float xc = 5;
float yc = 1;
float zc = 5;
float speed = 0.1;

/*************************
        MOUSE
*************************/
float xrotSpeed = 0.0005f;    //mouse sensitivity
float yrotSpeed = 0.0004f;    //mouse sensitivity
int mx, my;
int lmbPressed = 0;        //left mouse button pressed = false

void mouseMovement(int x, int y)
{
    mx = x;     //mouse x
    my = y;     //mouse y
}

void mouseClick(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        lmbPressed = true;
    else
        lmbPressed = false;
}

void processMouse(void)
{
    int dx = mx - (1920/2);     //TODO: Make these  height/width variables
    int dy = my - (1080/2);
    angle = angle+dx*xrotSpeed;
    angle1 = angle1+dy*yrotSpeed;        //spooky math magic
    lx=sin(angle1)*sin(angle);
    ly=cos(angle1);
    lz=-sin(angle1)*cos(angle);

    glutWarpPointer((1920/2), (1080/2));

    if(lmbPressed && ballHeld)
    {
        ball1CurrPos[0] = xc + lx * 2;       //direction we are looking, 2 units away from us
        ball1CurrPos[1] = yc + ly * 2;
        ball1CurrPos[2] = zc + lz * 2;

        ball1PrevPos[0] = xc + lx;
        ball1PrevPos[1] = yc + ly;
        ball1PrevPos[2] = zc + lz;

        ball1ThrowVel[0] = lx * speed * 10;     //set velocity to direction we are facing
        ball1ThrowVel[1] = ly * speed * 10;
        ball1ThrowVel[2] = lz * speed * 10;

        ballHeld = false;
    }

}



/**************************
        KEYBOARD
**************************/

int* keyStates[256];    //array of 'booleans'

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true;     //set the key to pressed
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = false;     //set the key to released
}

void processKeys(void)
{
    if(keyStates[27])      //escape key
        exit(0);
    if(keyStates['1'])       //press 1 to reset
    {
        resetObjects();
    }

    if(keyStates['w'])      //move forward
    {
        xc += lx * speed;
        zc += lz * speed;
    }
    if(keyStates['W'])      //sprint forward
    {
        xc += lx * speed * 5;
        zc += lz * speed * 5;
    }
    if(keyStates['s'])      //move backward
    {
        xc -= lx * speed;
        zc -= lz * speed;
    }
    if(keyStates['d'])      //strafe right
    {
        xc -= lz * speed;
        zc += lx * speed;
    }
    if(keyStates['a'])      //strafe left
    {
        xc += lz * speed;
        zc -= lx * speed;
    }
    if(keyStates[32])       //space to fly up
        yc += speed;

    if(keyStates['c'])      //fly down
    {
        if(yc > 1)      //stop from going through ground
            yc -= speed;
    }

    if(keyStates['r'] && ballHeld)      //rotatea d
    {
        ball1YRotationAngle += 1.0f;
        if(ball1YRotationAngle > 360.0f)
            ball1YRotationAngle -= 360.0f;
    }
    if(keyStates['k'] && ballHeld)   //if 'j' scale increases
        ball1Scale += 0.05f;
    if(keyStates['j'] && ballHeld)   //if 'k' scale decreases
        ball1Scale -= 0.05f;

    if(keyStates['m'])
        gravMultiplier += 0.01;

    if(keyStates['n'])
        gravMultiplier -= 0.01;

     // distance formula: (P1,P2) = sqrt( (x2 -x1)^2 + (y2-y1)^2 + (z )
    double ball1Distance = fabs((sqrt( pow((xc - ball1CurrPos[0]), 2) + pow((yc - ball1CurrPos[1]), 2) + pow((zc - ball1CurrPos[2]), 2))));
    if(ball1Distance < 5)
        ball1Near = true;
    else
        ball1Near = false;

    if(keyStates['e'] && ball1Near)
        ballHeld = true;

    double ball2Distance = fabs((sqrt( pow((xc - ball2CurrPos[0]), 2) + pow((yc - ball2CurrPos[1]), 2) + pow((zc - ball2CurrPos[2]), 2))));
    if(ball2Distance < 5)
        ball2Near = true;
    else
        ball2Near = false;

    if(keyStates['e'] && ball2Near)
    {
        ballSwap();
        ballHeld = true;
    }

    if(ballHeld)
    {
        ball1CurrPos[0] = xc + lx * 2;       //direction we are looking, 2 units away from us
        ball1CurrPos[1] = yc + ly * 2;
        ball1CurrPos[2] = zc + lz * 2;

        ball1ThrowVel[0] = 0;
        ball1ThrowVel[1] = 0;
        ball1ThrowVel[2] = 0;
    }


}
