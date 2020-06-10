//drawScene.h - draws the scene for assignment 2
//Connor Nicholson
//16 May 20


#ifndef DRAWSCENE_H
#define DRAWSCENE_H

#include <GL/freeglut.h>
#include "animation.h"

typedef struct
{
    float xmin, xmax, ymin, ymax, zmin, zmax
}objStats;

void onScreenText();

extern objStats pillarStats;
void drawPillar(void);

void drawSunset(void);

void drawFloor(void);

void drawWalls(void);

extern objStats wall1Stats;
void drawWall1(void);

extern objStats wall2Stats;
void drawWall2(void);

extern objStats wall3Stats;
void drawWall3(void);


void drawBall1(void);
void drawBall2(void);


#endif // DRAWSCENE_H
