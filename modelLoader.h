//modelLoader.h - loads 3d models from .off files
//Connor Nicholson
//16 May 20

#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <GL/freeglut.h>

#include <stdio.h>

typedef GLfloat point3[3];
typedef int     Face[3];

typedef struct {
    int nvert, nfaces;
    point3* vertices;
    Face*   faces;

} Object3D;


/*************************************************/

void readOFFFile(const char* file_name, Object3D* obj);

void draw3DShape(Object3D obj);

#endif
