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


void drawOrientationMarker(void);

void drawSunset(void);

void drawFloor(void);

extern objStats wallStats;
void drawWall(void);

void drawBall(void);


#endif // DRAWSCENE_H
