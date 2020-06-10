#include "drawScene.h"

void onScreenText(void)
{
    //set orthographic projection
    GLdouble width = 1920;
    GLdouble height = 1080;
    float x = 5, y = 20, z = 0;
    char text[8][25] = {
        {"CONTROLS:\0"},
        {"Move: w a s d\0"},
        {"Up: Spacebar\0"},
        {"Down: c\0"},
        {"Reset balls: 1\0"},
        {"Throw ball: 2\0"},
        {"Rotate ball: r\0"},
        {"Grow/shrink ball: +/-\0"}
    };

    for(int i=0; i<8; i++)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glLoadIdentity();
        glRasterPos3f(x, y+(20*i), z);
        char *c;
        for(c=text[i]; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        glPopMatrix();

        //restore Perspective projection
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

}

objStats pillarStats = {.xmin = -1.0, .xmax = 1.0,
            .ymin = 0, .ymax = 4,
            .zmin = -1.0, .zmax = 1.0};

void drawPillar(void)        //blue marker at 0,0-1,0
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    //top
    glBegin(GL_QUADS);
    glVertex3f(pillarStats.xmin, pillarStats.ymax, pillarStats.zmax);
    glVertex3f(pillarStats.xmin, pillarStats.ymax, pillarStats.zmin);
    glVertex3f(pillarStats.xmax, pillarStats.ymax, pillarStats.zmax);
    glVertex3f(pillarStats.xmax, pillarStats.ymax, pillarStats.zmin);
    glEnd();
    //front
    glBegin(GL_QUADS);
    glVertex3f(pillarStats.xmin, pillarStats.ymin, pillarStats.zmax);
    glVertex3f(pillarStats.xmin, pillarStats.ymax, pillarStats.zmax);
    glVertex3f(pillarStats.xmax, pillarStats.ymax, pillarStats.zmax);
    glVertex3f(pillarStats.xmax, pillarStats.ymin, pillarStats.zmax);
    glEnd();
    //Left
    glBegin(GL_QUADS);
    glVertex3f(pillarStats.xmin, pillarStats.ymin, pillarStats.zmin);
    glVertex3f(pillarStats.xmin, pillarStats.ymax, pillarStats.zmin);
    glVertex3f(pillarStats.xmin, pillarStats.ymax, pillarStats.zmax);
    glVertex3f(pillarStats.xmin, pillarStats.ymin, pillarStats.zmax);
    glEnd();
    //back
    glBegin(GL_QUADS);
    glVertex3f(pillarStats.xmin, pillarStats.ymin, pillarStats.zmin);
    glVertex3f(pillarStats.xmin, pillarStats.ymax, pillarStats.zmin);
    glVertex3f(pillarStats.xmax, pillarStats.ymax, pillarStats.zmin);
    glVertex3f(pillarStats.xmax, pillarStats.ymin, pillarStats.zmin);
    glEnd();
    //right
    glBegin(GL_QUADS);
    glVertex3f(pillarStats.xmax, pillarStats.ymin, pillarStats.zmin);
    glVertex3f(pillarStats.xmax, pillarStats.ymax, pillarStats.zmin);
    glVertex3f(pillarStats.xmax, pillarStats.ymax, pillarStats.zmax);
    glVertex3f(pillarStats.xmax, pillarStats.ymin, pillarStats.zmax);
    glEnd();
    //bottom
    glBegin(GL_QUADS);
    glVertex3f(pillarStats.xmin, pillarStats.ymin, pillarStats.zmax);
    glVertex3f(pillarStats.xmin, pillarStats.ymin, pillarStats.zmin);
    glVertex3f(pillarStats.xmax, pillarStats.ymin, pillarStats.zmax);
    glVertex3f(pillarStats.xmax, pillarStats.ymin, pillarStats.zmin);
    glEnd();
    glPopMatrix();

}

void drawSunset(void)
{
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.4f, 1.0f);
    glTranslatef(800, -20, 0);
    glutSolidSphere(300, 100, 100);
    //lines accross sunset
    glColor4f(0.15, 0.0, 0.36, 1.0);
    glLineWidth(150.0);     //max line width?
    for(int i=75; i>-100; i-=15)
    {
        glBegin(GL_LINES);
        glVertex3f(-310, i, -1000);
        glVertex3f(-310, i, 1000);
        glEnd();
    }
    glLoadIdentity();
    glPopMatrix();
}

void drawFloor(void)
{
    float flength = 100;    //floor length  = units either side from 0,0

    glPushMatrix();
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex3f( -flength, 0.0, -flength);
    glVertex3f( -flength, 0.0, flength);
    glVertex3f(flength, 0.0, flength);
    glVertex3f(flength, 0.0, -flength);
    glEnd();
    //grid on floor
    glLineWidth(5.0);
    glBegin(GL_LINES);
    for(int i=-flength;i<=flength;i=i+2) {
        if(i==-flength){ glColor3f(1.0, 0.5, 1.0); } else { glColor3f(0.8, 0.2, 0.8); };
        glVertex3f(i,0,-flength);
        glVertex3f(i,0,flength);
        if (i==-flength) { glColor3f(1.0, 0.5, 1.0); } else { glColor3f(0.8, 0.2, 0.8); };
        glVertex3f(-flength,0,i);
        glVertex3f(flength,0,i);
    };
    glEnd();
    glPopMatrix();
}

//orientated with back towards the sun
void drawWalls(void)
{
    drawWall1();        //right
    drawWall2();        //back
    drawWall3();        //left
}

//right from sun
objStats wall1Stats = {.xmin = -10, .xmax = 10,
            .ymin = 0, .ymax = 6,
            .zmin = -10, .zmax = -10};
void drawWall1(void)
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(wall1Stats.xmin, wall1Stats.ymin, wall1Stats.zmin);
    glVertex3f(wall1Stats.xmin, wall1Stats.ymax, wall1Stats.zmin);
    glVertex3f(wall1Stats.xmax, wall1Stats.ymax, wall1Stats.zmin);
    glVertex3f(wall1Stats.xmax, wall1Stats.ymin, wall1Stats.zmin);
    glEnd();
    glPopMatrix();
}

//back from sun
objStats wall2Stats = {.xmin = -10, .xmax = -10,
            .ymin = 0, .ymax = 6,
            .zmin = -10, .zmax = 10};
void drawWall2(void)
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(wall2Stats.xmin, wall2Stats.ymin, wall2Stats.zmax);
    glVertex3f(wall2Stats.xmin, wall2Stats.ymax, wall2Stats.zmax);
    glVertex3f(wall2Stats.xmin, wall2Stats.ymax, wall2Stats.zmin);
    glVertex3f(wall2Stats.xmin, wall2Stats.ymin, wall2Stats.zmin);
    glEnd();
    glPopMatrix();
}


//left from sun
objStats wall3Stats = {.xmin = -10, .xmax = 10,
            .ymin = 0, .ymax = 6,
            .zmin = 10, .zmax = 10};
void drawWall3(void)
{

    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(wall3Stats.xmin, wall3Stats.ymin, wall3Stats.zmin);
    glVertex3f(wall3Stats.xmin, wall3Stats.ymax, wall3Stats.zmin);
    glVertex3f(wall3Stats.xmax, wall3Stats.ymax, wall3Stats.zmin);
    glVertex3f(wall3Stats.xmax, wall3Stats.ymin, wall3Stats.zmin);
    glEnd();
    glPopMatrix();
}

void drawBall1(void)
{
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //set colour of bone
    glTranslatef(ball1CurrPos[0], ball1CurrPos[1], ball1CurrPos[2]);
    glScalef(ball1Scale, ball1Scale, ball1Scale);    //bone can size up or down
    glRotatef(ball1YRotationAngle, 0.0f, 1.0f, 0.0f);    //rotate bone
    glutWireSphere(ball1Scale, 20, 16);
    glLoadIdentity();
    glPopMatrix();
}

void drawBall2(void)
{
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //set colour of bone
    glTranslatef(ball2CurrPos[0], ball2CurrPos[1], ball2CurrPos[2]);
    glScalef(ball2Scale, ball2Scale, ball2Scale);    //bone can size up or down
    glRotatef(ball2YRotationAngle, 0.0f, 1.0f, 0.0f);    //rotate bone
    glutWireSphere(ball2Scale, 20, 16);
    glLoadIdentity();
    glPopMatrix();
}


