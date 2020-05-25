#include "drawScene.h"

void drawOrientationMarker(void)        //blue marker at 0,0-1,0
{
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0.0, 0.8, 1.0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
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

objStats wallStats = {.xmin = -4, .xmax = 4,
            .ymin = 4, .ymax = 4 + 4,
            .zmin = -5, .zmax = -5};


void drawWall(void)
{

    glPushMatrix();
    glColor3f(0.0, 0.8, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(wallStats.xmin, wallStats.ymin, wallStats.zmin);
    glVertex3f(wallStats.xmin, wallStats.ymax, wallStats.zmin);
    glVertex3f(wallStats.xmax, wallStats.ymax, wallStats.zmin);
    glVertex3f(wallStats.xmax, wallStats.ymin, wallStats.zmin);
    glEnd();
    glPopMatrix();
}

void drawBall(void)
{
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); //set colour of bone
    glTranslatef(currPos[0], currPos[1], currPos[2]);
    glScalef(objScale, objScale, objScale);    //bone can size up or down
    glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f);    //rotate bone
    glutWireSphere(objScale, 20, 16);
    glLoadIdentity();
    glPopMatrix();
}


