#include "drawScene.h"

void onScreenText(void)
{
    //set orthographic projection
    GLdouble width = 1920;
    GLdouble height = 1080;
    float x = 5, y = 20, z = 0;
    char text[17][50] = {
        {"CONTROLS:\0"},
        {"\0"},
        {"Move: ............................. W A S D\0"},
        {"Up: ................................. Spacebar\0"},
        {"Down: ......................................... C\0"},
        {"Reset balls ................................. 1\0"},
        {"Throw ball: ... Left Mouse Button\0"},
        {"Rotate ball: ................................. R\0"},
        {"Grow ball: ................................... K\0"},
        {"Shrink ball: ................................. J\0"},
        {"Increase gravity: ...................... M\0"},
        {"Decrease gravity: .................... N\0"},
        {"Increase throw force: ............... O\0"},
        {"Decrease throw force: .............. I\0"},
        {"\0"},
        {"GRAVITY PLACEHOLDER\0"},
        {"THROW FORCE PLACEHOLDER\0"},
    };
    sprintf(text[15], "Current gravity ................... %%%.0f\0:", gravMultiplier*100);
    sprintf(text[16], "Throw force ......................... %%%.0f\0:", throwForce*10);

    for(int i=0; i<17; i++)
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

int ball1Near = 0;
int ball2Near = 0;       //false
int ballHeld = 0;       //false
void grabBallPrompt(void)
{
    if((ball1Near || ball2Near) && !ballHeld)
    {
        //set orthographic projection
        GLdouble width = 1920;
        GLdouble height = 1080;
        float x = (width/2)-50, y = (height/2)-100, z = 0;
        char text[25] = {"PRESS E TO PICK UP\0"};

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glLoadIdentity();
        glRasterPos3f(x, y, z);
        char *c;
        for(c=text; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
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

void drawPillar(void)
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    draw3DRectangle(pillarStats.xmin, pillarStats.xmax,
                    pillarStats.ymin, pillarStats.ymax,
                    pillarStats.zmin, pillarStats.zmax);
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
    glLineWidth(15.0);     //max line width?
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
    drawWall4();        //front
}

//right from sun
objStats wall1Stats = {.xmin = -10, .xmax = 10,
            .ymin = 0, .ymax = 6,
            .zmin = -15, .zmax = -14};
void drawWall1(void)
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    draw3DRectangle(wall1Stats.xmin, wall1Stats.xmax, wall1Stats.ymin, wall1Stats.ymax, wall1Stats.zmin, wall1Stats.zmax);
    glPopMatrix();
}

//back from sun
objStats wall2Stats = {.xmin = -15, .xmax = -14,
            .ymin = 0, .ymax = 6,
            .zmin = -10, .zmax = 10};
void drawWall2(void)
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    draw3DRectangle(wall2Stats.xmin, wall2Stats.xmax, wall2Stats.ymin, wall2Stats.ymax, wall2Stats.zmin, wall2Stats.zmax);
    glPopMatrix();
}


//left from sun
objStats wall3Stats = {.xmin = -10, .xmax = 10,
            .ymin = 0, .ymax = 6,
            .zmin = 14, .zmax = 15};
void drawWall3(void)
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    draw3DRectangle(wall3Stats.xmin, wall3Stats.xmax, wall3Stats.ymin, wall3Stats.ymax, wall3Stats.zmin, wall3Stats.zmax);
    glPopMatrix();
}

//front from sun
objStats wall4Stats = {.xmin = 14, .xmax = 15,
            .ymin = 0, .ymax = 6,
            .zmin = -10, .zmax = 10};
void drawWall4(void)
{
    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    draw3DRectangle(wall4Stats.xmin, wall4Stats.xmax, wall4Stats.ymin, wall4Stats.ymax, wall4Stats.zmin, wall4Stats.zmax);
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

void draw3DRectangle(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    //top
    glBegin(GL_QUADS);
    glVertex3f(xmin, ymax, zmax);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmax, ymax, zmin);
    glEnd();
    //front
    glBegin(GL_QUADS);
    glVertex3f(xmin, ymin, zmax);
    glVertex3f(xmin, ymax, zmax);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmax, ymin, zmax);
    glEnd();
    //Left
    glBegin(GL_QUADS);
    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmin, ymax, zmax);
    glVertex3f(xmin, ymin, zmax);
    glEnd();
    //back
    glBegin(GL_QUADS);
    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmin, ymax, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymin, zmin);
    glEnd();
    //right
    glBegin(GL_QUADS);
    glVertex3f(xmax, ymin, zmin);
    glVertex3f(xmax, ymax, zmin);
    glVertex3f(xmax, ymax, zmax);
    glVertex3f(xmax, ymin, zmax);
    glEnd();
    //bottom
    glBegin(GL_QUADS);
    glVertex3f(xmin, ymin, zmax);
    glVertex3f(xmin, ymin, zmin);
    glVertex3f(xmax, ymin, zmax);
    glVertex3f(xmax, ymin, zmin);
    glEnd();
}


