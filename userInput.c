#include "userInput.h"


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
float xc = 0;
float yc = 1;
float zc = 10;
float speed = 0.1;

/*************************
        MOUSE
*************************/
float xrotSpeed = 0.0005f;    //mouse sensitivity
float yrotSpeed = 0.0004f;    //mouse sensitivity
int mx, my;

void mouseMovement(int x, int y)
{
    mx = x;     //mouse x
    my = y;     //mouse y
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
}


/**************************
        KEYBOARD
**************************/

const int true = 1;
const int false = 0;
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
    if(keyStates[49])       //press 1 to drop ball again
    {
        currPos[1] = 0;
        currPos[1] = 100;
        currPos[1] = 0;

        prevPos[0] = 0;
        prevPos[1] = 0;
        prevPos[2] = 0;
    }
    if(keyStates[50])       //press 2 to throw ball
    {
        resetObject();

        currPos[0] = xc + lx * 2;       //direction we are looking, 2 units away from us
        currPos[1] = yc + ly * 2;
        currPos[2] = zc + lz * 2;

        prevPos[0] = xc + lx;
        prevPos[1] = yc + ly;
        prevPos[2] = zc + lz;

        v0[0] = lx * speed * 15;     //set velocity to direction we are facing
        v0[1] = ly * speed * 15;
        v0[2] = lz * speed * 15;
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

    if(keyStates['r'])      //rotatea d
    {
        yRotationAngle += 1.0f;
        if(yRotationAngle > 360.0f)
            yRotationAngle -= 360.0f;
    }
    if(keyStates[43])   //if '+' scale increases
        objScale += 0.05f;
    if(keyStates[45])   //if '-' scale decreases
        objScale -= 0.05f;

}
