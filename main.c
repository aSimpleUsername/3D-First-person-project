//assignment 2 ICT289

#include <GL/freeglut.h>
#include <math.h>
#include "drawScene.h"
#include "userInput.h"
#include "animation.h"
#include "modelLoader.h"

/****************************
        Complex Models
****************************/

//Object3D myBone;          To test modelLoader.h works

/**************************
        DISPLAY
**************************/
void init(void)
{
    //readOFFFile("testFile.off", &myBone);         to test modelLoader.h works

    glClearColor(0.15, 0.0, 0.36, 1.0); /* set colour of background */
    glLineWidth(5.0);   /* draw using lines 5 pixels wide */

    glEnable(GL_DEPTH_TEST);

    /* switch matrix mode to 'projection' and load an identity matrix as the projection matrix */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble fov = 60;		// degrees
    GLdouble aspect	 = 1;		// aspect ratio
    GLdouble nearVal = 0.1;
    GLdouble farVal = 1000;     // near and far clipping planes
    gluPerspective(fov, aspect, nearVal, farVal);

    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    processKeys();
    processMouse();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(  xc, yc, zc,
                xc+lx, yc+ly, zc+lz,
                0, 1, 0);

    drawOrientationMarker();
    drawSunset();
    drawFloor();
    drawWall();
    drawBall();

    //draw3DShape(myBone);      to test modelLoader.h works

    glutSwapBuffers();      //swap the buffers
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);   //set viewport to size of window
    glMatrixMode(GL_PROJECTION);        //switch so we can manipulate how scene is viewed
    glLoadIdentity();       //reset so we don't get any artifacts
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 1000.0);       //set FOV, Aspect ration and near-far clipping
    glMatrixMode(GL_MODELVIEW);     //switch back so we can draw shapes correctly
}


/*************************
        MAIN
*************************/

int main(int argc, char **argv)
{
    glutInit(&argc, argv);      //initialise GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);       //doubl buffered display that accepts RGBA colour
    glutInitWindowSize (500, 500);      //set width and height of window
    glutInitWindowPosition(100, 100);       //set window position
    glutCreateWindow("Placeholder Window name");        //creates window and gives name

    glutGameModeString("1920x1080:32@60");
    glutEnterGameMode();

    glutTimerFunc(TIMERSECS, animate, 0);

    init();

    startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
    prevTime = startTime;

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    glutPassiveMotionFunc(mouseMovement);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(250, 250);      //middle of the initial 500x500 window

    resetObject();

    glutMainLoop();
}
